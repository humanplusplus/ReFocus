import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtQuick.Controls.Fusion
import EarEEG_DemoApp 1.0

ApplicationWindow {
    visible: true
    width: 360
    height: 640

    // Screens paths
    property string homeScreenPath:         UiSettings.rootPathToQmlScreens + "EegChartScreen.qml" // "HomeScreen.qml"
    property string dataScreenPath:         UiSettings.rootPathToQmlScreens + "DataScreen.qml"
    property string settingsScreenPath:     UiSettings.rootPathToQmlScreens + "SettingsScreen.qml"
    property string userDetailsScreenPath:  UiSettings.rootPathToQmlScreens + "TestScreen.qml" // "UserDetailsScreen.qml"
    property string logoutScreenPath:       UiSettings.rootPathToQmlScreens + "EegChartScreen.qml" // "LogOutScreen.qml"

    // Menus titles
    property string headerTitle:            "Attention"
    property string homeTitle:              "Home"
    property string dataTitle:              "EarEEG Data"
    property string userDetailsTitle:       "User Details"
    property string settingsTitle:          "Settings"
    property string logoutTitle:            "Logout"

    Material.accent: "transparent"
    background: Rectangle {
        color: ThemeManager.colors.backgroundColor
    }

    header: ToolBar {
        contentHeight: 60
        background: Rectangle {
            color: ThemeManager.colors.ribbonColor
        }

        Row {
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 5

            // Left side header
            ToolButton {
                hoverEnabled: false
                highlighted: false

                Rectangle {
                    width: 30
                    height: 30
                    radius: 5
                    color: ThemeManager.colors.smallRectangleBgColor
                    anchors.verticalCenter: parent.verticalCenter

                    CustomImage {
                        iconPath: ThemeManager.icons.sideMenuIcon
                    }
                }

                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if (drawer.visible) {
                        drawer.close()
                    } else {
                        drawer.open()
                    }
                }
            }

            // Transparent space to center
            Rectangle {
                width: parent.width * 0.25
                height: 1
                color: "transparent"
            }

            // Middle side header
            Row {
                spacing: 5
                anchors.centerIn: parent

                Label {
                    id: headerLabel
                    text: headerTitle
                    color: ThemeManager.fonts.fontColor
                    font.pointSize: ThemeManager.fonts.fontSize
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            // Transparent space to center
            Rectangle {
                width: parent.width * 0.25
                height: 1
                color: "transparent"
            }

            // Right side header
            ToolButton {
                id: homeButton
                visible: false

                hoverEnabled: false
                highlighted: false

                CustomImage {
                    iconPath: ThemeManager.icons.homeIcon
                }

                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    headerLabel.text = headerTitle
                    homeButton.visible = false
                    stackView.push(homeScreenPath)
                    footer.visible = true
                }
            }
        }

        // Line on the top of the header
        LineSeparator {
            lineHeight: 2
            lineColor: ThemeManager.colors.linesColor
        }
    }

    // Side menu
    Drawer {
        id: drawer
        width: parent.width * 0.5
        height: parent.height
        edge: Qt.LeftEdge

        background: Rectangle {
            color: ThemeManager.colors.cardsBackgroundColor
        }

        ListView {
            width: parent.width
            height: parent.height
            model: [
                homeTitle,
                dataTitle,
                userDetailsTitle,
                settingsTitle,
                logoutTitle
            ]
            delegate: ItemDelegate {
                width: parent.width
                height: 50

                contentItem: Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    text: modelData
                    font.pointSize: ThemeManager.fonts.fontSize
                    color: ThemeManager.fonts.fontColor
                }

                highlighted: false
                hoverEnabled: false

                LineSeparator {
                    lineColor: ThemeManager.colors.linesColor
                    lineHeight: 1
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        drawer.close()
                        if (modelData === homeTitle) {
                            homeButton.visible = true
                            headerLabel.text = homeTitle
                            stackView.push(homeScreenPath)
                            footer.visible = false
                        } else if (modelData === dataTitle) {
                            homeButton.visible = true
                            headerLabel.text = dataTitle
                            stackView.push(dataScreenPath)
                            footer.visible = false
                        } else if (modelData === userDetailsTitle) {
                            homeButton.visible = true
                            headerLabel.text = userDetailsTitle
                            stackView.push(Qt.resolvedUrl(userDetailsScreenPath))
                            footer.visible = false
                        } else if (modelData === settingsTitle) {
                            homeButton.visible = true
                            headerLabel.text = settingsTitle
                            stackView.push(Qt.resolvedUrl(settingsScreenPath))
                            footer.visible = false
                        } else if (modelData === logoutTitle) {
                            homeButton.visible = true
                            headerLabel.text = logoutTitle
                            stackView.push(Qt.resolvedUrl(logoutScreenPath))
                            footer.visible = false
                        } else {
                            stackView.push(Qt.resolvedUrl(homeScreenPath), { category: modelData })
                        }
                    }
                }
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: homeScreenPath

        // onCurrentItemChanged:
        //     tabBar.visible = !(stackView.currentItem instanceof HomeScreen)
    }

    footer: TabBar {
        id: footer
        height: 50

        background: Rectangle {
            color: ThemeManager.colors.ribbonColor
        }

        TabButtonFooter {
            stackViewPath: Qt.resolvedUrl(homeScreenPath)
            iconPath: ThemeManager.icons.homeIcon
        }

        TabButtonFooter {
            stackViewPath: Qt.resolvedUrl(dataScreenPath)
            iconPath: ThemeManager.icons.chartsIcon
        }

        TabButtonFooter {
            stackViewPath: Qt.resolvedUrl(userDetailsScreenPath)
            iconPath: ThemeManager.icons.userIcon
        }
    }
}
