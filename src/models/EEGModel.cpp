#include "EEGModel.h"

EEGModel::EEGModel(QObject *parent) : QObject(parent) {}

void EEGModel::addBatch(const QMap<int, QVector<QPointF>> &batch) {

    if (batch.isEmpty()) return;

    const double offsetStep = 100.0;

    for (auto it = batch.begin(); it != batch.end(); ++it) {
        int ch = it.key();
        QVector<QPointF> incomingPoints = it.value();

        for (const QPointF &p : incomingPoints) {
            // 1. Obliczamy pozycję X w oknie 0-5s
            double xPos = fmod(p.x(), m_windowSize);

            // 2. Dodajemy do historii (używamy y z batcha, który jest już wycentrowany)
            m_fullHistory[ch].append(QPointF(xPos, p.y() + (ch * offsetStep)));

            // 3. Ograniczamy historię (utrzymujemy nieco więcej niż mieści się w oknie)
            if (m_fullHistory[ch].size() > m_maxSamplesPerChannel) {
                m_fullHistory[ch].remove(0, m_fullHistory[ch].size() - m_maxSamplesPerChannel);
            }
        }
    }

    // Zapamiętujemy ostatni czas do pozycjonowania kursora
    m_latestTimestamp = batch.first().last().x();
    emit dataUpdated();
}

QVector<QPointF> EEGModel::getLeadingPoints(int ch) const {

    QVector<QPointF> points;
    double currentX = fmod(m_latestTimestamp, m_windowSize);

    for (const QPointF &p : m_fullHistory.value(ch)) {
        if (p.x() <= currentX) points.append(p);
    }
    std::sort(points.begin(), points.end(), [](const QPointF &a, const QPointF &b) { return a.x() < b.x(); });
    return points;
}

QVector<QPointF> EEGModel::getTrailingPoints(int ch) const {

    QVector<QPointF> points;
    double currentX = fmod(m_latestTimestamp, m_windowSize);
    double gapEdge = currentX + m_gapSize;

    for (const QPointF &p : m_fullHistory.value(ch)) {
        if (gapEdge < m_windowSize) {
            if (p.x() > gapEdge) points.append(p);
        } else {
            // Jeśli gap zawija się na początek okna
            if (p.x() > gapEdge - m_windowSize && p.x() < currentX) {
                // pomin punkt
            } else if (p.x() > currentX && p.x() < gapEdge) {
                // pomin punkt
            } else {
                // to specyficzny przypadek przy samym końcu okna
            }
        }
    }
    std::sort(points.begin(), points.end(), [](const QPointF &a, const QPointF &b) { return a.x() < b.x(); });
    return points;
}

void EEGModel::clear() {
    m_fullHistory.clear();
    m_latestTimestamp = 0;
    emit dataUpdated();
}
