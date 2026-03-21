#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QMutex>

class Logger
{
public:
    // Instaluje handler w systemie Qt
    static void install();
    static void logExecutionStart();
    static void logExecutionEnd();

    // Zwraca ścieżkę do aktualnego pliku logu (do wysyłki)
    static QString getLogFilePath();

private:
    // Funkcja przechwytująca wszystkie qDebug, qWarning itd.
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    static void writeLogEntry(const QJsonObject &entry);

    // Zarządzanie rotacją plików
    static void rotateLogs(const QString &basePath);

    static QMutex s_mutex; // Zapewnia bezpieczeństwo przy wielu wątkach
    static QDateTime s_startTime;

    static const qint64 MAX_FILE_SIZE = 1024 * 1024; // 1MB
    static const int MAX_FILES = 5;
};

#endif // LOGGER_H
