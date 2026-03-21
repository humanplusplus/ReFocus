#include <QDebug>

#include "ParticipantModel.h"

ParticipantModel::ParticipantModel(ParticipantRepository *repo, QObject *parent)
    : QAbstractListModel(parent),
    m_repo(repo)
{
    refresh();
}

int ParticipantModel::rowCount(const QModelIndex &) const {
    return m_items.size();
}

QVariant ParticipantModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_items.size())
        return QVariant();

    const Participant &p = m_items[index.row()];

    switch (role) {
        case IdRole: return p.id;
        case NicknameRole: return p.nickname;
        case GenderRole: return p.gender;
        case BirthYearRole: return p.birthYear;
        default: return QVariant();
    }
}

QHash<int, QByteArray> ParticipantModel::roleNames() const {
    return {
        { IdRole, "id" },
        { NicknameRole, "nickname" },
        { GenderRole, "gender" },
        { BirthYearRole, "birth_year" }
    };
}

void ParticipantModel::refresh() {
    beginResetModel();
    m_items = m_repo->getAllParticipants();
    endResetModel();

    emit userDataChanged();
}

QVariantMap ParticipantModel::getUserDetails() {
    QVariantMap map;

    if (m_items.isEmpty()) {
        qDebug() << "No user data available.";
        return map;
    }

    const Participant &p = m_items.first();
    map["id"] = p.id;
    map["nickname"] = p.nickname;
    map["gender"] = p.gender;
    map["birth_year"] = p.birthYear;

    return map;
}

void ParticipantModel::upsertUser(const QString &nickname,
                                  const QString &gender,
                                  int birthYear)
{
    Participant p;
    p.nickname = nickname;
    p.gender = gender;
    p.birthYear = birthYear;

    if (m_repo->addParticipant(p)) {
        qDebug() << "User upserted successfully.";
        refresh();
    } else {
        qWarning() << "Failed to upsert user.";
    }
}
