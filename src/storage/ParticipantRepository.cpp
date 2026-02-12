#include <QVariantMap>
#include <QDateTime>
#include <QDebug>

#include "ParticipantRepository.h"
#include "TableSchemasSQLite.h"

ParticipantRepository::ParticipantRepository(IDatabaseManager *dataManager)
    : m_dataManager(dataManager) {}

bool ParticipantRepository::addParticipant(const Participant &p)
{
    // 🔍 Sprawdź, czy istnieje już rekord użytkownika
    QString checkQuery = QString("SELECT id, created_at FROM %1 LIMIT 1")
                             .arg(TableNamesSQLite::PARTICIPANTS);
    auto rows = m_dataManager->queryData(checkQuery);

    QVariantMap data;
    data["nickname"] = p.nickname;
    data["gender"] = p.gender;
    data["birth_year"] = p.birthYear;
    data["updated_at"] = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    data["synced"] = 0;

    if (!rows.isEmpty()) {
        // 🔁 Rekord istnieje → aktualizacja
        int existingId = rows.first()["id"].toInt();
        data["id"] = existingId;  // potrzebne dla update po keyColumn=id
        return m_dataManager->updateData(TableNamesSQLite::PARTICIPANTS, data, "id");
    }

    // 🟢 Brak rekordu → pierwszy INSERT
    data["created_at"] = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    return m_dataManager->insertData(TableNamesSQLite::PARTICIPANTS, data);
}

QList<Participant> ParticipantRepository::getAllParticipants()
{
    QList<Participant> result;
    QString query = QString("SELECT * FROM %1").arg(TableNamesSQLite::PARTICIPANTS);
    auto rows = m_dataManager->queryData(query);

    for (auto &r : rows) {
        Participant p;
        p.id = r["id"].toInt();
        p.nickname = r["nickname"].toString();
        p.gender = r["gender"].toString();
        p.birthYear = r["birth_year"].toInt();
        result.append(p);
    }
    return result;
}
