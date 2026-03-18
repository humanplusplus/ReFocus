#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QVariantMap>

#include "core/Note.h"
#include "storage/NoteRepository.h"

class NoteModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TimestampRole,
        ContentRole,
        MoodRatingRole,
        TagRole
    };
    Q_ENUM(Roles);

    explicit NoteModel(NoteRepository *repo, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addNote(const QString &contentTimestamp, const QString &content, int moodRating, const QString &tag);
    Q_INVOKABLE void refresh();

private:
    QList<Note> m_items;
    NoteRepository *m_repo;

};

#endif // NOTEMODEL_H
