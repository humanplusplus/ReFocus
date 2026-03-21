#ifndef PARTICIPANTMODEL_H
#define PARTICIPANTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QVariantMap>

#include "core/Participant.h"
#include "storage/ParticipantRepository.h"

class ParticipantModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        NicknameRole,
        GenderRole,
        BirthYearRole
    };
    Q_ENUM(Roles)

    explicit ParticipantModel(ParticipantRepository *repo, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QVariantMap getParticipantDetails();
    Q_INVOKABLE void upsertParticipant(const QString &nickname, const QString &gender, int birthYear);

    Q_INVOKABLE void refresh();

signals:
    void participantDataChanged();

private:
    QList<Participant> m_items;
    ParticipantRepository *m_repo;
};



#endif // PARTICIPANTMODEL_H
