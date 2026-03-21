#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>

#include "storage/UserRepository.h"

class UserModel : public QObject {
    Q_OBJECT

public:
    explicit UserModel(UserRepository* repo, QObject* parent = nullptr);

    Q_INVOKABLE bool registerUser(const QString& username, const QString& password);
    Q_INVOKABLE bool loginUser(const QString& username, const QString& password);
    Q_INVOKABLE QString currentUserRole() const;

signals:
    void loginSuccess(const QString& username);
    void loginFailed(const QString& reason);

private:
    UserRepository* m_repo;
    QString m_currentUser;
    QString m_role;
};

#endif // USERMODEL_H
