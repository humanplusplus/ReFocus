pragma Singleton
import QtQuick 2.15
import QtCharts 2.15
import EarEEG_DemoApp 1.0

QtObject {
    property string name: "blue"

    property QtObject colors: QtObject {
        // *** GENERAL SETTINGS ***
        property color backgroundColor: "#E1F8FD"
        property color linesColor:      "#0B2964"
        property color ribbonColor:     "#ABF8FA"

        // *** CARDS PROPERIES ***
        property color cardsBackgroundColor: "#ABF8FA"
        property color mediumRectangleBgColor: "#ABF8FA"
        property color smallRectangleBgColor: "#ABF8FA"

        // *** LIST PROPERIES ***
        property color listLineColor: "#0B2964"
        property color generalBorderColor: "#0B2964"

        // *** BUTTONS PROPERIES ***
        property color buttonBorderColor: "#0B2964"
        property color radioButtonCheckedColor: "#ABF8FA"
    }

    property QtObject fonts: QtObject {
        property string fontStyle: "Courier New"
        property int fontSize: 16
        property color fontColor: "#0B2964"
    }

    property QtObject radii: QtObject {
        property int radiusGeneral: 10
    }

    property QtObject charts: QtObject {
        // *** CHART SETTINGS ***
        property int chartTheme: ChartView.ChartThemeLight
    }

    property QtObject icons: QtObject {
        // *** ICONS SETTINGS & PATHS ***
        property real iconWidth: 30
        property real iconHeight: 30

        property string sideMenuIcon:       UiSettings.rootPath + "assets/themeBlueIcons/menu-bar.png"
        property string chartsIcon:         UiSettings.rootPath + "assets/themeBlueIcons/data-analysis.png"
        property string userIcon:           UiSettings.rootPath + "assets/themeBlueIcons/user.png"
        property string homeIcon:           UiSettings.rootPath + "assets/themeBlueIcons/house.png"
        property string logoutIcon:         UiSettings.rootPath + "assets/themeBlueIcons/logout.png"
        property string settingsIcon:       UiSettings.rootPath + "assets/themeBlueIcons/settings.png"
    }
}
