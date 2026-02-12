import QtQuick 2.15

Rectangle {
    width: parent.width
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter

    property real lineHeight
    property color lineColor

    color: lineColor
    height: lineHeight // line thickness
}
