#ifndef EEGSAMPLE_H
#define EEGSAMPLE_H

#include <QtGlobal>
#include <QVector>
#include <QString>

struct EEGSample
{
    qint64 timestamp; // Czas systemowy odbierania
    int sampleIndex; // Pierwsza kolumna w pliku csv
    QVector<double> channels; // Dane z EEG (np. 8 kanałów)
    QString phaseId; // Identyfikator fazy badania, pozwala odróżnić różne części eksperymentu np. OczyOtwarte, OczyZamkniete itp. Dzięki temu można łatwo odflitrować dane w bazie
    int event; // Znacznik konkretnego zdarzenia czasowego. Wykorzystuje się go do oznaczania momentów, w których wystąpił bodzieć, np. błysk światła, dźwięk lub kliknięcie przycisku. W analizie EEG pozwala to na wyliczenie tzw. Potencjałów Wywołanych (ERP)
    int label; // Etykieta klasy danych - najczęściej używana w ML. Jeżeli buduję aplikację, która ma rozpoznawać skupienie to etykieta przechowuje informację o stanie faktycznym (np. 0 = brak skupienia, 1 = pełne skupienie)
};

#endif // EEGSAMPLE_H
