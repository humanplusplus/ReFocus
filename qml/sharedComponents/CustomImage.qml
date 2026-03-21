import QtQuick 2.15
import EarEEG_DemoApp 1.0

Image {
    anchors.verticalCenter: parent.verticalCenter

    property string iconPath
    property bool iconVisible: true
    property real widthMultiplier: 1
    property real heightMultiplier: 1

    width: ThemeManager.icons.iconWidth * widthMultiplier
    height: ThemeManager.icons.iconHeight * heightMultiplier
    visible: iconVisible
    source: iconPath
}
