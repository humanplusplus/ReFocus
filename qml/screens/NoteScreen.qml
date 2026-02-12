import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import EarEEG_DemoApp 1.0

Page {
    anchors.fill: parent
    property string innerButtonText: "Save"
    property string noteDate: ""
    property string dateTitle: "Date"
    property string description: ""
    property string noteTitle: "Description"

    background: Rectangle {
        color: "transparent"
    }

    Item {
        width: parent.width
        height: parent.height - 10
        anchors.centerIn: parent

        Column {
            spacing: 8
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10

            CustomLabel {
                labelText: dateTitle
                textBold: true
            }
            CustomTextField {
                id: noteDateItem
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                innerText: noteDate
                onInnerTextChanged: noteDate = innerText
            }


            CustomLabel {
                labelText: noteTitle
                textBold: true
            }
            CustomTextField {
                id: descriptionItem
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                innerText: description
                onInnerTextChanged: description = innerText
            }

            ButtonWithText {
                anchors.right: parent.right
                buttonText: innerButtonText
            }
        }
    }
}
