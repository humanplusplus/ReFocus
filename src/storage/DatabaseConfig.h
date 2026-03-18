#ifndef DATABASECONFIG_H
#define DATABASECONFIG_H

#include <QDir>
#include <QDebug>
#include <QString>
#include <QStandardPaths>
#include <QApplication>

namespace DatabaseConfig {

    inline QString getCsvPath() {
        // return QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("../../data/openbci_training_data_cut.csv");

        static const QString cachedCsvPath = []() {
            QString basePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

            QString subFolder;
            QString fileName;

            #if defined(APP_STATE_PRODUCTION)
                subFolder = "PROD";
                fileName = "openbci_training_data_cut.csv";
            #else
                subFolder = "DEV";
                fileName = "openbci_training_data_cut.csv";
            #endif

            QDir dir(basePath);
            dir.mkpath(subFolder);

            return dir.absoluteFilePath(subFolder + "/" + fileName);
        }();

        return cachedCsvPath;
    }

    inline QString getLogFilePath() {
        static const QString cachedLogPath = []() {
            QString basePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

            QString subFolder;
            QString fileName;

            #if defined(APP_STATE_PRODUCTION)
                subFolder = "PROD";
                fileName = "app_PROD.log.0";
            #else
                subFolder = "DEV";
                fileName = "app_DEV.log.0";
            #endif

            QDir dir(basePath);
            dir.mkpath(subFolder);

            return dir.absoluteFilePath(subFolder + "/" + fileName);
        }();

        return cachedLogPath;
    }

    inline QString getSqliteDbPath() {
        static const QString cachedSqliePath = []() {
            QString basePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

            QString subFolder;
            QString fileName;

            #if defined(APP_STATE_PRODUCTION)
                subFolder = "PROD";
                fileName = "EarEEG_PROD.db";
            #else
                subFolder = "DEV";
                fileName = "EarEEG_DEV.db";
            #endif

            QDir dir(basePath);
            dir.mkpath(subFolder);

            return dir.absoluteFilePath(subFolder + "/" + fileName);
        }();
        return cachedSqliePath;
    }

    inline void printDbPath() {
        qDebug() << "Using SQLite database at: " << getSqliteDbPath();
    }
}

#endif // DATABASECONFIG_H
