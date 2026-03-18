#ifndef NOTE_H
#define NOTE_H

#include <QObject>
#include <QString>
#include <QDateTime>

struct Note {
    int id = -1;
    QString contentTimestamp;
    QString content;
    int moodRating = 0;
    QString tag;

    Note() = default;
};

#endif // NOTE_H
