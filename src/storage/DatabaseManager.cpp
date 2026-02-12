#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(std::unique_ptr<IDatabaseManager> localBackend,
                                 std::unique_ptr<IDatabaseManager> cloudBackend,
                                 QObject *parent)
    : QObject(parent),
      local_(std::move(localBackend)),
      cloud_(std::move(cloudBackend))
{}

bool DatabaseManager::initialize()
{
    bool ok = true;

    if (local_) {
        ok &= local_->initialize();
    } else {
        qWarning() << "No local backend provided!";
    }

    if (cloud_) {
        ok &= cloud_->initialize();
    }

    return ok;
}

void DatabaseManager::insertRecord(const QString &table, const QVariantMap &data)
{
    if (local_) {
        if (!local_->insertData(table, data)) {
            qWarning() << "Local insert failed in table: " << table;
        }
    }

    if (cloud_) {
        cloud_->insertData(table, data);
    }
}
