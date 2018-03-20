#include "Cell.h"
#include <QDebug>

Cell::Cell(QObject *parent) : QObject(parent)
{

}

Cell::Cell(int v,QObject *parent)
{
    this->val = v;
    col = "#d4ccc4";
    qDebug() << "Cell created. Val = " << val;
}

void Cell::setValue(int i)
{
    this->setValue(QString::number(i));
    QColor c;
    switch (val)
    {
        case 0: c = QColor("#d4ccc4");
        break;
        case 2: c = QColor(238,228,218);
        break;
        case 4: c = QColor(237,224,200);
        break;
        case 8: c = QColor(242,177,121);
        break;
        case 16: c = QColor(245,150,100);
        break;
        case 32: c = QColor(245,125,95);
        break;
        case 64: c = QColor(245,95,60);
        break;
        case 128: c = QColor(237,207,114);
        break;
        case 256: c = QColor(237,204,97);
        break;
        case 512: c = QColor(237,204,97);
        break;
        case 1024: c = QColor(237,204,97);
        break;
        case 2048: c = QColor(237,204,97);
        break;
    }

    setColor(c);
}


void Cell::setValue(QString str)
{
    val = str.toInt();
    emit valueChanged();
}

QString Cell::value()
{
   QString s = QString::number(val);
   if (val == 0) {s = "";}
   return s;
}

void Cell::setColor(QColor c)
{
    col = c;
    qDebug()<< val;
    qDebug()<< col;
    emit colorChanged();
}

QColor Cell::color()
{
   return col;
}

int Cell::getVal()
{
    return val;
}

bool Cell::isEmpty()
{
    return (val == 0);
}

bool Cell::notEmpty()
{
    return (val != 0);
}
