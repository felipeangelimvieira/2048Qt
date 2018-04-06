#include "Cell.h"
#include <QDebug>
#include <QtMath>

// constructeur par défault
Cell::Cell(QObject *parent) : QObject(parent)
{

}

//constructer 2
Cell::Cell(int v,QObject *parent)
{
    this->val = v;
    col = "#d4ccc4";
}

// définition de la valeur de la cellule
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
    case 4096: c =  QColor(241,104,112);
        break;
    case 8192: c = QColor(241,75,97);
        break;
    case 16384: c = QColor(239,67,63);
        break;
    case 32768: c = QColor(111,179,216);
        break;
    case 65536: c = QColor(61,153,203);
        break;
    case 131072: c = QColor(0,127,194);

    }

    setColor(c);
}


// communication avec l'QML
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

//Communication de la couleur avec le QML
void Cell::setColor(QColor c)
{
    col = c;
    emit colorChanged();
}

QColor Cell::color()
{
   return col;
}

int Cell::xpos()
{
   return x;
}


// communication du positionnement de la cellule avec le QML
void Cell::setXpos(int i)
{
    x = i;
    emit xposChanged();
}

int Cell::ypos()
{
   return y;
}

void Cell::setYpos(int i)
{
    y = i;
    emit yposChanged();
}


// fonctions auxiliaires
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
