import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material
import EarEEG_DemoApp 1.0

Label {
    width: parent.width

    property string labelText
    property bool textBold: false
    property real textSize: ThemeManager.fonts.fontSize
    property color textColor: ThemeManager.fonts.fontColor

    horizontalAlignment: Text.AlignLeft
    text: labelText
    font.pixelSize: textSize
    font.bold: textBold
    color: textColor
}
