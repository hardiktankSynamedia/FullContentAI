#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "blackscreenview.h"
#include <QQuickWindow>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Register the types with QML
    qmlRegisterType<CustomTextPainter>("CustomControls", 1, 0, "CustomTextPainter");
    qmlRegisterType<BlackScreenView>("CustomControls", 1, 0, "BlackScreenView");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        qDebug() << "Failed to load QML";
        return -1;
    }

    return app.exec();
}
