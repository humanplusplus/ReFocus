#include <QApplication>
#include <QQmlApplicationEngine>

#include "ApplicationController.h"
#include "utils/Logger.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("EarEEGApp");
    app.setOrganizationDomain("eareegapp.com");
    app.setApplicationName("EarEEGApp");
    app.setApplicationVersion("1.0.0");

    Logger::install();
    QObject::connect(&app, &QCoreApplication::aboutToQuit, [](){
        Logger::logExecutionEnd();
    });

    QQmlApplicationEngine engine;
    ApplicationController controller;
    controller.initialize(&engine);

    const QUrl url(QStringLiteral("qrc:/EarEEG_DemoApp/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) {
                qWarning() << "QML load failed for: " << objUrl;
                QCoreApplication::exit(-1);
            };
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
