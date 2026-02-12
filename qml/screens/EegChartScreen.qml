import QtQuick
import QtQuick.Controls
import QtGraphs
import EarEEG_DemoApp 1.0

Page {
    id: eegChartPage

    property string xAxisTitle: "Time [s]"
    property string yAxisTitle: "Amplitude [µV]"
    readonly property int channelCount: 8
    readonly property int offsetSpacing: 20
    readonly property real eegSpeed: 1

    readonly property var chColors:  ["#FF5555", "#55FF55", "#5555FF", "#FFFF55", "#FF55FF", "#55FFFF", "#FFAA00", "#FFFFFF"]
    readonly property var chText:    ["CH01", "CH02", "CH03", "CH04", "CH05", "CH06", "CH07", "CH08"]

    Connections {
        target: eegModel
        function onDataUpdated() {
            let points = eegModel.getPointsForChannel(0)
            let points1 = eegModel.getPointsForChannel(1)
            let points2 = eegModel.getPointsForChannel(2)
            if (points.length > 0) {
                console.log("QML Channel 0 sample: X=" + points[0].x + " Y=" + points[0].y)
                console.log("QML Channel 1 sample: X=" + points1[1].x + " Y=" + points1[1].y)
                console.log("QML Channel 2 sample: X=" + points2[2].x + " Y=" + points2[2].y)
            }
            series0.replace(eegModel.getPointsForChannel(0))
            series1.replace(eegModel.getPointsForChannel(1))
            series2.replace(eegModel.getPointsForChannel(2))
            series3.replace(eegModel.getPointsForChannel(3))
            series4.replace(eegModel.getPointsForChannel(4))
            series5.replace(eegModel.getPointsForChannel(5))
            series6.replace(eegModel.getPointsForChannel(6))
            series7.replace(eegModel.getPointsForChannel(7))
        }
    }

    background: Rectangle { color: "transparent" }

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
                labelFont.pixelSize: 11
            }

            axisX: ValueAxis {
                id: xAxis
                // Jeśli lastestTimestamp jest 0, ustaw sztywny zakres, żeby nie było błędów
                min: 0
                max: 5
                titleText: xAxisTitle
                labelsVisible: true
                gridVisible: false
                lineVisible: true
            }

            axisY: ValueAxis {
                id: yAxis
                max: (offsetSpacing * channelCount)
                min: -50
                titleText: yAxisTitle
                labelsVisible: true
                tickInterval: offsetSpacing
            }

            // ==========================================
            // SERIE DANYCH (LINIE WYKRESU)
            // ==========================================
            LineSeries { id: series0; color: chColors[0]; width: 2 } //; axisX: xAxis; axisY: yAxis }
            LineSeries { id: series1; color: chColors[1]; width: 2 } //; axisX: xAxis; axisY: yAxis }
            LineSeries { id: series2; color: chColors[2]; width: 2 } //; axisX: xAxis; axisY: yAxis }
            LineSeries { id: series3; color: chColors[3]; width: 2 } //; axisX: xAxis; axisY: yAxis }
            LineSeries { id: series4; color: chColors[4]; width: 2 } //; axisX: xAxis; axisY: yAxis }
            LineSeries { id: series5; color: chColors[5]; width: 2 } //; axisX: xAxis; axisY: yAxis }
            LineSeries { id: series6; color: chColors[6]; width: 2 } //; axisX: xAxis; axisY: yAxis }
            LineSeries { id: series7; color: chColors[7]; width: 2 } //; axisX: xAxis; axisY: yAxis }
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

            Row {
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

    // RĘCZNA WERSJA RYSOWANIA WYKRESU
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
    //         ch1.append(currentX, ((Math.random()-0.5) * 20) + (offsetSpacing * 7.5))
    //         ch2.append(currentX, ((Math.random()-0.5) * 20) + (offsetSpacing * 6.5))
    //         ch3.append(currentX, ((Math.random()-0.5) * 20) + (offsetSpacing * 5.5))
    //         ch4.append(currentX, ((Math.random()-0.5) * 20) + (offsetSpacing * 4.5))
    //         ch5.append(currentX, ((Math.random()-0.5) * 20) + (offsetSpacing * 3.5))
    //         ch6.append(currentX, ((Math.random()-0.5) * 20) + (offsetSpacing * 2.5))
    //         ch7.append(currentX, ((Math.random()-0.5) * 20) + (offsetSpacing * 1.5))
    //         ch8.append(currentX, ((Math.random()-0.5) * 20) + (offsetSpacing * 0.5))

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

    // // ==========================================
    // // DEFINICJA KOMPONENTU LINII
    // // ==========================================
    // component AnimatedSplineSeries: SplineSeries {
    //     property color pointColor: "white"
    //     width: 1.5 // grubość linii wykresu

    //     pointDelegate: Rectangle {
    //         height: 0
    //         width: 0
    //         radius: width / 2
    //         color: pointColor
    //     }

    //     // Punkty startowe, żeby wykres nie był pusty na początku
    //     XYPoint { x: 0.0; y: 0.0 }
    // }
}
