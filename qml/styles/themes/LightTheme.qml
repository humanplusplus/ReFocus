pragma Singleton
import QtQuick 2.15
import QtCharts 2.15
import EarEEG_DemoApp 1.0

QtObject {
    property string name: "light"

    property QtObject colors: QtObject {
        // *** GENERAL SETTINGS ***
        property color backgroundColor: "#FFFFFF"
        property color linesColor:      "#a6dced"
        property color ribbonColor:     "#a6dced"

        // *** CARDS PROPERIES ***
        property color cardsBackgroundColor: "#a6dced"
        property color mediumRectangleBgColor: "#a6dced"
        property color smallRectangleBgColor: "#a6dced"

        // *** LIST PROPERIES ***
        property color listLineColor: "#a6dced"
        property color generalBorderColor: "#a6dced"

        // *** BUTTONS PROPERIES ***
        property color buttonBorderColor: "#a6dced"
        property color radioButtonCheckedColor: "#a6dced"
    }

    property QtObject fonts: QtObject {
        property string fontStyle: "Courier New"
        property int fontSize: 16
        property color fontColor: "#000000"
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
