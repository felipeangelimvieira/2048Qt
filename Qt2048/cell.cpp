#include "cell.h"
#include <QString>
#include <QDebug>

Cell::Cell()
{

}

Cell::Cell(int x1, int y1, int val, QGraphicsItem*  parent): QGraphicsItem(parent)
{
    value = val;
    setPos(x1,y1);
}

Cell::Cell(const Cell& C, QGraphicsItem* parent): QGraphicsItem(parent)
{
    this->value = C.value;
    setPos(C.x(),C.y());
}

//création des bornes de l'objet graphique
QRectF Cell::boundingRect() const
{
    return QRectF(x(),y(),30,30);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    qDebug() << "Coordinates: "<<QString::number(x());
    QRectF boundaries = boundingRect();
    QBrush brush;
    brush.setColor(Qt::green);
    if (value == 0)
    {
    painter->setBrush(Qt::blue);
    }
    else
    {
    painter->setBrush(Qt::green);
    }
    painter->drawRoundedRect(x(),y(),30,30,5,5);
    painter->drawText(boundaries,Qt::AlignCenter,QString::number(value));


}

Cell& Cell::operator=(const Cell &cell)
{
    this->value = cell.value;
    this->setPos(cell.x(),cell.y());
    return *this;
}

Cell &Cell::operator+=(const Cell &cell)
{
    this->value += cell.value;
    return *this;
}
