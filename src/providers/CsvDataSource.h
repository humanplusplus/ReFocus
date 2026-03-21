#ifndef CSVDATASOURCE_H
#define CSVDATASOURCE_H

#include <QFile>
#include <QTimer>

#include "IDataSource.h"

class CsvDataSource : public IDataSource {
    Q_OBJECT
public:
    explicit CsvDataSource(const QString &filePath, QObject *parent = nullptr);
    ~CsvDataSource(); // Ważne przy pracy z wątkami

    bool start() override;
    void stop() override;

private slots:
    void readNextLine();

private:
    QString m_filePath;
    QFile m_file;
    QTimer *m_timer;
    const int m_frequency = 250;
};

#endif // CSVDATASOURCE_H
