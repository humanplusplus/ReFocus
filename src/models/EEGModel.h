#ifndef EEGMODEL_H
#define EEGMODEL_H

#include <QVector>
#include <QObject>
#include <QPointF>
#include <QMap>
#include <QDebug>

class EEGModel : public QObject {
    Q_OBJECT
    // Właściwość do śledzenia czasu, aby przesuwać oś X w QML
    Q_PROPERTY(double lastestTimestamp READ lastestTimestamp NOTIFY dataUpdated)

public:
    explicit EEGModel(QObject *parent = nullptr);

    // Ta metoda pozwala LinesGraph w QML pobrać punkty dla konkretnego kanału
    Q_INVOKABLE QVector<QPointF> getPointsForChannel(int channelIndex) const;

    double lastestTimestamp() const { return m_lastestTimestamp; }

public slots:
    void addBatch(const QMap<int, QVector<QPointF>> &batch); // Slot odbierający paczkę z DataPipeline (zmieniony typ danych!)

signals:
    void dataUpdated();

private:
    QMap<int, double> m_firstValues; // zapamiętuje poziom bazowy
    QMap<int, QVector<QPointF>> m_channelBuffers; // przechowujemy osobny wektor punktów dla każdego z 8 kanałów
    double m_lastestTimestamp = 0;
    const int m_maxSamplesPerChannle = 2000; // Limit punktów w pamięci (np. 2000 próbek = ~8 sekund przy 250Hz)
};

#endif // EEGMODEL_H
