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
#include <QQmlComponent>
#include <QPointF>
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
    QObject* const tableObj = root->findChild<QObject*>("table");
    QQuickItem *table = qobject_cast<QQuickItem*>(tableObj);

    game.attachTable(table);

    QQuickItem *cell = table->findChild<QQuickItem*>(QString("pos1"));
    cell->setParentItem(table);
    //cell->setProperty("xpos",120);

    cell->dumpObjectInfo();

    /*
    qDebug() << child->children().size();
    QQmlComponent component(&engine, "qrc:/Cell.qml");
    if (component.isReady()){
    QObject *object = component.create();
    object->setProperty("z",20);
    object->setParent(child);
    engine.setObjectOwnership(object, engine.CppOwnership);
    object->dumpObjectInfo();
    }



*/





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
