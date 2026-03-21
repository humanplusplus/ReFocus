#ifndef BLEDATASOURCE_H
#define BLEDATASOURCE_H

#include <QObject>

class BleDataSource : public QObject
{
    Q_OBJECT
public:
    explicit BleDataSource(QObject *parent = nullptr);

signals:
};

#endif // BLEDATASOURCE_H
