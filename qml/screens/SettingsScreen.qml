import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import EarEEG_DemoApp 1.0

Page {
    anchors.fill: parent
    property var themeData: ({})

    Connections {
        target: themeModel
        function onThemeDataChanged() {
            themeData = themeModel.getThemeDetails()
        }
    }

    property var themeList: ["Dark", "Light", "Modern", "Blue"]

    property string innerButtonText: "Apply"
    property string themeDefault: "Dark"
    property string themeTitle: "App theme"

    background: Rectangle {
        color: "transparent"
    }

    Column {
        anchors.margins: 20
        anchors.fill: parent
        spacing: 20

        CustomLabel {
            labelText: themeTitle
            textBold: true
        }

        CustomComboBox {
            id: themeCombo
            width: parent.width
            model: themeList
            currentIndex: themeList.indexOf(themeDefault)
            onCurrentIndexChanged: themeDefault = themeList[currentIndex]
        }

        ButtonWithText {
            anchors.right: parent.right
            buttonText: innerButtonText

            onClicked: {
                console.log("Saving theme data: ", theme)

                // ThemeManager.setTheme(themeList[themeCombo.currentIndex])
                // themeModel.upsertTheme(theme)
                // themeModel.refresh()
            }
        }
    }
}
