pragma Singleton
import QtQuick 2.15
import QtCharts 2.15
import EarEEG_DemoApp 1.0

QtObject {
    property string name: "dark"

    property QtObject colors: QtObject {
        // *** GENERAL SETTINGS ***
        property color backgroundColor: "#0A0A0A"
        property color linesColor:      "#000000"
        property color ribbonColor:     "#000007"

        // *** CARDS PROPERIES ***
        property color cardsBackgroundColor: "#000000"
        property color mediumRectangleBgColor: "#161617"
        property color smallRectangleBgColor: "#222224"

        // *** LIST PROPERIES ***
        property color listLineColor: "#000000"
        property color generalBorderColor: "#000000"

        // *** BUTTONS PROPERIES ***
        property color buttonBorderColor: "#000000"
        property color radioButtonCheckedColor: "#000000"
    }

    property QtObject fonts: QtObject {
        property string fontStyle: "Courier New"
        property int fontSize: 16
        property color fontColor: "#ECECF6"
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

        property string sideMenuIcon:       UiSettings.rootPath + "assets/themeDarkIcons/menu-bar.png"
        property string chartsIcon:         UiSettings.rootPath + "assets/themeDarkIcons/data-analysis.png"
        property string userIcon:           UiSettings.rootPath + "assets/themeDarkIcons/user.png"
        property string homeIcon:           UiSettings.rootPath + "assets/themeDarkIcons/house.png"
        property string eegImageIcon:       UiSettings.rootPath + "assets/themeDarkIcons/eeg-image.png"
        property string logoutIcon:         UiSettings.rootPath + "assets/themeDarkIcons/logout.png"
        property string settingsIcon:       UiSettings.rootPath + "assets/themeDarkIcons/settings.png"
    }
}
