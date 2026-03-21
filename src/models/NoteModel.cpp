#include "NoteModel.h"

NoteModel::NoteModel(NoteRepository *repo, QObject *parent)
    : QAbstractListModel(parent), m_repo(repo) {}

int NoteModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return m_items.size();
}

QVariant NoteModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_items.size())
        return {};

    const Note &n = m_items.at(index.row());

    switch (role) {
        case IdRole:            return n.id;
        case TimestampRole:     return n.contentTimestamp;
        case ContentRole:       return n.content;
        case MoodRatingRole:    return n.moodRating;
        case TagRole:           return n.tag;
        default:                return {};
    }
}

QHash<int, QByteArray> NoteModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TimestampRole] = "contentTimestamp";
    roles[ContentRole] = "contentRole";
    roles[MoodRatingRole] = "moodRating";
    roles[TagRole] = "tag";

    return roles;
}

void NoteModel::addNote(const QString &contentTimestamp, const QString &content, int moodRating, const QString &tag) {
    Note n;
    n.contentTimestamp = contentTimestamp;
    n.content = content;
    n.moodRating = moodRating;
    n.tag = tag;

    if(m_repo->addNote(n)) {
        beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
        m_items.append(n);
        endInsertRows();
        qDebug() << "Note add successfully.";
    } else {
        qWarning() << "Failed to add note.";
    }
}

void NoteModel::refresh() {
}

