#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QDebug>
#include <memory>

#include "IDatabaseManager.h"

class DatabaseManager : public QObject, public IDatabaseManager
{
    Q_OBJECT
public:
    DatabaseManager(std::unique_ptr<IDatabaseManager> localBackend,
                    QObject *parent = nullptr);

    bool initialize() override;
    bool insertData(const QString &table, const QVariantMap &data) override;
    bool updateData(const QString &table, const QVariantMap &data, const QString &keyColumn) override;
    QList<QVariantMap> queryData(const QString &queryStr) override;

protected:
    std::unique_ptr<IDatabaseManager> local_;
};

#endif // DATABASEMANAGER_H
