#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QQmlContext>
#include <QVector>

#include "cell.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    Game(QQmlContext* context,QObject *parent = nullptr);
    void start();
    void fillRandom();

    void moveCell(int xi, int yi, int xf, int yf);
    void handleRight();
    void handleLeft();
    void handleUp();
    void handleDown();
    bool canSumUp(int xi, int yi, int xf, int yf);
    void emptyCell(int i, int j);

private:
    QQmlContext* gameContext;
    QVector<QVector<Cell*>> board;
signals:

public slots:
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
};

#endif // GAME_H
