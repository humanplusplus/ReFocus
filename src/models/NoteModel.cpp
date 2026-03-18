#include "NoteModel.h"

NoteModel::NoteModel(NoteRepository *repo, QObject *parent)
    : QAbstractListModel(parent),
    m_repo(repo)
{}

int NoteModel::rowCount(const QModelIndex &) const {
    return m_items.size();
}

QVariant NoteModel::data(const QModelIndex &index, int role) const {
    QVariant();
}

QHash<int, QByteArray> NoteModel::roleNames() const {
    return {
        { IdRole, "id" },
        { TimestampRole, "contentTimestamp" },
        { ContentRole, "contentRole" },
        { MoodRatingRole, "moodRating" },
        { TagRole, "tag" }
    };
}

void NoteModel::addNote(const QString &contentTimestamp, const QString &content, int moodRating, const QString &tag)
{
    Note n;
    n.contentTimestamp = contentTimestamp;
    n.content = content;
    n.moodRating = moodRating;
    n.tag = tag;

    if(m_repo->addNote(n)) {
        qDebug() << "Note add successfully.";
    } else {
        qWarning() << "Failed to add note.";
    }
}

void NoteModel::refresh()
{

}

