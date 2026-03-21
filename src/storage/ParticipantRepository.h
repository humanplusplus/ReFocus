#ifndef PARTICIPANTREPOSITORY_H
#define PARTICIPANTREPOSITORY_H

#include <QObject>

#include "core/Participant.h"
#include "IDatabaseManager.h"

class ParticipantRepository
{
public:
    ParticipantRepository(IDatabaseManager *dataManager);
    bool addParticipant(const Participant &p);
    QList<Participant> getAllParticipants();

signals:
    void userDataChanged();

private:
    IDatabaseManager *m_dataManager;
};

#endif // PARTICIPANTREPOSITORY_H
