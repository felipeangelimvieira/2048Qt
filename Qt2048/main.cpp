#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QUrl>
#include <QStringLiteral>
#include <QQuickView>
#include <QQUickItem>
#include <QDebug>
#include "game.h"
#include "Cell.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();

    Game game(context);
    game.start();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *root = engine.rootObjects()[0];




    /*


    QQmlEngine engine;
    QQmlContext *objectContext = new QQmlContext(engine.rootContext());

    QQmlComponent container(&engine, QUrl(QStringLiteral("qrc:/main.qml")));
    qDebug() << container.errorString();
    QObject *windowObj = container.create(objectContext);

    Game *game;
    game->start();
*/

    return app.exec();
}
