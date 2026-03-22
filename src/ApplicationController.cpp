#include <QQmlContext>
#include <QThread>

#include "ApplicationController.h"
#include "models/EEGModel.h"
#include "models/NoteModel.h"
#include "storage/NoteRepository.h"
#include "models/ParticipantModel.h"
#include "storage/ParticipantRepository.h"
#include "storage/SettingsRepository.h"
#include "providers/CsvDataSource.h"
#include "storage/DataPipeline.h"
#include "storage/SQLiteManager.h"
#include "storage/DatabaseManager.h"
#include "storage/DatabaseConfig.h"

ApplicationController::ApplicationController(QObject *parent)
    : QObject(parent),
    m_eegModel(nullptr),
    m_noteModel(nullptr),
    m_noteRepo(nullptr),
    m_participantModel(nullptr),
    m_participantRepo(nullptr),
    m_settingsRepo(nullptr),
    m_dataPipeline(nullptr),
    m_dataSource(nullptr),
    m_dbManager(nullptr),
    m_workerThread(nullptr)
{}

ApplicationController::~ApplicationController()
{
    qInfo() << "Cleaning up ApplicationController and stopping threads...";

    if (m_workerThread) {
        m_workerThread->quit();
        m_workerThread->wait(2000);
    }

    qInfo() << "Cleanup complete.";
}

void ApplicationController::initialize(QQmlApplicationEngine *engine)
{
    qInfo() << "Initialize modules.";

    // 1. Inicjalizacja modułów
    m_eegModel = new EEGModel(this);

    // 2. Konfiguracja bazy danych: tworzenie lokalnego SQLite
    QString dbPath = DatabaseConfig::getSqliteDbPath();
    std::unique_ptr<IDatabaseManager> localBackend = std::make_unique<SQLiteManager>(dbPath);
    m_dbManager = new DatabaseManager(std::move(localBackend));
    m_dbManager->initialize();

    // --- TWORZENIE NOWYCH MODUŁÓW ---
    m_noteRepo = new NoteRepository(m_dbManager, this);
    m_noteModel = new NoteModel(m_noteRepo, this);

    connect(m_noteRepo, &NoteRepository::noteDataChanged, m_noteModel, &NoteModel::refresh);

    m_participantRepo = new ParticipantRepository(m_dbManager, this);
    m_participantModel = new ParticipantModel(m_participantRepo, this);

    connect(m_participantRepo, &ParticipantRepository::participantDataChanged, m_participantModel, &ParticipantModel::refresh);

    m_settingsRepo = new SettingsRepository(m_dbManager, this);

    // 3. Rurociąg danych i źródło danych CSV: przekazujemy nullptr zamiast DatabaseManager, skoro na razie nie zapisujemy tam EEG
    m_dataPipeline = new DataPipeline(nullptr, nullptr);
    m_dataSource = new CsvDataSource(DatabaseConfig::getCsvPath(), nullptr);

    // 4. Wątek roboczy
    m_workerThread = new QThread(this);

    // // 5. PRZENIESIENIE DO WĄTKU (najpierw przenosimy, potem łączymy)
    m_dataSource->moveToThread(m_workerThread);
    m_dataPipeline->moveToThread(m_workerThread);

    // 6. ŁĄCZENIE SYGNAŁÓW
    connect(m_workerThread, &QThread::started, m_dataSource, &IDataSource::start);
    connect(m_workerThread, &QThread::started, m_dataPipeline, &DataPipeline::startProcessing);

    connect(m_dataSource, &IDataSource::dataReceived, m_dataPipeline, &DataPipeline::onNewSampleReceived);
    connect(m_dataPipeline, &DataPipeline::batchReadyForUI, m_eegModel, &EEGModel::addBatch);

    // Czyszczenie
    connect(m_workerThread, &QThread::finished, m_dataSource, &QObject::deleteLater);
    connect(m_workerThread, &QThread::finished, m_dataPipeline, &QObject::deleteLater);

    // 7. START
    m_workerThread->start();

    // 8. Udostępnienie obiektów do QML
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("eegModel", m_eegModel);
    context->setContextProperty("noteRepo", m_noteRepo);
    context->setContextProperty("noteModel", m_noteModel);
    context->setContextProperty("participantRepo", m_participantRepo);
    context->setContextProperty("participantModel", m_participantModel);
    context->setContextProperty("settingsRepo", m_settingsRepo);
    context->setContextProperty("appController", this);

    qInfo() << "Initialization complete.";
}
