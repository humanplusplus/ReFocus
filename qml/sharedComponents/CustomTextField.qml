import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material
import EarEEG_DemoApp 1.0

TextField {
    property string innerText: ""

    width: parent.width
    height: 40

    // === DWUKIERUNKOWA SYNC ===
    // Gdy użytkownik zmienia text, aktualizuj innerText
    onTextChanged: {
        if (innerText !== text) innerText = text
    }
    // Gdy z zewnątrz zmienia się innerText, aktualizuj text
    onInnerTextChanged: {
        if (text !== innerText) text = innerText
    }

    background: Rectangle {
        radius: 21
        color: ThemeManager.colors.mediumRectangleBgColor
        border.color: ThemeManager.colors.linesColor
        border.width: 1
    }

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter

    font.pixelSize: ThemeManager.fonts.fontSize
    color: ThemeManager.fonts.fontColor
    placeholderTextColor: Qt.rgba(color.r, color.g, color.b, 0.3)
}
