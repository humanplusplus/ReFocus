import QtQuick
import QtQuick.Controls
import QtGraphs
import EarEEG_DemoApp 1.0

Page {
    id: eegChartPage

    property string xAxisTitle: "Time [s]"
    property string yAxisTitle: "Amplitude [µV]"
    property int channelCount: 8
    property int channelSpacing: 10 // Odstęp między kanałami na osi Y (uV)
    property real eegSpeed: 1

    property var chColors:  ["#FF5555", "#55FF55", "#5555FF", "#FFFF55", "#FF55FF", "#55FFFF", "#FFAA00", "#FFFFFF"]
    property var chText:    ["CH01", "CH02", "CH03", "CH04", "CH05", "CH06", "CH07", "CH08"]

    background: Rectangle {
        color: "transparent"
    }

    // Główny kontener wykresu - tutaj ograniczasz rozmiar
    Rectangle {
        id: chartContainer
        anchors.centerIn: parent
        width: parent.width * 1
        height: parent.height * 0.6

        GraphsView {
            id: graphsView
            anchors.fill: parent

            // ==========================================
            // GLOBALNY MOTYW I SIATKA
            // ==========================================
            theme: GraphsTheme {
                colorScheme: GraphsTheme.ColorScheme.Dark
                // labelTextColor: red // "#AAAAAA" Kolor cyfr na osiach
                labelFont.pixelSize: 11
            }

            axisX: ValueAxis {
                id: xAxis
                //tickInterval: 1
                max: 10
                min: 0
                titleText: xAxisTitle
                labelsVisible: true
                gridVisible: false
                lineVisible: true
            }

            axisY: ValueAxis {
                id: yAxis
                max: channelSpacing * channelCount
                min: 0
                titleText: yAxisTitle
                labelsVisible: true
                tickInterval: channelSpacing
            }

            // ==========================================
            // SERIE DANYCH (LINIE WYKRESU) (Wersja z ręcznym ID dla łatwego wstrzykiwania)
            // ==========================================
            AnimatedSplineSeries { id: ch1; color: chColors[0] }
            AnimatedSplineSeries { id: ch2; color: chColors[1] }
            AnimatedSplineSeries { id: ch3; color: chColors[2] }
            AnimatedSplineSeries { id: ch4; color: chColors[3] }
            AnimatedSplineSeries { id: ch5; color: chColors[4] }
            AnimatedSplineSeries { id: ch6; color: chColors[5] }
            AnimatedSplineSeries { id: ch7; color: chColors[6] }
            AnimatedSplineSeries { id: ch8; color: chColors[7] }
        }

        // ==========================================
        // LEGENDA (Ręczna konstrukcja)
        // ==========================================
        Rectangle {
            id: customLegend
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 20
            width: 120
            height: columnLayout.childrenRect.height + 20
            color: Qt.rgba(0, 0, 0, 0.6) // Półprzezroczyste tło
            radius: 5
            border.color: "#444"

            Column {
                id: columnLayout
                anchors.centerIn: parent
                spacing: 5

                Repeater {
                    model: 8 // Wygeneruj 8 wierszy
                    Row {
                        spacing: 8
                        Rectangle {
                            width: 10;
                            height: 10;
                            color: chColors[index]; // bierze kolor z tablicy
                            radius: 2
                        }
                        Text {
                            text: "CH0" + (index + 1);
                            color: "white";
                            font.pixelSize: 10
                        }
                    }
                }
            }
        }
    }

    // // ==========================================
    // // WSTRZYKIWANIE DANYCH (Logika napływu)
    // // ==========================================
    // Timer {
    //     interval: 1000
    //     running: true
    //     repeat: true

    //     property real currentX: 5.0 // Punkt startowy

    //     onTriggered: {
    //         currentX += (eegSpeed * 1.1)

    //         // Symulacja danych z offsetem dla każdego kanału
    //         // Wartość Y = (Szum) + (Index kanału * Odstęp)
    //         ch1.append(currentX, ((Math.random()-0.5) * 20) + (channelSpacing * 7.5))
    //         ch2.append(currentX, ((Math.random()-0.5) * 20) + (channelSpacing * 6.5))
    //         ch3.append(currentX, ((Math.random()-0.5) * 20) + (channelSpacing * 5.5))
    //         ch4.append(currentX, ((Math.random()-0.5) * 20) + (channelSpacing * 4.5))
    //         ch5.append(currentX, ((Math.random()-0.5) * 20) + (channelSpacing * 3.5))
    //         ch6.append(currentX, ((Math.random()-0.5) * 20) + (channelSpacing * 2.5))
    //         ch7.append(currentX, ((Math.random()-0.5) * 20) + (channelSpacing * 1.5))
    //         ch8.append(currentX, ((Math.random()-0.5) * 20) + (channelSpacing * 0.5))

    //         // Zarządzanie pamięcią: Usuwamy stare punkty (bufor 200 punktów)
    //         if (ch1.count > 200) {
    //             ch1.remove(0); ch2.remove(0); ch3.remove(0); ch4.remove(0);
    //             ch5.remove(0); ch6.remove(0); ch7.remove(0); ch8.remove(0);
    //         }
    //     }
    // }

    // // ==========================================
    // // ANIMACJA PRZESUWU OSI (Scroll)
    // // ==========================================
    // FrameAnimation {
    //     running: true
    //     onTriggered: {
    //         xAxis.max += frameTime * eegSpeed
    //         xAxis.min += frameTime * eegSpeed
    //     }
    // }

    // ==========================================
    // DEFINICJA KOMPONENTU LINII
    // ==========================================
    component AnimatedSplineSeries: SplineSeries {
        property color pointColor: "white"
        width: 1.5 // grubość linii wykresu

        pointDelegate: Rectangle {
            height: 0
            width: 0
            radius: width / 2
            color: pointColor
        }

        // Punkty startowe, żeby wykres nie był pusty na początku
        XYPoint { x: 0.0; y: 0.0 }
    }
}
