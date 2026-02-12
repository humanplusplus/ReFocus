#include <QQmlContext>
#include <QThread>

#include "ApplicationController.h"
#include "models/EEGModel.h"
#include "providers/CsvDataSource.h"
#include "storage/DataPipeline.h"
#include "storage/SQLiteManager.h"
#include "storage/DatabaseManager.h"
#include "storage/DatabaseConfig.h"

ApplicationController::ApplicationController(QObject *parent)
    : QObject(parent),
    m_eegModel(nullptr),
    m_dataPipeline(nullptr),
    m_dataSource(nullptr),
    m_dbManager(nullptr)
{}

void ApplicationController::initialize(QQmlApplicationEngine *engine)
{
    qInfo() << "Initialize modules.";

    // 1. Inicjalizacja modułów
    m_eegModel = new EEGModel(this);

    // 2. Konfiguracja bazy danych
    // Tworzenie lokalnego SQLite
    QString dbPath = DatabaseConfig::getSqliteDbPath();
    std::unique_ptr<IDatabaseManager> localBackend = std::make_unique<SQLiteManager>(dbPath);
    m_dbManager = new DatabaseManager(std::move(localBackend), nullptr, this);
    m_dbManager->initialize();

    // 3. Tworzenie rurociągu danych
    // Przekazujemy nullptr zamiast DatabaseManager, skoro na razie nie zapisujemy tam EEG
    m_dataPipeline = new DataPipeline(nullptr, this);

    // 4. Tworzenie źródła danych (np. plik CSV)
    m_dataSource = new CsvDataSource(DatabaseConfig::getCsvPath());
    m_workerThread = new QThread(this);

    // Obsługa startu i sprzątania wątku
    connect(m_workerThread, &QThread::started, m_dataSource, &IDataSource::start);
    connect(m_workerThread, &QThread::finished, m_dataSource, &QObject::deleteLater);

    m_workerThread->start();

    // 5. ŁĄCZENIE SYGNAŁÓW (Logika przepływu danych)
    // KROK A: Źródło (CSV) -> Pipeline
    connect(m_dataSource, &IDataSource::dataReceived, m_dataPipeline, &DataPipeline::onNewSampleReceived);

    // KROK B: Rurociąg (paczki danych) -> Model (wykres)
    connect(m_dataPipeline, &DataPipeline::batchReadyForUI, m_eegModel, &EEGModel::addBatch);

    // 6. Udostępnienie obiektów do QML
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("eegModel", m_eegModel);
    context->setContextProperty("appController", this);

    qInfo() << "Initialization complete.";
}
