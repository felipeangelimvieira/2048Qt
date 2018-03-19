#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>

class Game: public QGraphicsView
{
public:

    Game(QWidget* parent = NULL);

    void start();

    QGraphicsScene* scene;
    QGraphicsView* view;

};

#endif // GAME_H
