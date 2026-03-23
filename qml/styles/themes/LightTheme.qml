pragma Singleton
import QtQuick 2.15
import QtCharts 2.15
import EarEEG_DemoApp 1.0

QtObject {
    property string name: "light"

    property QtObject colors: QtObject {
        // *** GENERAL SETTINGS ***
        property color backgroundColor: "#FFFFFF"
        property color linesColor:      "#351D4D"
        property color ribbonColor:     "#E2E9EB"

        // *** CARDS PROPERIES ***
        property color cardsBackgroundColor: "#E2E9EB"
        property color mediumRectangleBgColor: "#E2E9EB"
        property color smallRectangleBgColor: "#E2E9EB"

        // *** LIST PROPERIES ***
        property color listLineColor: "#351D4D"
        property color generalBorderColor: "#351D4D"

        // *** BUTTONS PROPERIES ***
        property color buttonBorderColor: "#351D4D"
        property color radioButtonCheckedColor: "#E2E9EB"
    }

    property QtObject fonts: QtObject {
        property string fontStyle: "Courier New"
        property int fontSize: 16
        property color fontColor: "#351D4D"
    }

    property QtObject radii: QtObject {
        property int radiusGeneral: 10
    }

    property QtObject charts: QtObject {
        // *** CHART SETTINGS ***
        property int chartTheme: ChartView.ChartThemeDark
    }

    property QtObject icons: QtObject {
        // *** ICONS SETTINGS & PATHS ***
        property real iconWidth: 30
        property real iconHeight: 30

        property string sideMenuIcon:       UiSettings.rootPath + "assets/themeLightIcons/menu-bar.png"
        property string chartsIcon:         UiSettings.rootPath + "assets/themeLightIcons/data-analysis.png"
        property string userIcon:           UiSettings.rootPath + "assets/themeLightIcons/user.png"
        property string homeIcon:           UiSettings.rootPath + "assets/themeLightIcons/house.png"
        property string logoutIcon:         UiSettings.rootPath + "assets/themeLightIcons/logout.png"
        property string settingsIcon:       UiSettings.rootPath + "assets/themeLightIcons/settings.png"
    }
}
