#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>

#include "UserRepository.h"

UserRepository::UserRepository(IDatabaseManager* dataManager, QObject* parent)
    : QObject(parent), m_dataManager(dataManager) {}

QString UserRepository::hashPassword(const QString& password) {
    QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashed.toHex());
}

bool UserRepository::registerUser(const QString& username, const QString& password) {
    if (!m_dataManager) {
        qWarning() << "Data manager is null!";
        return false;
    }

    // --- 1️⃣ sprawdź czy użytkownik już istnieje ---
    QString safeUsername = username;
    safeUsername.replace("'", "''");

    QString query = QString("SELECT username FROM users WHERE username = '%1'")
                        .arg(safeUsername);

    auto rows = m_dataManager->queryData(query);
    if (!rows.isEmpty()) {
        qWarning() << "User already exists:" << username;
        return false;
    }

    // --- 2️⃣ wstaw nowego użytkownika ---
    QVariantMap data;
    data["username"] = username;
    data["password_hash"] = hashPassword(password);
    data["role"] = "user";
    data["created_at"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    data["last_login"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    bool success = m_dataManager->insertData("users", data);
    if (!success)
        qWarning() << "Failed to insert new user into DB.";

    return success;
}

bool UserRepository::authenticate(const QString& username, const QString& password) {
    if (!m_dataManager) {
        qWarning() << "Data manager is null!";
        return false;
    }

    // --- 1️⃣ zabezpiecz dane wejściowe ---
    QString safeUsername = username;
    safeUsername.replace("'", "''");

    // --- 2️⃣ znajdź użytkownika w bazie ---
    QString query = QString("SELECT password_hash FROM users WHERE username = '%1'")
                        .arg(safeUsername);
    auto rows = m_dataManager->queryData(query);

    if (rows.isEmpty()) {
        qWarning() << "User not found:" << username;
        return false;
    }

    // --- 3️⃣ porównaj hasła ---
    QString storedHash = rows.first()["password_hash"].toString();
    if (storedHash != hashPassword(password)) {
        qWarning() << "Invalid password for user:" << username;
        return false;
    }

    // --- 4️⃣ aktualizuj last_login po sukcesie ---
    updateLastLogin(username);

    qDebug() << "Authentication successful for user:" << username;
    return true;
}

User UserRepository::getUser(const QString& username) {
    User user; // 🔹 brakowało tej zmiennej!
    if (!m_dataManager) {
        qWarning() << "Data manager is null!";
        return user;
    }

    QString safeUsername = username;
    safeUsername.replace("'", "''");

    QString query = QString("SELECT id, username, role, last_login FROM users WHERE username = '%1'")
                        .arg(safeUsername);

    auto rows = m_dataManager->queryData(query);
    if (!rows.isEmpty()) {
        const auto &r = rows.first();
        user.id = r["id"].toInt();
        user.username = r["username"].toString();
        user.role = r["role"].toString();
        user.lastLogin = r["last_login"].toString();
    } else {
        qWarning() << "User not found for getUser():" << username;
    }

    return user;
}

bool UserRepository::updateLastLogin(const QString& username) {
    if (!m_dataManager) {
        qWarning() << "Data manager is null!";
        return false;
    }

    QVariantMap update;
    update["username"] = username;
    update["last_login"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    bool success = m_dataManager->updateData("users", update, "username");
    if (!success)
        qWarning() << "Failed to update last_login for" << username;

    return success;
}
