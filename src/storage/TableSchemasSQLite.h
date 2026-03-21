#ifndef TABLESCHEMASSQLITE_H
#define TABLESCHEMASSQLITE_H

#include <QString>
#include <QVector>

namespace TableNamesSQLite {
    constexpr const char* SETTINGS          = "settings";
    constexpr const char* USERS             = "users"; // dane użytkownika zalogowanego do aplikacji
    constexpr const char* PARTICIPANTS      = "participants"; // dane użytkownika, który brał udział w badaniu
    constexpr const char* USER_NOTES        = "user_notes";
    constexpr const char* EEG_EVENTS        = "eeg_events"; // opisuje momenty bodźców lub reakcji w czasie np. reakcje, kliknięcia, sygnały z Psychopy
    constexpr const char* EEG_FEAUTERS      = "eeg_feauters"; // przechowuje metryki wyliczone z EEG np. alpha power
    constexpr const char* EEG_SESSIONS      = "eeg_sessions"; // jedna sesja nagrania - powiązana sesja EEG z konkretnym użytkownikiem
}

namespace TableSchemasSQLite {

    inline const QString CREATE_SETTINGS_TABLE = QStringLiteral(R"(
        CREATE TABLE IF NOT EXISTS %1 (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            key TEXT UNIQUE NOT NULL,
            value TEXT NOT NULL,
            created_at TEXT DEFAULT (datetime('now')),
            updated_at TEXT DEFAULT (datetime('now'))
            );
    )").arg(TableNamesSQLite::SETTINGS);

    inline const QString CREATE_USERS_TABLE = QStringLiteral(R"(
        CREATE TABLE IF NOT EXISTS %1 (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            role TEXT DEFAULT 'user',        -- np. 'admin', 'researcher', 'participant'
            last_login TEXT,
            created_at TEXT DEFAULT (datetime('now')),
            updated_at TEXT DEFAULT (datetime('now')),
            synced INTEGER DEFAULT 0,
            synced_at TEXT
            );
    )").arg(TableNamesSQLite::USERS);


    inline const QString CREATE_PARTICIPANTS_TABLE = QStringLiteral(R"(
        CREATE TABLE IF NOT EXISTS %1 (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER,
            nickname TEXT UNIQUE NOT NULL,
            birth_year INTEGER NOT NULL,
            gender TEXT,
            created_at TEXT DEFAULT (datetime('now')),
            updated_at TEXT DEFAULT (datetime('now')),
            synced INTEGER DEFAULT 0,
            synced_at TEXT,
            FOREIGN KEY(user_id) REFERENCES users(id)
        )
    )").arg(TableNamesSQLite::PARTICIPANTS);

    inline const QString CREATE_USER_NOTES_TABLE = QStringLiteral(R"(
        CREATE TABLE IF NOT EXISTS %1 (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            content_timestamp TEXT NOT NULL,
            content TEXT NOT NULL,
            mood_rating INTEGER,
            tag TEXT,
            created_at TEXT DEFAULT (datetime('now')),
            updated_at TEXT DEFAULT (datetime('now')),
            synced INTEGER DEFAULT 0,
            synced_at TEXT
            );
    )").arg(TableNamesSQLite::USER_NOTES);

    inline const QString CREATE_EEG_EVENTS_TABLE = QStringLiteral(R"(
        CREATE TABLE IF NOT EXISTS %1 (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            uuid TEXT UNIQUE NOT NULL,
            onset REAL,
            duration REAL,
            value TEXT,
            trial_type TEXT,
            session_id INTEGER NOT NULL,
            created_at TEXT DEFAULT (strftime('%Y-%m-%d %H:%M;%f', 'now')),
            updated_at TEXT DEFAULT (strftime('%Y-%m-%d %H:%M;%f', 'now')),
            synced INTEGER DEFAULT 0,
            synced_at TEXT,
            FOREIGN KEY(session_id) REFERENCES %2(id)
        )
    )").arg(TableNamesSQLite::EEG_EVENTS, TableNamesSQLite::EEG_SESSIONS);

    inline const QString CREATE_EEG_FEAUTERS_TABLE = QStringLiteral(R"(
        CREATE TABLE IF NOT EXISTS %1 (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            uuid TEXT UNIQUE NOT NULL,
            channel INTEGER,
            alpha_power REAL,
            beta_power REAL,
            theta_power REAL,
            total_power REAL,
            correlation_env REAL,
            session_id INTEGER NOT NULL,
            created_at TEXT DEFAULT (datetime('now')),
            updated_at TEXT DEFAULT (datetime('now')),
            synced INTEGER DEFAULT 0,
            synced_at TEXT,
            FOREIGN KEY(session_id) REFERENCES %2(id)
        )
    )").arg(TableNamesSQLite::EEG_FEAUTERS, TableNamesSQLite::EEG_SESSIONS);

    inline const QString CREATE_EEG_SESSIONS_TABLE = QStringLiteral(R"(
        CREATE TABLE IF NOT EXISTS %1 (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            uuid TEXT UNIQUE NOT NULL,
            device TEXT,
            task_name TEXT,
            start_time REAL,
            end_time REAL,
            sampling_rate REAL,
            n_channels INTEGER,
            participant_id INTEGER NOT NULL,
            created_at TEXT DEFAULT (datetime('now')),
            updated_at TEXT DEFAULT (datetime('now')),
            synced INTEGER DEFAULT 0,
            synced_at TEXT,
            FOREIGN KEY(participant_id) REFERENCES %2(id)
        )
    )").arg(TableNamesSQLite::EEG_SESSIONS, TableNamesSQLite::PARTICIPANTS);

    // Zwracamy wszystkie CREATE TABLES
    inline const QStringList& createAllTables() {
        static const QStringList createAllTbl = {
            CREATE_SETTINGS_TABLE,
            CREATE_USERS_TABLE,
            CREATE_PARTICIPANTS_TABLE,
            CREATE_USER_NOTES_TABLE,
            CREATE_EEG_SESSIONS_TABLE,
            CREATE_EEG_EVENTS_TABLE,
            CREATE_EEG_FEAUTERS_TABLE
        };
        return createAllTbl;
    }
}

#endif // TABLESCHEMASSQLITE_H

