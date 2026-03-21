import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import EarEEG_DemoApp 1.0

Page {
    id: selectorPage

    background: Rectangle { color: "transparent" }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 30

        Text {
            text: "Select Data Source"
            color: ThemeManager.fonts.fontColor
            font.pixelSize: ThemeManager.fonts.fontSize * 1.6
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }

        ColumnLayout {
            spacing: 15

            ButtonWithText {
                buttonText: "CSV File (.csv)"
                Layout.preferredWidth: 200
                onClicked: {
                    eegModel.clear()
                    appController.startStreaming(0)
                    stackView.push(UiSettings.rootPathToQmlScreens + "EegChartScreen.qml")
                }
            }

            // ButtonWithText {
            //     buttonText: "Binary File (.bin)"
            //     Layout.preferredWidth: 200
            //     onClicked: {
            //         eegModel.clear()
            //         appController.startStreaming(1)
            //         stackView.push(UiSettings.rootPathToQmlScreens + "EegChartScreen.qml")
            //     }
            // }

            // ButtonWithText {
            //     buttonText: "Connect via BLE"
            //     Layout.preferredWidth: 200
            //     enabled: false
            //     onClicked: {
            //         eegModel.clear()
            //         appController.startStreaming(2)
            //         stackView.push(UiSettings.rootPathToQmlScreens + "EegChartScreen.qml")
            //     }
            // }
        }
    }
}
