cmake_minimum_required(VERSION 3.16)
project(appEarEEG_DemoApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8 COMPONENTS Quick REQUIRED Quick Core Gui Widgets Graphs Sql Network Bluetooth)

set(QT_METHODS_IN_NAMESPACED_SCOPE ON)

qt_add_executable(appEarEEG_DemoApp
    main.cpp
)

set_source_files_properties(
    qml/styles/MyStyles.qml
    qml/styles/ThemeManager.qml
    qml/styles/themes/UiSettings.qml
    qml/styles/themes/LightTheme.qml
    qml/styles/themes/DarkTheme.qml
    qml/styles/themes/BlueTheme.qml
    qml/styles/themes/ModernTheme.qml

    PROPERTIES
        QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(appEarEEG_DemoApp
    URI EarEEG_DemoApp
    VERSION 1.0

    QML_FILES
        main.qml

        qml/styles/MyStyles.qml
        qml/styles/ThemeManager.qml
        qml/styles/themes/UiSettings.qml
        qml/styles/themes/LightTheme.qml
        qml/styles/themes/DarkTheme.qml
        qml/styles/themes/BlueTheme.qml
        qml/styles/themes/ModernTheme.qml

        qml/screens/TestScreen.qml
        qml/screens/DataScreen.qml
        qml/screens/HomeScreen.qml
        qml/screens/UserDetailsScreen.qml
        qml/screens/SingInScreen.qml
        qml/screens/LogInScreen.qml
        qml/screens/LogOutScreen.qml
        qml/screens/EegChartScreen.qml
        qml/screens/SettingsScreen.qml
        qml/screens/NoteScreen.qml
        qml/screens/DataSourceSelectorScreen.qml

        qml/sharedComponents/CustomLabel.qml
        qml/sharedComponents/CustomLabelClick.qml
        qml/sharedComponents/CustomTextField.qml
        qml/sharedComponents/CustomComboBox.qml
        qml/sharedComponents/CustomSpinBox.qml
        qml/sharedComponents/CustomImage.qml
        qml/sharedComponents/ButtonWithText.qml
        qml/sharedComponents/LineSeparator.qml
        qml/sharedComponents/TabButtonFooter.qml
        qml/sharedComponents/CustomTextArea.qml

        qml/eegComponents/FocusRecommendations.qml

    SOURCES
        src/ApplicationController.h
        src/ApplicationController.cpp

        src/core/EEGSample.h
        src/core/User.h
        src/core/Participant.h
        src/core/Note.h

        src/utils/Logger.h
        src/utils/Logger.cpp

        src/storage/DatabaseConfig.h
        src/storage/TableSchemasSQLite.h
        src/storage/IDatabaseManager.h
        src/storage/DataPipeline.h
        src/storage/DataPipeline.cpp
        src/storage/DatabaseManager.h
        src/storage/DatabaseManager.cpp
        src/storage/SQLiteManager.h
        src/storage/SQLiteManager.cpp
        src/storage/UserRepository.h
        src/storage/UserRepository.cpp
        src/storage/ParticipantRepository.h
        src/storage/ParticipantRepository.cpp
        src/storage/NoteRepository.h
        src/storage/NoteRepository.cpp
        src/storage/SettingsRepository.h
        src/storage/SettingsRepository.cpp

        src/providers/IDataSource.h
        src/providers/CsvDataSource.h
        src/providers/CsvDataSource.cpp
        src/providers/BinDataSource.h
        src/providers/BinDataSource.cpp
        src/providers/BleDataSource.h
        src/providers/BleDataSource.cpp

        src/models/UserModel.h
        src/models/UserModel.cpp
        src/models/ParticipantModel.h
        src/models/ParticipantModel.cpp
        src/models/EEGModel.h
        src/models/EEGModel.cpp
        src/models/NoteModel.h
        src/models/NoteModel.cpp

    RESOURCES
        README.md

        # GENERAL
        assets/example-eegchart-with4channels.png
        assets/EarEEG.png
        assets/EarEEG2.png
        assets/arrowStraight.png
        assets/arrowDown.png
        assets/arrowTop.png

        # THEME DARK ICONS
        assets/themeDarkIcons/menu-bar.png
        assets/themeDarkIcons/data-analysis.png
        assets/themeDarkIcons/user.png
        assets/themeDarkIcons/house.png
        assets/themeDarkIcons/logout.png
        assets/themeDarkIcons/settings.png

        # THEME LIGHT ICONS
        assets/themeLightIcons/menu-bar.png
        assets/themeLightIcons/data-analysis.png
        assets/themeLightIcons/user.png
        assets/themeLightIcons/house.png
        assets/themeLightIcons/logout.png
        assets/themeLightIcons/settings.png

        # THEME BLUE ICONS
        assets/themeBlueIcons/menu-bar.png
        assets/themeBlueIcons/data-analysis.png
        assets/themeBlueIcons/user.png
        assets/themeBlueIcons/house.png
        assets/themeBlueIcons/logout.png
        assets/themeBlueIcons/settings.png

        # THEME BLUE ICONS
        assets/themeModernIcons/menu-bar.png
        assets/themeModernIcons/data-analysis.png
        assets/themeModernIcons/user.png
        assets/themeModernIcons/house.png
        assets/themeModernIcons/logout.png
        assets/themeModernIcons/settings.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appEarEEG_DemoApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appEarEEG_DemoAppFrontend
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appEarEEG_DemoApp PRIVATE src)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(appEarEEG_DemoApp PRIVATE QT_DISABLE_DEPRECATED_BEFORE=0x060000)
else()
    target_compile_definitions(appEarEEG_DemoApp PRIVATE
        QT_NO_DEBUG_OUTPUT
        QT_NO_INFO_OUTPUT
    )
endif()

target_link_libraries(appEarEEG_DemoApp
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::Widgets
        Qt6::Graphs
        Qt6::Sql
        Qt6::Network
        Qt6::Bluetooth
)

include(GNUInstallDirs)
install(TARGETS appEarEEG_DemoApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
