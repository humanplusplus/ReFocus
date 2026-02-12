import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import EarEEG_DemoApp 1.0

Page {
    id: pageItem
    padding: 50

    property int rowWidth: 150
    property int rowHeight: 80
    property string buttonInnerText: "Let's Focus!"

    background: Rectangle {
        color: ThemeManager.colors.backgroundColor
    }

    CustomImage {
        anchors.centerIn:  parent
        fillMode: Image.PreserveAspectFit
        widthMultiplier: 14
        heightMultiplier: 14
        iconPath: MyStyles.earEegImage
    }
}
