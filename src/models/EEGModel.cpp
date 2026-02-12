#include "EEGModel.h"

EEGModel::EEGModel(QObject *parent) : QObject(parent) {}

QVector<QPointF> EEGModel::getPointsForChannel(int channelIndex) const {
    return m_channelBuffers.value(channelIndex);
}

void EEGModel::addBatch(const QMap<int, QVector<QPointF>> &batch) {
    const double windowSize = 5.0;
    const double offsetStep = 50.0;

    for (auto it = batch.begin(); it != batch.end(); ++it) {
        int ch = it.key();
        QVector<QPointF> &currentBuffer = m_channelBuffers[ch];
        QVector<QPointF> incomingPoints = it.value();

        for (QPointF &p : incomingPoints) {
            // 1. Obliczamy X w trybie Sweep (modulo)
            double xPos = fmod(p.x(), windowSize);

            // 2. Y z mocniejszym gainem (np. x 1.0 zamiast 0.01)
            // Używamy baseline, żeby sygnał oscylował wokół zera
            double zeroedY = p.y(); // p.y ma już gain z Pipeline
            p.setX(xPos);
            p.setY(zeroedY + (ch * offsetStep));

            // 3. Usuwamy stare punkty "przed" linią kasującą
            currentBuffer.erase(
                std::remove_if(currentBuffer.begin(), currentBuffer.end(), [&](const QPointF& oldP) {
                    return (oldP.x() >= xPos && oldP.x() < xPos + 0.1);
                }),
                currentBuffer.end()
                );
            currentBuffer.append(p);
        }

        // 4. Sortowanie jest KLUCZOWE, żeby LineSeries nie rysowało prostych linii przez cały ekran
        std::sort(currentBuffer.begin(), currentBuffer.end(), [](const QPointF& a, const QPointF& b) {
            return a.x() < b.x();
        });
    }
    emit dataUpdated();
}

// void EEGModel::addBatch(const QMap<int, QVector<QPointF>> &batch)
// {
//     if (batch.isEmpty()) return;

//     // Logowanie dla diagnostyki
//     if(!batch.isEmpty() && !batch.first().isEmpty()) {
//         qDebug() << "Bieżacy X wysłany do QML: " << batch.first().last().x();
//     }

//     const double channelOffsetStep = 10.0;

//     for (auto it = batch.begin(); it != batch.end(); ++it) {
//         int ch = it.key();
//         QVector<QPointF> newPoints = it.value();

//         // 1. Zapamiętujemy pierwszy poziom sygnału (baseline) dla każdego kanału
//         if (!m_firstValues.contains(ch) && !newPoints.isEmpty()) {
//             m_firstValues[ch] = newPoints.first().y();
//             qDebug() << "Channel " << ch << " baseline set to:" << m_firstValues[ch];
//         }

//         double currentOffset = ch * channelOffsetStep;

//         for (QPointF &point : newPoints) {
//             // Pobierz baseline. Jeśli go nie ma, użyj aktualnego Y (wynik będzie 0)
//             double baseline = m_firstValues.value(ch, point.y());

//             double zeroedY = point.y() - baseline;

//             // Ustawienie punktu: (Sygnał * Skala) + Offset kanału
//             // Dodaj mnożnik 2.0 lub 5.0, jeśli sygnał jest zbyt płaski (mikrowolty są małe)
//             point.setY((zeroedY * 1.0) + currentOffset);
//         }

//         m_channelBuffers[ch].append(newPoints);

//         if(m_channelBuffers[ch].size() > m_maxSamplesPerChannle) {
//             int toRemove = m_channelBuffers[ch].size() - m_maxSamplesPerChannle;
//             m_channelBuffers[ch].remove(0, toRemove);
//         }
//     }

//     // Aktualizacja timestampu dla osi X
//     if(!batch.isEmpty() && !batch.first().isEmpty()) {
//         m_lastestTimestamp = batch.first().last().x();
//     }

//     emit dataUpdated();
// }
