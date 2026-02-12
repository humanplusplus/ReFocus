#ifndef BINDATASOURCE_H
#define BINDATASOURCE_H

#include <QObject>

class BinDataSource : public QObject
{
    Q_OBJECT
public:
    explicit BinDataSource(QObject *parent = nullptr);

signals:
};

#endif // BINDATASOURCE_H
