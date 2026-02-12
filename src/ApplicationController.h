#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

class EEGModel;
class DataPipeline;
class SQLiteManager;
class IDataSource;
class DatabaseManager;

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationController(QObject *parent = nullptr);

    // Konfiguracja wszystkiego i wstrzykiwanie do silnika QML
    void initialize(QQmlApplicationEngine *engine);

private:
    // Trzymanie głównych modułów aplikacji
    EEGModel* m_eegModel;
    DataPipeline* m_dataPipeline;
    IDataSource* m_dataSource;
    DatabaseManager* m_dbManager;
    QThread* m_workerThread;
};

#endif // APPLICATIONCONTROLLER_H
