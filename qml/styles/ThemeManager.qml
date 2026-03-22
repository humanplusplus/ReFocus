pragma Singleton
import QtQuick 2.15
import QtCharts 2.15
import Qt.labs.settings 1.1
import EarEEG_DemoApp 1.0

Item {
    id: root

    readonly property string themeKey: "selected_theme";

    property var availableThemes: ({
        "Dark": DarkTheme,
        "Light": LightTheme,
        "Modern": ModernTheme,
        "Blue": BlueTheme
    })

    property string activeThemeName: "Dark"
    readonly property var currentTheme: availableThemes[activeThemeName]

    property var colors: currentTheme.colors
    property var icons: currentTheme.icons
    property var radii: currentTheme.radii
    property var charts: currentTheme.charts
    property var fonts: currentTheme.fonts

    Component.onCompleted: {
        refreshTheme();
    }

    function refreshTheme() {
        let saved = settingsRepo.getSettingValue(themeKey, activeThemeName)
        if (saved && availableThemes[saved]) {
            activeThemeName = saved
        }
    }

    function setTheme(name) {
        if (availableThemes[name]) {
            activeThemeName = name
            settingsRepo.upsertSettings(themeKey, name)
            console.log("Saved new theme: ", name)
        }
    }
}
