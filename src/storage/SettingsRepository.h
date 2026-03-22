#ifndef SETTINGSREPOSITORY_H
#define SETTINGSREPOSITORY_H

#include <QObject>
#include <QVariant>
//#include <QVariantMap>

#include "IDatabaseManager.h"

class SettingsRepository : public QObject {
    Q_OBJECT
public:
    SettingsRepository(IDatabaseManager *dataManager, QObject *parent = nullptr);
    Q_INVOKABLE bool upsertSettings(const QString &key, const QVariant &value);
    Q_INVOKABLE QVariant getSettingValue(const QString &key, const QVariant &defaultValue = QVariant());
    // Q_INVOKABLE  QVariantMap getAllSettings(); -> do wykorzystania jeżeli będzie potrzeba pobierania kilku rekordów

signals:
    void settingsDataChanged();

private:
    IDatabaseManager *m_dataManager;
};

#endif // SETTINGSREPOSITORY_H
