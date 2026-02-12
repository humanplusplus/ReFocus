#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <QObject>

#include "IDatabaseManager.h"
#include "core/User.h"

class UserRepository : public QObject {
    Q_OBJECT
public:
    explicit UserRepository(IDatabaseManager* dataManager, QObject* parent = nullptr);

    bool registerUser(const QString& username, const QString& password);
    bool authenticate(const QString& username, const QString& password);
    User getUser(const QString& username);
    bool updateLastLogin(const QString& username);

private:
    IDatabaseManager* m_dataManager;
    QString hashPassword(const QString& password);
};

#endif // USERREPOSITORY_H
