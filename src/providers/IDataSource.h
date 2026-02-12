#ifndef IDATASOURCE_H
#define IDATASOURCE_H

#include <QObject>
#include "core/EEGSample.h"

class IDataSource : public QObject {
    Q_OBJECT
public:
    explicit IDataSource(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IDataSource() {}

    virtual bool start() = 0;
    virtual void stop() = 0;

signals:
    void dataReceived(const EEGSample &sample);
};

#endif // IDATASOURCE_H
