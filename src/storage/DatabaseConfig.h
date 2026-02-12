#ifndef DATABASECONFIG_H
#define DATABASECONFIG_H

#include <QDir>
#include <QDebug>
#include <QString>
#include <QStandardPaths>
#include <QApplication>

namespace DatabaseConfig {

    inline QString getCsvPath() {
        return QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("../../data/openbci_training_data_cut.csv");
    }

    inline QString getLogFilePath() {
        static const QString cachedLogPath = []() {
            QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
            QDir().mkpath(path);
            return QDir(path).absoluteFilePath("app.log");
        }();

        return cachedLogPath;
    }

    inline QString getSqliteDbPath() {
        static const QString cachedSqliePath = []() {
            QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
            QDir().mkpath(path);
            return QDir(path).absoluteFilePath("EarEEG_PROD.db");
        }();
        return cachedSqliePath;
    }

    // inline QString DEFAULT_CSV_PATH = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("../../") + "/data/openbci_training_data_cut.csv";

    // inline QString DEFAULT_SQLITE_DB_PATH = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + "EarEEG_PROD.db";
    // inline QString DEFAULT_SQLITE_DB_PATH_TEST = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + "EarEEG_TEST.db";

    // // W Superbase projekt: EarEEG_DemoApp
    // inline const QString SUPABASE_URL = "";
    // inline const QString SUPABASE_API_KEY = "";

    // // W Superbase projekt: EarEEG_DemoApp_Test
    // inline const QString SUPABASE_URL_TEST = "";
    // inline const QString SUPABASE_API_KEY_TEST = "";

    inline void printDbPath() {
        qDebug() << "Using SQLite database at: " << getSqliteDbPath();
    }
}

#endif // DATABASECONFIG_H
