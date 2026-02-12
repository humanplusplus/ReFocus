#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QString>

struct Participant
{
    int id = -1;
    QString nickname;
    QString gender;
    int birthYear = 0;
};

#endif // PARTICIPANT_H
