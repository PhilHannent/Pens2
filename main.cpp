#include <QApplication>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>

#include "mainwindow.h"

int main(int argc, char * argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QLoggingCategory("qml").setEnabled(QtDebugMsg, true);

    QApplication app(argc, argv);

    /*
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }
    */

    MainWindow window;
    window.show();

    return app.exec();
}
