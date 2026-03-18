#ifndef DATAPIPELINE_H
#define DATAPIPELINE_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QPointF>
#include <QMap>

#include <core/EEGSample.h>
#include "DatabaseManager.h"

class DataPipeline : public QObject
{
    Q_OBJECT
public:
    explicit DataPipeline(DatabaseManager *db, QObject *parent = nullptr);

    void setStartTime(qint64 startTime); // Metoda do ustawiania czasu startu, aby tx zaczynało się od 0

public slots:
    void onNewSampleReceived(const EEGSample &sample); // Slot podłączony bezpośrednio do źródła danych (np. CSVDataSource)
    void startProcessing();

signals:
    // Sygnał wysyłany do EEGModel: Mapa <IneksKanału, ListaPunktówX_Y>
    // QtGraphs uwielbia dostawać QVector<QPointF>, bo może te dane wrzucać prosto do pamięci karty graficznej (VBO)
    void batchReadyForUI(const QMap<int, QVector<QPointF>> &batch);

private slots:
    void flushBuffer();

private:
    DatabaseManager *m_db;
    QVector<EEGSample> m_buffer;
    QTimer *m_flushTimer;
    qint64 m_startTime = 0;
    const int m_uiRefreshRate = 33; // ~64Hz
};

#endif // DATAPIPELINE_H
