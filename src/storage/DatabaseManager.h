#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QDebug>
#include <memory>

#include "IDatabaseManager.h"

class DatabaseManager : public IDatabaseManager
{
    Q_OBJECT
public:
    DatabaseManager(std::unique_ptr<IDatabaseManager> localBackend,
                    std::unique_ptr<IDatabaseManager> cloudBackend = nullptr,
                    QObject *parent = nullptr);

    bool initialize();
    void insertRecord(const QString &table, const QVariantMap &data);
    void updateRecord(const QString &table, const QVariantMap &data, const QString &keyColumn);

protected:
    std::unique_ptr<IDatabaseManager> local_;
    std::unique_ptr<IDatabaseManager> cloud_;
};

#endif // DATABASEMANAGER_H
