import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material
import EarEEG_DemoApp 1.0

TextArea {
    property string innerText: ""
    property int textLines: 4

    implicitHeight: 40 * textLines
    width: parent.width
    height: implicitHeight

    wrapMode: TextEdit.Wrap
    selectByMouse: true

    leftPadding: 15
    rightPadding: 15
    topPadding: 10
    bottomPadding: 10

    // Synchronizacja danych
    onTextChanged: {
        if (innerText !== text) innerText = text
    }
    onInnerTextChanged: {
        if (text !== innerText) text = innerText
    }

    font.pixelSize: ThemeManager.fonts.fontSize
    color: ThemeManager.fonts.fontColor
    placeholderTextColor: Qt.rgba(color.r, color.g, color.b, 0.3)

    background: Rectangle {
        radius: 21
        color: ThemeManager.colors.mediumRectangleBgColor
        border.color:  ThemeManager.colors.linesColor
        border.width: 1
    }
}
