import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import EarEEG_DemoApp 1.0

ComboBox {
    id: genderCombo
    Material.theme: Material.Dark
    width: parent.width
    height: 40
    font.pixelSize: ThemeManager.fonts.fontSize
    model: genderList
    currentIndex: genderList.indexOf(gender)
    Material.accent: ThemeManager.colors.linesColor

    // Tło głównego pola
    background: Rectangle {
        color: ThemeManager.colors.mediumRectangleBgColor
        border.color: ThemeManager.colors.linesColor
        border.width: 1
        radius: 21
    }

    delegate: ItemDelegate {
        width: parent.width
        height: 42
        text: modelData
        font.pixelSize: ThemeManager.fonts.fontSize + 2
        font.family: ThemeManager.fonts.fontStyle
        contentItem: Text {
            text: modelData
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 12
            font.pixelSize: ThemeManager.fonts.fontSize + 2
            color: ThemeManager.fonts.fontColor
        }
        background: Rectangle {
            color: highlighted ? ThemeManager.colors.backgroundColor : "red"
            radius: 8
        }
        onClicked: {
            genderCombo.currentIndex = index
            genderCombo.popup.close()
        }
    }

    // Widoczny tekst w zamkniętym ComboBoxie
    contentItem: Text {
        text: genderCombo.displayText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        elide: Text.ElideRight
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 12
        color: ThemeManager.fonts.fontColor
        font.pixelSize: ThemeManager.fonts.fontSize
        font.family: ThemeManager.fonts.fontStyle
    }

    // Strzałka rozwijania
    indicator: Canvas {
        id: arrow
        width: 12
        height: 8
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.verticalCenter: parent.verticalCenter
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)
            ctx.beginPath()
            ctx.moveTo(0, 0)
            ctx.lineTo(width, 0)
            ctx.lineTo(width / 2, height)
            ctx.closePath()
            ctx.fillStyle = ThemeManager.fonts.fontColor
            ctx.fill()
        }
    }

    // Lista rozwijalna
    popup: Popup {
        y: genderCombo.height
        width: genderCombo.width
        implicitHeight: Math.min(3, genderCombo.model.length) * 44 //Math.min(contentItem.implicitHeight, 200)
        Material.elevation: 8
        Material.theme: Material.Dark

        background: Rectangle {
            color: ThemeManager.colors.mediumRectangleBgColor
            border.color: ThemeManager.colors.linesColor
            border.width: 1
            radius: 21
        }

        contentItem: ListView {
            clip: true
            spacing: 2
            implicitHeight: contentHeight
            model: genderCombo.model
            delegate: ItemDelegate {
                width: parent.width
                height: 42
                text: modelData
                font.pixelSize: ThemeManager.fonts.fontSize + 2
                font.family: ThemeManager.fonts.fontStyle

                contentItem: Text {
                    text: modelData
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 12
                    font.pixelSize: ThemeManager.fonts.fontSize + 2
                    color: ThemeManager.fonts.fontColor
                }

                background: Rectangle {
                    color: highlighted ? "red" : ThemeManager.colors.mediumRectangleBgColor
                    radius: 8
                }

                onClicked: {
                    genderCombo.currentIndex = index
                    genderCombo.popup.close()
                }
            }
        }
    }
}
