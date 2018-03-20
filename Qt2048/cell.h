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
public:
    explicit Cell(QObject *parent = nullptr);
    Cell(int v,QObject *parent = nullptr);
    QString value();
    QColor color();
    void setValue(int i);
    void setValue(QString str);
    void setColor(QColor c);
    int getVal();
    bool isEmpty();
    bool notEmpty();

signals:
    // changement de la valeur de la case
    void valueChanged();
    void colorChanged();
public slots:

private:
    int val;
    QColor col;
};

#endif // CELL_H
