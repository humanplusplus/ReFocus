#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(std::unique_ptr<IDatabaseManager> localBackend,
                                 QObject *parent)
    : QObject(parent),
      local_(std::move(localBackend))
{}

bool DatabaseManager::initialize()
{
    if (!local_) {
        qWarning() << "No local backend provided!";
        return false;
    }

    return local_->initialize();
}

bool DatabaseManager::insertData(const QString &table, const QVariantMap &data)
{
    if (!local_) {
        qWarning() << "No local backend for insertData";
        return false;
    }
    return local_->insertData(table, data);
}

bool DatabaseManager::updateData(const QString &table,
                                 const QVariantMap &data,
                                 const QString &keyColumn)
{
    if (!local_) {
        qWarning() << "No local backend for updateData";
        return false;
    }
    return local_->updateData(table, data, keyColumn);
}

QList<QVariantMap> DatabaseManager::queryData(const QString &queryStr)
{
    if (!local_) {
        qWarning() << "No local backend for queryData";
        return {};
    }
    return local_->queryData(queryStr);
}
