import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import EarEEG_DemoApp 1.0

Page {
    anchors.fill: parent
    property var userData: ({})

    Connections {
        target: participantModel
        function onUserDataChanged() {
            userData = participantModel.getUserDetails()
            nickname = userData.nickname ?? ""
            gender = userData.gender ?? "Woman"
            birthYear = userData.birth_year ?? 1990
        }
    }

    property var genderList: ["Woman", "Man"]

    property string nickname: ""
    property int birthYear: 1990
    property string gender: "Woman"

    property string innerButtonText: "Save"
    property string genderDefault: "Woman"

    property string nicknameTitle: "Nickname"
    property string genderTitle: "Gender"
    property string birthYearTitle: "Birth year"

    Component.onCompleted: participantModel.refresh()

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
                labelText: nicknameTitle
                textBold: true
            }
            CustomTextField {
                id: nicknameItem
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                innerText: nickname
                onInnerTextChanged: nickname = innerText
            }


            CustomLabel {
                labelText: genderTitle
                textBold: true
            }

            CustomComboBox {
                id: genderCombo
                width: parent.width
                model: genderList
                currentIndex: genderList.indexOf(gender)
                onCurrentIndexChanged: gender = genderList[currentIndex]
            }


            CustomLabel {
                labelText: birthYearTitle
                textBold: true
            }
            CustomTextField {
                id: birthYearItem
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                innerText: birthYear > 0 ? birthYear.toString() : ""
                inputMethodHints: Qt.ImhDigitsOnly
                onInnerTextChanged: {
                    const n = parseInt(innerText)
                    birthYear = isNaN(n) ? 0 : n
                }
            }

            ButtonWithText {
                anchors.right: parent.right
                buttonText: innerButtonText

                onClicked: {
                    console.log("Saving user: ", nickname, gender, birthYear)

                    participantModel.upsertUser(nickname, gender, birthYear)
                    participantModel.refresh()
                    userData = participantModel.getUserDetails()

                    if (userData.nickname !== undefined) {
                        nicknameItem.innerText = userData.nickname
                        genderCombo.currentIndex = Math.max(0, genderList.indexOf(userData.gender ?? genderDefault))
                        birthYearItem.innerText = userData.birth_year.toString()
                    }
                    console.log("User data updated:", JSON.stringify(userData))
                }
            }
        }
    }
}
