#include "NoteRepository.h"
#include "storage/TableSchemasSQLite.h"

NoteRepository::NoteRepository(IDatabaseManager *dataManager, QObject *parent)
    : QObject(parent), m_dataManager(dataManager) {}

bool NoteRepository::addNote(const Note &n) {

    if (!m_dataManager) {
        qWarning() << "NoteRepository: Database manager is null!";
        return false;
    }

    QVariantMap data;
    data["content_timestamp"] = n.contentTimestamp;
    data["content"] = n.content;
    data["mood_rating"] = n.moodRating;
    data["tag"] = n.tag;

    bool success = m_dataManager->insertData(TableNamesSQLite::USER_NOTES, data);

    if (success) {
        qDebug() << "NoteRepository: Successfully inserted note.";
        emit noteDataChanged();
    } else {
        qWarning() << "NoteRepository: Failed to insert note into table" << TableNamesSQLite::USER_NOTES;
    }

    return success;
}
