#ifndef CELL_H
#define CELL_H
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsTextItem>
#include <QDebug>

class Cell: public QGraphicsItem
{
public:
    Cell();
    Cell(const Cell& C, QGraphicsItem* parent = NULL);
    Cell(int x,int y, int val, QGraphicsItem* parent = NULL);

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    Cell& operator=(const Cell &cell);

    //pensar em botar ponteiro
    int value;
};


#endif // CELL_H
