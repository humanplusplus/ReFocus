import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material
import EarEEG_DemoApp 1.0

TextField {
    width: parent.width
    height: 40

    property string innerText: ""
    property string placeholderInnerText
    property int maxTextLength: 40
    property color backgroundColor: ThemeManager.colors.mediumRectangleBgColor
    property color borderColor: ThemeManager.colors.linesColor

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
        width: parent.width
        height: parent.height
        radius: 21
        color: backgroundColor
        border.color: borderColor
        border.width: 1
    }

    horizontalAlignment: Text.AlignLeft
    verticalAlignment: Text.AlignLeft
    placeholderText: placeholderInnerText
    font.pixelSize: ThemeManager.fonts.fontSize
    color: ThemeManager.colors.fontColor
    maximumLength: maxTextLength
}
