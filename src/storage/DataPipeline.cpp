#include <QThread>
#include <QPoint>

#include "DataPipeline.h"

DataPipeline::DataPipeline(DatabaseManager *db, QObject *parent)
    : QObject(parent), m_db(db), m_flushTimer(nullptr) {
    // connect(m_flushTimer, &QTimer::timeout, this, &DataPipeline::flushBuffer);
    // m_flushTimer->start(m_uiRefreshRate);
}

void DataPipeline::setStartTime(qint64 startTime) {
    m_startTime = startTime;
}

void DataPipeline::onNewSampleReceived(const EEGSample &sample) {
    // Jeśli to pierwsza próbka w historii zapisz jej czas jako t0
    if (m_startTime == 0) {
        m_startTime = sample.timestamp;
        qDebug() << "Pipeline started at: " << m_startTime;
    }
    m_buffer.append(sample);
}

void DataPipeline::startProcessing() {
    if (!m_flushTimer) {
        m_flushTimer = new QTimer(this);
        connect(m_flushTimer, &QTimer::timeout, this, &DataPipeline::flushBuffer);
        m_flushTimer->start(m_uiRefreshRate);
        qInfo() << "DataPipeline processing started in thread:" << QThread::currentThreadId();
    }
}

void DataPipeline::flushBuffer() {
    if(m_buffer.isEmpty()) return;

    // Przygotuj kontener na dane dla 8 kanałów
    QMap<int, QVector<QPointF>> batchForUI;

    // liczenie średniej na każdym kanale
    QVector<double> avg(8, 0.0);
    int n = m_buffer.size();
    for (const auto &sample : m_buffer)
        for (int ch = 0; ch < sample.channels.size(); ++ch)
            avg[ch] += sample.channels[ch];

    for (int ch = 0; ch < avg.size(); ++ch)
        avg[ch] /= n;

    double gain = 1.0;

    for(const auto& sample : m_buffer) {
        // Obliczamy czas w sekundach od startu (oś X)
        double tx = static_cast<double>(sample.timestamp - m_startTime) / 1000.0;
        for(int ch = 0; ch < sample.channels.size(); ++ch) {
            // Dodajemy punkt (Czas, Amplituda) dla konkretnego kanału
            double centered = sample.channels[ch] - avg[ch];
            batchForUI[ch].append(QPointF(tx, centered * gain));
        }
    }

    // Wysyłamy gotową paczkę do EEGModel
    emit batchReadyForUI(batchForUI);
    m_buffer.clear();
}
