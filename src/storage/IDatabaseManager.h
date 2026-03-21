#ifndef IDATABASEMANAGER_H
#define IDATABASEMANAGER_H

#include <QString>
#include <QVariantMap>

class IDatabaseManager
{
public:
    virtual ~IDatabaseManager() = default;

    virtual bool initialize() = 0;
    virtual bool insertData(const QString &table, const QVariantMap &data) = 0;
    virtual bool updateData(const QString &table, const QVariantMap &data, const QString &keyColumn) = 0;
    virtual QList<QVariantMap> queryData(const QString &queryStr) = 0;
};

#endif // IDATABASEMANAGER_H
