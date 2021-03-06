#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QQmlContext>
#include <QVector>
#include <QQuickItem>

#include "cell.h"

typedef struct play {
    int** playMemory;
    struct play* nextPlay;
    struct play* prePlay;
    int playScore;
} Play;

typedef struct memory {
    Play* firstPlay;
    Play* lastPlay;
} Memory;

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString score READ score WRITE setScore NOTIFY scoreChanged)
    Q_PROPERTY(QString best READ best WRITE setBest NOTIFY bestChanged)
    Q_PROPERTY(bool gameOver READ gameOver WRITE setGameOver NOTIFY gameOverChanged)

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

    QString score();
    void setScore(int i);
    void setScore(QString str);

    QString best();
    void setBest(int i);
    void setBest(QString str);

    bool gameOver();
    void setGameOver(bool b);


    void updatePositions();
    bool checkGameOver();

    void saveMemory();

    void deletePlaysAfter();
    void deleteAll();

private:
    QQmlContext* gameContext;
    QQuickItem* parentTable;
    QVector<QVector<Cell*>> board;
    int scoreVal;
    int bestVal;
    bool gameOverVal;
    bool somethingChanged;
    QVector<QVector<QPointF>> boardPositions;
    int turn;
    Memory myMemory;
    int lastTurnS;

signals:
    void scoreChanged();
    void bestChanged();
    void gameOverChanged();
public slots:
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void newGame();
    void returnArrow();
    void forwardArrow();
};

#endif // GAME_H
