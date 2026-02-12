import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material
import EarEEG_DemoApp 1.0

Button {
    width: 120

    property string buttonText: "Confirm"
    property color innerColor: ThemeManager.colors.cardsBackgroundColor
    property color borderColor: ThemeManager.colors.linesColor
    property bool fontBold: false
    property real fontMultiplier: 1
    property real rectangleHeightMultiplier: 1
    property real rectangleWidthMultiplier: 1

    background: Rectangle {
        width: parent.width * rectangleWidthMultiplier
        height: 40 * rectangleHeightMultiplier
        radius: 21
        color: innerColor
        border.color: borderColor
        border.width: 1
    }

    contentItem: Text {
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.fill: parent
        text: buttonText
        color: ThemeManager.fonts.fontColor
        font.pixelSize: ThemeManager.fonts.fontSize * fontMultiplier
        font.bold: fontBold
    }
}
