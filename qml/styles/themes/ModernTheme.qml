pragma Singleton
import QtQuick 2.15
import QtCharts 2.15
import EarEEG_DemoApp 1.0

QtObject {
    property string name: "modern"

    property QtObject colors: QtObject {
        // *** GENERAL SETTINGS ***
        property color backgroundColor: "#EADCF7"
        property color linesColor:      "#41126F"
        property color ribbonColor:     "#9E49F3"

        // *** CARDS PROPERIES ***
        property color cardsBackgroundColor: "#9E49F3"
        property color mediumRectangleBgColor: "#9E49F3"
        property color smallRectangleBgColor: "#9E49F3"

        // *** LIST PROPERIES ***
        property color listLineColor: "#41126F"
        property color generalBorderColor: "#41126F"

        // *** BUTTONS PROPERIES ***
        property color buttonBorderColor: "#41126F"
        property color radioButtonCheckedColor: "#9E49F3"
    }

    property QtObject fonts: QtObject {
        property string fontStyle: "Courier New"
        property int fontSize: 16
        property color fontColor: "#280A47"
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

        property string sideMenuIcon:       UiSettings.rootPath + "assets/themeModernIcons/menu-bar.png"
        property string chartsIcon:         UiSettings.rootPath + "assets/themeModernIcons/data-analysis.png"
        property string userIcon:           UiSettings.rootPath + "assets/themeModernIcons/user.png"
        property string homeIcon:           UiSettings.rootPath + "assets/themeModernIcons/house.png"
        property string logoutIcon:         UiSettings.rootPath + "assets/themeModernIcons/logout.png"
        property string settingsIcon:       UiSettings.rootPath + "assets/themeModernIcons/settings.png"
    }
}
