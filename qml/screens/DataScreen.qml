import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import EarEEG_DemoApp 1.0

Page {
    id: root
    anchors.fill: parent

    FocusRecommendations {
        id: recs
    }

    property int currentFocusLevel: 1
    property int currentFocusPercent: 0
    property var currentRec: recs.byLevel(currentFocusLevel)
    property string titleText: "Current Score"
    property string buttonAddDataText: "ADD NOTES"
    property string buttonCheckChartsText: "Click to check EEG channels!"
    property string loadingDataText: "Loading data..."
    property string titleHowToHangeText: "How to change it?"

    property string eegChartScreenPath: UiSettings.rootPathToQmlScreens + "EegChartScreen.qml"
    property string datasourceSelectorScreenPath: UiSettings.rootPathToQmlScreens + "DataSourceSelectorScreen.qml"
    property string noteScreenPath: UiSettings.rootPathToQmlScreens + "NoteScreen.qml"

    background: Rectangle {
        color: "transparent"
    }

    // ---------------------------
    // USTAWIENIA - generowanie losowych liczb, które określają poziom skupienia (dopóki backend nie będzie gotowy)
    // ---------------------------
    Timer {
        interval: 3000
        running: true
        repeat: true

        onTriggered: {
            root.currentFocusLevel = Math.floor(Math.random() * 3) + 1

            var rec = recs.byLevel(root.currentFocusLevel)
            if (rec) {
                var min = rec.minPercent
                var max = rec.maxPercent
                root.currentFocusPercent = Math.floor(Math.random() * (max - min + 1)) + min
            }
        }
    }

    // ---------------------------
    // USTAWIENIA - przypięta stopka z przyciskiem
    // ---------------------------
    ButtonWithText {
        id: notesButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        buttonText: buttonAddDataText
        z: 10

        onClicked: {
            stackView.push(noteScreenPath)
        }
    }

    // ---------------------------
    // EKRAN: Nagłówek i opis
    // ---------------------------
    Column {
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        spacing: 15

        Column {
            width: parent.width * 0.9
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 5

            // Text {
            //     text: currentRec ? currentRec.description : loadingDataText
            //     color: MyStyles.fontColor
            //     font.pixelSize: 18
            //     font.bold: true
            //     horizontalAlignment: Text.AlignHCenter
            //     wrapMode: Text.WordWrap
            //     anchors.horizontalCenter: parent.horizontalCenter
            // }

            // Text {
            //     text: currentRec ? currentRec.detailedDescription : ""
            //     color: MyStyles.fontColor
            //     font.pixelSize: 18
            //     horizontalAlignment: Text.AlignHCenter
            //     wrapMode: Text.WordWrap
            //     anchors.horizontalCenter: parent.horizontalCenter
            //     width: parent.width
            //     maximumLineCount: 4
            //     elide: Text.ElideRight
            // }
        }

        // ---------------------------
        // EKRAN: POZIOM SKUPIENIA - karta z detalami i poziomem
        // ---------------------------
        Rectangle {
            width: parent.width
            height: 100
            color: ThemeManager.colors.mediumRectangleBgColor
            radius: ThemeManager.radii.radiusGeneral

            Column {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 7

                // napis na górze
                Text {
                    text: titleText
                    color: "transparent" // currentRec ? currentRec.color : MyStyles.fontColor
                    font.pixelSize: 10
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                // wiersz z % i ikonką
                Row {
                    spacing: 12
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        text: currentFocusPercent + "%" //currentRec ? currentRec.focusPercentage : "--"
                        color: currentRec ? currentRec.color : ThemeManager.colors.fontColor
                        font.pixelSize: 40
                        font.bold: true
                    }

                    Rectangle {
                        width: 34
                        height: 34
                        radius: 6
                        color: ThemeManager.colors.smallRectangleBgColor
                        anchors.verticalCenter: parent.verticalCenter

                        CustomImage {
                            anchors.centerIn: parent
                            iconPath: currentRec ? (root.MyStyles.assetsPath + currentRec.arrowIconFileName) : ""
                            widthMultiplier: 1
                            heightMultiplier: 1
                            fillMode: Image.PreserveAspectFit
                        }
                    }
                }
            }
        }

        // ---------------------------
        // EKRAN: IKONA WYKRES EEG (PNG) - przekierowanie do prawdziwego wykresu
        // ---------------------------

        Column {
            id: chartPreviewColumn
            width: parent.width
            spacing: 14
            anchors.horizontalCenter: parent.horizontalCenter

            // ---- PREVIEW WYKRESU (klikany) ----
            Rectangle {
                id: chartPreview
                width: parent.width
                height: 100
                radius: ThemeManager.radii.radiusGeneral
                color: "transparent" // ThemeManager.colors.mediumRectangleBgColor
                border.color: "transparent" // ThemeManager.colors.linesColor
                border.width: 1
                anchors.horizontalCenter: parent.horizontalCenter

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stackView.push(eegChartScreenPath)
                    }
                }

                CustomImage {
                    anchors.centerIn: parent
                    iconPath: ThemeManager.icons.eegImageIcon
                    widthMultiplier: 3
                    heightMultiplier: 3
                }
            }
        }

        // ---------------------------
        // EKRAN: LISTA REKOMENDACJI
        // ---------------------------
        Column {
            width: parent.width * 0.9
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 30
            spacing: 8

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: currentRec ? currentRec.recommendationTitle : ""
                color: ThemeManager.fonts.fontColor
                font.pixelSize: ThemeManager.fonts.fontSize
                font.bold: true
            }

            Repeater {
                model: currentRec ? currentRec.recommendations : []
                delegate: Text {
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.Wrap
                    text: "• " + modelData
                    color: ThemeManager.fonts.fontColor
                    font.pixelSize: 18
                }
            }
        }
    }
}
