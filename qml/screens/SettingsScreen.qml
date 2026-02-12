import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import EarEEG_DemoApp 1.0

Page {
    anchors.fill: parent
    // property var themeData: ({})
    // property var themeList: ["Dark", "Light", "Blue"]
    // property string innerButtonText: "Apply"
    // property string themeDefault: "Dark"
    // property string themeTitle: "App theme"

    property var themeList: ["dark", "light", "modern", "blue"]

    background: Rectangle {
        color: "transparent"
    }

    Column {
        anchors.margins: 20
        anchors.fill: parent
        spacing: 20

        CustomLabel {
            labelText: "App theme"
            textBold: true
        }

        ComboBox {
            id: themeCombo
            model: themeList
            currentIndex: themeList.indexOf(ThemeManager.currentTheme.name)
        }

        Button {
            text: "Apply"
            onClicked: {
                ThemeManager.setTheme(themeList[themeCombo.currentIndex])
            }
        }
    }

    // Item {
    //     width: parent.width
    //     height: parent.height - 10
    //     anchors.centerIn: parent

    //     Column {
    //         spacing: 8
    //         anchors.left: parent.left
    //         anchors.right: parent.right
    //         anchors.margins: 10

    //         CustomLabel {
    //             labelText: themeTitle
    //             textBold: true
    //         }

    //         CustomComboBox {
    //             id: genderCombo
    //             width: parent.width
    //             model: themeList
    //             currentIndex: themeList.indexOf(themeDefault)
    //             onCurrentIndexChanged: gender = themeList[currentIndex]
    //         }

    //         ButtonWithText {
    //             anchors.right: parent.right
    //             buttonText: innerButtonText
    //         }
    //     }
    // }
}
