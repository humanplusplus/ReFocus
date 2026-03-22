#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

class EEGModel;
class NoteModel;
class NoteRepository;
class ParticipantModel;
class ParticipantRepository;
class SettingsRepository;
class DataPipeline;
class SQLiteManager;
class IDataSource;
class DatabaseManager;

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationController(QObject *parent = nullptr);
    ~ApplicationController();

    // NA RAZIE WYCOFUJEMY - BĘDZIE WDROŻONE W KOLEJNYM ETAPIE
    // Q_INVOKABLE void startStreaming(int mode); // 0: CSV, 1: BIN, 2: BLE
    // Q_INVOKABLE void stopStreaming();

    void initialize(QQmlApplicationEngine *engine);

private:
    EEGModel* m_eegModel;
    NoteModel* m_noteModel;
    NoteRepository* m_noteRepo;
    ParticipantModel* m_participantModel;
    ParticipantRepository* m_participantRepo;
    SettingsRepository* m_settingsRepo;
    DataPipeline* m_dataPipeline;
    IDataSource* m_dataSource;
    DatabaseManager* m_dbManager;
    QThread* m_workerThread;
};

#endif // APPLICATIONCONTROLLER_H
