import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import EarEEG_DemoApp 1.0

Page {
    anchors.fill: parent

    function getCurrentDateTime() {
        let now = new Date();

        // Pomocnicza funkcja dodająca zero przed cyfrą (np. "9" -> "09")
        let format = (v) => v.toString().padStart(2, '0');

        let y = now.getFullYear();
        let m = format(now.getMonth() + 1);
        let d = format(now.getDate());
        let hh = format(now.getHours());
        let mm = format(now.getMinutes());

        return `${y}-${m}-${d} ${hh}:${mm}`;
    }

    property string innerButtonText: "Save"
    property string noteDate: ""
    property string dateTitle: "Date"
    property string description: ""
    property string noteTitle: "Description"
    property string datePlaceholder: "YYYY-MM-DD HH:MM"
    property string dateMask: "0000-00-00 00:00; "

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
                // placeholderText: (text === "" && !focus) ? datePlaceholder : ""
                // inputMask: (focus || text.length > 0) ? dateMask : ""
                inputMask: dateMask
                innerText: noteDate

                Component.onCompleted: {
                    let dt = getCurrentDateTime()
                    innerText = dt
                    text = dt
                }
                onInnerTextChanged: noteDate = innerText
            }


            CustomLabel {
                labelText: noteTitle
                textBold: true
            }
            CustomTextArea {
                id: descriptionItem
                horizontalAlignment: Text.AlignHCenter
                innerText: description
                onInnerTextChanged: description = innerText
            }

            ButtonWithText {
                anchors.right: parent.right
                buttonText: innerButtonText
                onClicked: {
                    noteModel.addNote(noteDateItem.text, descriptionItem.text, "3", "exampleTag");
                }
            }
        }
    }
}
