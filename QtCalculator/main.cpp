#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQuickView>

#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDebug>

#include <QQuickStyle>
#include <QQmlContext>
#include <QException>
//#define IMPORT_MODULE
//#include "BigInteger.cpp"
//#include "BST.cpp"
//#include "LinkedList.cpp"
//#include "OrderedList.cpp"
#include "QmlInterface.h"
extern QObject* rootobj;
QObject* rootobj;
int main(int argc, char *argv[])
try
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
//    qputenv("QT_QUICK_CONTROLS_STYLE", "material");
//    QQuickStyle::setStyle("Material"); //mdc牛逼
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QmlInterface data_mgr;
        engine.rootContext()->setContextProperty("QI", &data_mgr);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    rootobj=engine.rootObjects().at(0);

    return app.exec();
}
catch (QException &e){
    qDebug() << e.what();
    return 1;
}
