#ifndef PARTICIPANTREPOSITORY_H
#define PARTICIPANTREPOSITORY_H

#include <QObject>
#include <QVariantMap>

#include "core/Participant.h"
#include "IDatabaseManager.h"

class ParticipantRepository : public QObject {
    Q_OBJECT
public:
    ParticipantRepository(IDatabaseManager *dataManager, QObject *parent = nullptr);
    bool addParticipant(const Participant &p);
    QList<Participant> getAllParticipants();

signals:
    void participantDataChanged();

private:
    IDatabaseManager *m_dataManager;
};

#endif // PARTICIPANTREPOSITORY_H
