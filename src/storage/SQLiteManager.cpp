#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>
#include <QDebug>

#include "SQLiteManager.h"
#include "TableSchemasSQLite.h"
#include "DatabaseConfig.h"

SQLiteManager::SQLiteManager(const QString &path)
    : dbPath_(path.isEmpty() ? DatabaseConfig::getSqliteDbPath() : path) {}

bool SQLiteManager::initialize()
{
    db_ = QSqlDatabase::addDatabase("QSQLITE", "ear_eeg_connection");
    db_.setDatabaseName(dbPath_);

    if (!db_.open()) {
        qCritical() << "Failed to open database: " << db_.lastError();
        return false;
    }

    qDebug() << "Database initialize at: " << dbPath_;
    DatabaseConfig::printDbPath();

    QSqlQuery query(db_);
    for (const QString &stmts : TableSchemasSQLite::createAllTables()) {
        if (!query.exec(stmts)) {
            qCritical() << "Failed to execute all table schemas: " << stmts << " Error: " << query.lastError().text();
            return false;
        }
    }

    qDebug() << "Database initialized at: " << dbPath_;
    return true;
}

bool SQLiteManager::insertData(const QString &table, const QVariantMap &data)
{
    if (!db_.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QStringList columns, placeholders;
    for (auto it = data.begin(); it != data.end(); ++it) {
        columns << it.key();
        placeholders << ":" + it.key();
    }

    QString sql = QString("INSERT INTO %1 (%2) VALUES (%3)")
                      .arg(table, columns.join(", "), placeholders.join(", "));

    QSqlQuery query(db_);
    if (!query.prepare(sql)) {
        qWarning() << "Prepare failed:" << query.lastError().text();
        return false;
    }

    for (auto it = data.begin(); it != data.end(); ++it) {
        query.bindValue(":" + it.key(), it.value());
    }

    if (!query.exec()) {
        qWarning() << "Insert failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "Insert successful into" << table;
    return true;
}


QList<QVariantMap> SQLiteManager::queryData(const QString &queryStr)
{
    QList<QVariantMap> results;

    if (!db_.isOpen()) {
        qWarning() << "Database id not open!";
        return results;
    }

    QSqlQuery query(db_);
    if (!query.exec(queryStr)) {
        qWarning() << "Query failed: " << query.lastError().text();
        return results;
    }

    while (query.next()) {
        QVariantMap row;
        for (int i = 0; i < query.record().count(); i++) {
            row.insert(query.record().fieldName(i), query.value(i));
        }
        results.append(row);
    }

    return results;
}

QList<QVariantMap> SQLiteManager::getUnsynced(const QString &table)
{
    QString queryStr = QString("SELECT * FROM %1 WHERE synced = 0 OR synced IS NULL").arg(table);
    return queryData(queryStr);
}

bool SQLiteManager::markAsSynced(const QString &table, const QVector<QVariantMap> &records)
{
    QSqlQuery query(db_);
    db_.transaction();
    for (const auto &record : records) {
        QString uuid = record["uuid"].toString();
        query.prepare(QString("UPDATE %1 SET synced = 1 WHERE uuid = :uuid").arg(table));
        query.bindValue(":uuid", uuid);
        if (!query.exec()) {
            qWarning() << "Failed to mark record as synced: " << query.lastError().text();
            db_.rollback();
            return false;
        }
    }
    db_.commit();
    return true;
}

QSqlDatabase SQLiteManager::getDatabase()
{
    if (QSqlDatabase::contains("ear_eeg_connection")) {
        return QSqlDatabase::database("ear_eeg_connection");
    }
    return db_;
}

bool SQLiteManager::updateData(const QString &table,
                               const QVariantMap &data,
                               const QString &keyColumn)
{
    if (!db_.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    if (keyColumn.isEmpty() || !data.contains(keyColumn)) {
        qWarning() << "Missing key column or key value!";
        return false;
    }

    QStringList assignments;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it.key() != keyColumn) {
            assignments << QString("%1 = :%1").arg(it.key());
        }
    }

    QString sql = QString("UPDATE %1 SET %2 WHERE %3 = :%3")
                      .arg(table, assignments.join(", "), keyColumn);

    QSqlQuery query(db_);
    if (!query.prepare(sql)) {
        qWarning() << "Prepare failed:" << query.lastError().text();
        return false;
    }

    // bindowanie wszystkich wartości
    for (auto it = data.begin(); it != data.end(); ++it) {
        query.bindValue(":" + it.key(), it.value());
    }

    if (!query.exec()) {
        qWarning() << "Update failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "Update successful for" << table << " WHERE: " << keyColumn;
    return true;
}



