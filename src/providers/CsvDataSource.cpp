#include <QDebug>
#include <QStringList>
#include <QDateTime>

#include "CsvDataSource.h"

CsvDataSource::CsvDataSource(const QString &filePath, QObject *parent)
    : IDataSource(parent), m_filePath(filePath), m_timer(nullptr) {}

CsvDataSource::~CsvDataSource()
{
    if (m_timer) {
        m_timer->stop();
        // m_timer->deleteLater();
    }
}

bool CsvDataSource::start()
{
    // 1. BEZPIECZNE TWORZENIE TIMERA
    // Jeśli timer nie istnieje, tworzymy go tutaj.
    // Ponieważ start() jest wywołane przez sygnał QThread::started,
    // timer zostanie stworzony w odpowiednim wątku roboczym.
    if (!m_timer) {
        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &CsvDataSource::readNextLine);
    }

    m_file.setFileName(m_filePath);
    if(!m_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Cannot open CSV file: " << m_filePath;
        return false;
    }

    // Pominięcie nagłówka i komentarzy
    while (!m_file.atEnd()) {
        qint64 pos = m_file.pos();
        QString line = m_file.readLine().trimmed();
        if(!line.startsWith('%') && !line.isEmpty()) {
            m_file.seek(pos);
            break;
        }
    }

    // Teraz m_timer na pewno nie jest nullem
    m_timer->start(1000 / m_frequency);
    qInfo() << "CSV Thread started reading:" << m_filePath;
    return true;
}

// bool CsvDataSource::start()
// {
//     // Jeśli timer nie ma rodzica, przypisujemy go teraz (jesteśmy już w Worker Thread)
//     if (m_timer && !m_timer->parent()) {
//         m_timer->setParent(this);
//         connect(m_timer, &QTimer::timeout, this, &CsvDataSource::readNextLine);
//     }

//     m_file.setFileName(m_filePath);
//     if(!m_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         qCritical() << "Cannot open CSV file: " << m_filePath;
//         return false;
//     }

//     // Pominięcie nagłówka i komentarzy
//     while (!m_file.atEnd()) {
//         qint64 pos = m_file.pos();
//         QString line = m_file.readLine().trimmed();
//         if(!line.startsWith('%') && !line.isEmpty()) {
//             m_file.seek(pos);
//             break;
//         }
//     }

//     m_timer->start(1000 / m_frequency);
//     qInfo() << "CSV Thread started reading:" << m_filePath;
//     return true;
// }

void CsvDataSource::stop()
{
    if (m_timer) m_timer->stop();
    if (m_file.isOpen()) m_file.close();
    qInfo() << "CSV Thread stopped.";
}

void CsvDataSource::readNextLine()
{
    if(m_file.atEnd()) {
        stop();
        return;
    }

    QString line = m_file.readLine().trimmed();
    if (line.isEmpty()) return;

    QStringList parts = line.split(',');
    if (parts.size() < 9) return;

    EEGSample sample;
    // Używamy czasu systemowego o wysokiej precyzji
    sample.timestamp = QDateTime::currentMSecsSinceEpoch();
    sample.sampleIndex = parts[1].toInt();

    // Pobieranie 8 kanałów EEG
    for(int i = 2; i <= 9; ++i) {
        sample.channels.append(parts[i].toDouble());
    }

    // Dodatkowe metadane (jeśli są)
    if (parts.size() > 19) {
        sample.phaseId = parts[17];
        sample.event = parts[18].toInt();
        sample.label = parts[19].toInt();
    }

    emit dataReceived(sample);
}
