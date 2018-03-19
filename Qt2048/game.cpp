#include "game.h"
#include "cell.h"
#include "grid.h"
#include <QDebug>

Game::Game(QWidget *parent): QGraphicsView(parent)
{
    //Ajoutant une scene...
    scene = new QGraphicsScene(0,0,400,600);
    setScene(scene);

    //Ajoutant une view...
    view = new QGraphicsView(scene);
    view->show();
}

void Game::start()
{
    qDebug() << "Starting Game...";
    int x = 0;
    int y = 0;
    int val = 4;
    Cell *cell =  new Cell(x,y,val);
    //scene->addItem(cell);
    Grid *grid = new Grid(x,y,cell);
    qDebug() << "Bornes: " << x <<", " << y;
    scene->addItem(grid);
    grid->show();
    grid->setFocus();



}
