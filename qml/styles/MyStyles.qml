// https://www.rapidtables.com/web/color/RGB_Color.html

pragma Singleton
import QtQuick
import QtCharts 2.15
import EarEEG_DemoApp 1.0

QtObject {
    property string exampleChartImage:  UiSettings.rootPath + "assets/example-eegchart-with4channels.png"
    property string earEegImage:        UiSettings.rootPath + "assets/EarEEG.png"
    property string earEeg2Image:       UiSettings.rootPath + "assets/EarEEG2.png"
    property string assetsPath:         UiSettings.rootPath + "assets/"
}
