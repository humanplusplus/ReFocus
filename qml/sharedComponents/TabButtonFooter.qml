import QtQuick 2.15
import QtQuick.Controls.Material
import EarEEG_DemoApp 1.0

TabButton {
    id: componentTab

    property url stackViewPath
    property string iconPath
    property string labelText

    contentItem: Column {
        spacing: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            source: iconPath
            width: ThemeManager.icons.iconWidth
            height: ThemeManager.icons.iconHeight
            anchors.centerIn: parent
        }
    }

    Rectangle {
        width: componentTab.width
        height: 3
        color: ThemeManager.colors.linesColor
        anchors.bottom: componentTab.top
    }

    onClicked: {
        stackView.push(stackViewPath)
    }
}
