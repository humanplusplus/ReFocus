#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "SettingsRepository.h"
#include "TableSchemasSQLite.h"

SettingsRepository::SettingsRepository(IDatabaseManager *dataManager, QObject *parent)
    : QObject(parent), m_dataManager(dataManager) {}

bool SettingsRepository::upsertSettings(const QString &key, const QVariant &value) {
    QSqlQuery query;

    query.prepare(QString(
        "INSERT INTO %1 (key, value, updated_at) "
        "VALUES (:key, :value, datetime('now')) "
        "ON CONFLICT(key) DO UPDATE SET "
        "value = excluded.value, "
        "updated_at = excluded.updated_at"
    ).arg(TableNamesSQLite::SETTINGS));

    query.bindValue(":key", key);
    query.bindValue(":value", value.toString());

    if (!query.exec()) {
        qWarning() << "Error while saving settings value: " << query.lastError().text();
        return false;
    }

    return query.exec();
}

QVariant SettingsRepository::getSettingValue(const QString &key, const QVariant &defaultValue) {
    QSqlQuery query;
    query.prepare(QString("SELECT value FROM %1 WHERE key = :key").arg(TableNamesSQLite::SETTINGS));
    query.bindValue(":key", key);

    if (query.exec() && query.next()) {
        return query.value(0);
    }
    return defaultValue;
}
