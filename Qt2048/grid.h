#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QVector>
#include "cell.h"

class Grid: public QGraphicsItem
{
public:
    Grid(int initX, int initY, Cell* &cell, QGraphicsItem* parent = NULL);
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setGridPositions(int w, int h);
    void keyPressEvent(QKeyEvent *e);
    void show();
    void updateGrid();
    void start();
    void emptyGridCell(int i, int j);
    void moveCell(int xi,int yi, int xf, int yf);

    void handleRight();
    void handleLeft();
    void handleUp();
    void handleDown();
    bool canSumUp(int xi, int yi, int xf, int yf);

    QVector<Cell*> cellVector;
    QVector<QVector<QVector<int>>> gridPositions;
    QVector<QVector<Cell*>> gridCells;


    int x0;
    int y0;
};

#endif // GRID_H
