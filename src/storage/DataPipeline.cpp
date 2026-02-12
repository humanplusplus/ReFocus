#include <qpoint.h>

#include "DataPipeline.h"

DataPipeline::DataPipeline(DatabaseManager *db, QObject *parent)
    : QObject(parent), m_db(db), m_flushTimer(new QTimer(this))
{
    connect(m_flushTimer, &QTimer::timeout, this, &DataPipeline::flushBuffer);
    m_flushTimer->start(m_uiRefreshRate);
}

void DataPipeline::onNewSampleReceived(const EEGSample &sample)
{
    // Jeśli to pierwsza próbka w historii zapisz jej czas jako t0
    if (m_startTime == 0) {
        m_startTime = sample.timestamp;
        qDebug() << "Pipeline started at:" << m_startTime;
    }
    m_buffer.append(sample);
}

void DataPipeline::flushBuffer()
{
    if(m_buffer.isEmpty()) return;

    // Przygotuj kontener na dane dla 8 kanałów
    QMap<int, QVector<QPointF>> batchForUI;
    double gain = 100;

    for(const auto& sample : m_buffer) {
        // Obliczamy czas w sekundach od startu (oś X)
        double tx = static_cast<double>(sample.timestamp - m_startTime) / 1000.0;
        for(int ch = 0; ch < sample.channels.size(); ++ch) {
            // Dodajemy punkt (Czas, Amplituda) dla konkretnego kanału
            batchForUI[ch].append(QPointF(tx, sample.channels[ch] * gain));
        }
    }

    // Wysyłamy gotową paczkę do EEGModel
    emit batchReadyForUI(batchForUI);

    // Opcjonalnie:: Tutaj można dodać logikę zapisu do bazy

    m_buffer.clear();
}
