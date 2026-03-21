#ifndef EEGMODEL_H
#define EEGMODEL_H

#include <QVector>
#include <QObject>
#include <QPointF>
#include <QMap>
#include <QDebug>
#include <algorithm>
#include <cmath>

class EEGModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(double latestTimestamp READ latestTimestamp NOTIFY dataUpdated)

public:
    explicit EEGModel(QObject *parent = nullptr);

    Q_INVOKABLE QVector<QPointF> getLeadingPoints(int channelIndex) const; // Pobiera punkty od 0 do kursora
    Q_INVOKABLE QVector<QPointF> getTrailingPoints(int channelIndex) const; // Pobiera punkty od kursora + przerwa do 5s
    Q_INVOKABLE void clear();

    double latestTimestamp() const { return m_latestTimestamp; }

public slots:
    void addBatch(const QMap<int, QVector<QPointF>> &batch);

signals:
    void dataUpdated();

private:
    QMap<int, QVector<QPointF>> m_fullHistory; // Pełna historia punktów (nieposortowana paczka dla fmod)
    double m_latestTimestamp = 0;
    const double m_windowSize = 5.0;
    const double m_gapSize = 0.1; // Szerokość "dziury" przed kursorem
    const int m_maxSamplesPerChannel = 2000;
};

#endif // EEGMODEL_H
