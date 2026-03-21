import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtGraphs
import EarEEG_DemoApp 1.0

Page {
    id: eegChartPage

    property string xAxisTitle: "Time [s]"
    property string yAxisTitle: "Amplitude [µV]"

    readonly property var chColors:  ["#FF5555", "#55FF55", "#5555FF", "#FFFF55", "#FF55FF", "#55FFFF", "#FFAA00", "#FFFFFF"]
    readonly property var chText:    ["CH1", "CH2", "CH3", "CH4", "CH5", "CH6", "CH7", "CH8"]

    Connections {
        target: eegModel
        function onDataUpdated() {
            // let p0 = eegModel.getLeadingPoints(0)
            // if (p0.length > 0) {
            //     console.log("QML ch0 size", p0.length, "last X", p0[p0.length-1].x)
            // }

            // Aktualizacja obu fragmentów dla każdego kanału
            series0_A.replace(eegModel.getLeadingPoints(0)); series0_B.replace(eegModel.getTrailingPoints(0))
            series1_A.replace(eegModel.getLeadingPoints(1)); series1_B.replace(eegModel.getTrailingPoints(1))
            series2_A.replace(eegModel.getLeadingPoints(2)); series2_B.replace(eegModel.getTrailingPoints(2))
            series3_A.replace(eegModel.getLeadingPoints(3)); series3_B.replace(eegModel.getTrailingPoints(3))
            series4_A.replace(eegModel.getLeadingPoints(4)); series4_B.replace(eegModel.getTrailingPoints(4))
            series5_A.replace(eegModel.getLeadingPoints(5)); series5_B.replace(eegModel.getTrailingPoints(5))
            series6_A.replace(eegModel.getLeadingPoints(6)); series6_B.replace(eegModel.getTrailingPoints(6))
            series7_A.replace(eegModel.getLeadingPoints(7)); series7_B.replace(eegModel.getTrailingPoints(7))

            // Ruch linii kursora
            cursorLine.x = ( (eegModel.latestTimestamp % 5.0) / 5.0 ) * qtGraphContainer.width
        }
    }

    background: Rectangle { color: "transparent" }

    Rectangle {
        id: qtGraphContainer
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
                min: 0
                max: 5
                titleText: xAxisTitle
                labelsVisible: true
                gridVisible: false
                lineVisible: true
            }

            axisY: ValueAxis {
                id: yAxis
                max: 850
                min: -50
                titleText: yAxisTitle
                labelsVisible: true
                tickInterval: 100
            }

            // ==========================================
            // SERIE DANYCH (LINIE WYKRESU) - Każdy kanał ma dwie serie, aby uniknąć linii powrotnej, która łączy dane w QtGraphs
            // ==========================================
            LineSeries { id: series0_A; color: chColors[0]; width: 1.5 }
            LineSeries { id: series0_B; color: chColors[0]; width: 1.5 }
            LineSeries { id: series1_A; color: chColors[1]; width: 1.5 }
            LineSeries { id: series1_B; color: chColors[1]; width: 1.5 }
            LineSeries { id: series2_A; color: chColors[2]; width: 1.5 }
            LineSeries { id: series2_B; color: chColors[2]; width: 1.5 }
            LineSeries { id: series3_A; color: chColors[3]; width: 1.5 }
            LineSeries { id: series3_B; color: chColors[3]; width: 1.5 }
            LineSeries { id: series4_A; color: chColors[4]; width: 1.5 }
            LineSeries { id: series4_B; color: chColors[4]; width: 1.5 }
            LineSeries { id: series5_A; color: chColors[5]; width: 1.5 }
            LineSeries { id: series5_B; color: chColors[5]; width: 1.5 }
            LineSeries { id: series6_A; color: chColors[6]; width: 1.5 }
            LineSeries { id: series6_B; color: chColors[6]; width: 1.5 }
            LineSeries { id: series7_A; color: chColors[7]; width: 1.5 }
            LineSeries { id: series7_B; color: chColors[7]; width: 1.5 }
        }
    }

    // ==========================================
    // KOMPAKTOWA LEGENDA POZIOMA (Zawsze w jednej linii)
    // ==========================================
    Rectangle {
        id: floatingLegend
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 8

        width: legendRow.width + 20
        height: 24

        color: Qt.rgba(0, 0, 0, 0.7)
        radius: 4
        border.color: ThemeManager.colors.linesColor

        Row {
            id: legendRow
            anchors.centerIn: parent
            spacing: 8

            Repeater {
                model: 8
                Row {
                    spacing: 4
                    Rectangle {
                        width: 8;
                        height: 8
                        color: chColors[index]
                        radius: 1
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text {
                        text: chText[index]
                        color: ThemeManager.fonts.fontColor
                        font.pixelSize: 10
                        font.bold: true
                    }
                }
            }
        }
    }
}
