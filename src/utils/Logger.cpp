#include <QJsonObject>
#include <QJsonDocument>

#include "Logger.h"
#include "storage/DatabaseConfig.h"

QMutex Logger::s_mutex;
QDateTime Logger::s_startTime;

void Logger::install()
{
    s_startTime = QDateTime::currentDateTime();
    qInstallMessageHandler(Logger::messageHandler);
    logExecutionStart();
}

void Logger::writeLogEntry(const QJsonObject &entry)
{
    QMutexLocker locker(&s_mutex);

    QJsonDocument doc(entry);
    QString logLine = QString::fromUtf8(doc.toJson(QJsonDocument::Compact)) + "\n";

    fprintf(stderr, "%s", logLine.toLocal8Bit().constData());

    QString filePath = getLogFilePath();
    QFile file(filePath);
    if (file.exists() && file.size() > MAX_FILE_SIZE) {
        rotateLogs(filePath);
    }

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << logLine;
        stream.flush();
        file.close();
    } else {
        fprintf(stderr, "Cannot open log file: %s\n", file.errorString().toStdString().c_str());
    }
}

void Logger::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString level;
    switch (type) {
        case QtDebugMsg:    level = "DEBUG"; break; // Co się dzieje w środku - tylko do informacji deweloperskich (pomagają zrozumieć przeływ danych, ale nie są istotne do działania systemu na produkcji)
        case QtInfoMsg:     level = "INFO"; break; // Logi, które chcemy widzieć na produkcji, żeby wiedzieć co użytkownik robił przed wystąpieniem błędu (np. start aplikacji, pomyślne połączenie z bazą, rozpoczęcie nagrywania itp)
        case QtWarningMsg:  level = "WARNING"; break; // Używać gdy wystąpił błąd, który potrafi "przeżyć", ale który nie powinien mieć miejsca (np. nie znaleziono pliku CSV ale stworzymy nowy, utrata pojedynczej próbki danych, niskie napięcie baterii sensora)
        case QtCriticalMsg: level = "CRITICAL"; break; // Poważny błąd systemowy (np. główna funkcja aplikacji przestaje działać, nie udało się zainicjalizować bazy danych)
        case QtFatalMsg:    level = "FATAL"; break; // Wywołanie qFatal domyślnie zamyka aplikację. Używać tylko w sytuacji, gdzie dalsze działanie mogłoby np. uszkodzić dane (np. brak krytycznej biblioteki, całkowite uszkodzenie struktury plików)
    }

    QJsonObject obj;
    obj["timestamp"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    obj["logLevel"] = level;
    obj["logType"] = "Default";
    obj["contextFile"] = QString::fromUtf8(context.file);
    obj["contextLine"] = context.line;
    obj["contextFunction"] = QString::fromUtf8(context.function);
    obj["message"] = msg;

    writeLogEntry(obj);
}

void Logger::logExecutionStart()
{
    QJsonObject obj;
    obj["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
    obj["logLevel"] = "INFO";
    obj["logType"] = "Execution Start";
    obj["message"] = "Process execution started";
    obj["appName"] = QCoreApplication::applicationName();
    obj["appVersion"] = QCoreApplication::applicationVersion();

    writeLogEntry(obj);
}

void Logger::logExecutionEnd()
{
    QJsonObject obj;
    obj["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
    obj["logLevel"] = "INFO";
    obj["logType"] = "Execution End";
    obj["message"] = "Process execution ended";
    obj["totalExecutionTimeInSeconds"] = s_startTime.msecsTo(QDateTime::currentDateTime()) / 1000.0;
    obj["totalExecutionTime"] = QTime(0,0).addMSecs(s_startTime.msecsTo(QDateTime::currentDateTime())).toString("hh:mm:ss.zzz");

    writeLogEntry(obj);
}


QString Logger::getLogFilePath()
{
    return DatabaseConfig::getLogFilePath();
}

void Logger::rotateLogs(const QString &basePath)
{
    // usuń najstarszy
    QFile::remove(basePath + "." + QString::number(MAX_FILES));

    // przesuń
    for (int i = MAX_FILES - 1; i >= 1; --i) {
        QFile::rename(basePath + "." + QString::number(i),
                      basePath + "." + QString::number(i + 1));
    }

    // obecny log → .1
    QFile::rename(basePath, basePath + ".1");
}
