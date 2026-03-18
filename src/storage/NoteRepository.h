#ifndef NOTEREPOSITORY_H
#define NOTEREPOSITORY_H

#include <QObject>
#include <QVariantMap>

#include "core/Note.h"
#include "IDatabaseManager.h"

class NoteRepository : public QObject
{
    Q_OBJECT
public:
    NoteRepository(IDatabaseManager *dataManager, QObject *parent = nullptr);
    bool addNote(const Note &n);

signals:
    void noteDataChanged();

private:
    IDatabaseManager *m_dataManager;
};

#endif // NOTEREPOSITORY_H
