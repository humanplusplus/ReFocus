import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material
import EarEEG_DemoApp 1.0

Page {

    property string loginScreenPath: UiSettings.rootPathToQmlScreens + "LogInScreen.qml"

    property string loginTitle: "Username or Email"
    property string passwordTitle: "Password"
    property string passwordConfirmationTitle: "Password Confirmation"
    property string buttonText: "Sing In"
    property string loginText: "Log In"

    property string loginValue: ""
    property string passwordValue: ""

    background: Rectangle {
        color: "transparent"
    }

    Item {
        width: 300
        height: 250
        anchors.centerIn: parent

        Column {
            spacing: 10
            width: parent.width

            CustomLabel {
                horizontalAlignment: Text.AlignHCenter
                labelText: loginTitle
            }

            CustomTextField {
                innerText: loginValue
            }

            CustomLabel {
                horizontalAlignment: Text.AlignHCenter
                labelText: passwordTitle
            }

            CustomTextField {
                innerText: passwordValue
                echoMode: TextInput.Password // hide password
            }

            CustomLabel {
                horizontalAlignment: Text.AlignHCenter
                labelText: passwordConfirmationTitle
            }

            CustomTextField {
                innerText: passwordValue
                echoMode: TextInput.Password // hide password
            }

            ButtonWithText {
                anchors.horizontalCenter: parent.horizontalCenter
                buttonText: buttonText

                onClicked: {
                    if (userModel.loginUser(loginValue, passwordValue)) {
                        console.log("✅ Login successful");
                        stackView.push("qml/screens/UserDetailsScreen.qml");
                    } else {
                        console.log("❌ Login failed");
                    }
                }
            }

            CustomLabelClick {
                horizontalAlignment: Text.AlignHCenter
                labelText: loginText
                color: "lightblue"                // dla wizualnego efektu linka
                font.underline: true              // podkreślenie jak w linku

                onClicked: {
                    console.log("🔁 Redirecting to:", loginScreenPath)
                    stackView.push(loginScreenPath)
                }
            }
        }
    }

}
