#include <QDebug>

#include "UserModel.h"

UserModel::UserModel(UserRepository* repo, QObject* parent)
    : QObject(parent), m_repo(repo) {}

bool UserModel::registerUser(const QString& username, const QString& password) {
    return m_repo->registerUser(username, password);
}

bool UserModel::loginUser(const QString& username, const QString& password) {
    if (m_repo->authenticate(username, password)) {
        auto user = m_repo->getUser(username);
        m_currentUser = user.username;
        m_role = user.role;
        emit loginSuccess(username);
        return true;
    } else {
        emit loginFailed("Invalid credentials");
        return false;
    }
}

QString UserModel::currentUserRole() const {
    return m_role;
}
