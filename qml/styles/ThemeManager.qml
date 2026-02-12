pragma Singleton
import QtQuick 2.15
import QtCharts 2.15
import Qt.labs.settings 1.1
import EarEEG_DemoApp 1.0

Item {
    id: root

    Settings {
        id: appSettings
        category: "Appearance"
        property string selectedTheme: "dark"
    }

    property var availableThemes: ({
        "dark": DarkTheme,
        "light": LightTheme,
        "modern": ModernTheme,
        "blue": BlueTheme
    })

    property var currentTheme: availableThemes[appSettings.selectedTheme] ?? BlueTheme

    function setTheme(name) {
        if (!availableThemes[name]) {
            console.warn("Unknown theme:", name)
            return
        }
        currentTheme = availableThemes[name]
        appSettings.selectedTheme = name
    }

    property var colors: currentTheme.colors
    property var icons: currentTheme.icons
    property var radii: currentTheme.radii
    property var charts: currentTheme.charts
    property var fonts: currentTheme.fonts
}
