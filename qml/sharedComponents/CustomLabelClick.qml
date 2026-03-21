import QtQuick 2.15
import QtQuick.Controls 2.15
import EarEEG_DemoApp 1.0

Text {
    id: root

    property string labelText: ""
    property bool textBold: false

    horizontalAlignment: horizontalAlignment
    //verticalAlignment: verticalAlignment
    text: labelText
    color: ThemeManager.fonts.fontColor
    font.bold: textBold
    font.pixelSize: ThemeManager.fonts.fontSize
    wrapMode: Text.WordWrap

    signal clicked()

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: root.clicked()
    }
}
