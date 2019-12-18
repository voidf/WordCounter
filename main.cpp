#include <QGuiApplication>

#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDebug>

#include <QQuickStyle>
#include <QQmlContext>
#include "link.h"
extern QObject* rootobj;
QObject* rootobj;

int main(int argc, char *argv[])
{
    qputenv("QT_QUICK_CONTROLS_STYLE", "material");
    QQuickStyle::setStyle("Material"); //mdc牛逼

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    int fontId = QFontDatabase::addApplicationFont("./fonts/PingFang Regular.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font(fontFamilies.at(0));
    //font.setFamily("PingFang SC Medium");//设置全局字体
    app.setFont(font);

    QDataMgr data_mgr;
    engine.rootContext()->setContextProperty("DATAMGR", &data_mgr);
    //engine.addImportPath( ":/qml/" );
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     },
                     Qt::QueuedConnection);
    engine.load(url);
    rootobj=engine.rootObjects().at(0);

    return app.exec();
}
