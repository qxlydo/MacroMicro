// "qrc:/qt/qml/MegaByte_Finder/Main.qml"

#include <QApplication> 
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "MegaByteFinder.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); 
    QQmlApplicationEngine engine;

    MMEngine mmEngine;
    engine.rootContext()->setContextProperty("engine", &mmEngine);

    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/MegaByte_Finder/Main.qml")));

    return app.exec();
}
