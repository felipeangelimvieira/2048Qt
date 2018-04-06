#ifndef CELL_H
#define CELL_H
#include <QString>
#include <QObject>
#include <QColor>

class Cell : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int xpos READ xpos WRITE setXpos NOTIFY xposChanged)
    Q_PROPERTY(int ypos READ ypos WRITE setYpos NOTIFY yposChanged)
public:
    explicit Cell(QObject *parent = nullptr);
    Cell(int v,QObject *parent = nullptr);

    QString value();
    QColor color();
    int xpos();
    int ypos();

    void setValue(int i);
    void setValue(QString str);
    void setColor(QColor c);
    void setXpos(int i);
    void setYpos(int i);
    int getVal();
    bool isEmpty();
    bool notEmpty();



signals:
    // changement de la valeur de la case
    void valueChanged();
    void colorChanged();
    void xposChanged();
    void yposChanged();

public slots:

private:
    int x;
    int y;
    int val;
    QColor col;
};

#endif // CELL_H
