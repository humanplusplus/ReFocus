#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

#include <QSqlDatabase>

#include "IDatabaseManager.h"

class SQLiteManager : public IDatabaseManager
{
public:
    explicit SQLiteManager(const QString &path = QString());

    bool initialize() override;
    bool insertData(const QString &table, const QVariantMap &data) override;
    bool updateData(const QString &table, const QVariantMap &data, const QString &keyColumn) override;
    QList<QVariantMap> queryData(const QString &queryStr) override;

    QList<QVariantMap> getUnsynced(const QString &table);
    bool markAsSynced(const QString &table, const QVector<QVariantMap> &records);

    QSqlDatabase getDatabase();

protected:
    QSqlDatabase db_;
    QString dbPath_;
};

#endif // SQLITEMANAGER_H
