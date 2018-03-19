#include "grid.h"
#include <QKeyEvent>
#include "cell.h"
#include "QDebug"
#include "game.h"


extern Game* game;

void Grid::setGridPositions(int w, int h)
    {
    for (int i = 0; i<4;i++)
    {
        for (int j = 0; j<4;j++)
        {
            int posx = x0 +i*w;
            int posy = y0 + j*h;
            gridPositions[i][j][0] = posx;
            gridPositions[i][j][1] = posy;
        }
    }
}

Grid::Grid(int initX, int initY, Cell* &cell,  QGraphicsItem*  parent): QGraphicsItem(parent)
{
  QVector<QVector<QVector<int>>> vecPos =  QVector<QVector<QVector<int>>>(4,QVector<QVector<int>>(4,QVector <int>(2)));
  QVector<QVector<Cell*>> vecCell =  QVector<QVector<Cell*>>(4,QVector<Cell*>(4));
  this->gridPositions = vecPos;
  this->gridCells = vecCell;

  int w = 40;
  int h = 40;

  x0 = initX;
  y0 = initY;

  setGridPositions(w,h);

  setFlag(QGraphicsItem::ItemIsFocusable,true);
  start();
}

void Grid::start(){


    Cell *cell1 = new Cell(gridPositions[0][3][0],gridPositions[0][3][1],8);
    Cell *cell2 = new Cell(gridPositions[2][2][0],gridPositions[1][3][1],4);
    Cell *cell3 = new Cell(gridPositions[2][3][0],gridPositions[2][3][1],4);
    Cell *cell4 = new Cell(gridPositions[3][3][0],gridPositions[3][3][1],4);

    gridCells[0][3] = cell1;
    gridCells[2][2] = cell2;
    gridCells[2][3] = cell3;
    gridCells[3][3] = cell4;

    game->scene->addItem(cell1);
    game->scene->addItem(cell2);
    game->scene->addItem(cell3);
    game->scene->addItem(cell4);


    updateGrid();


}

void Grid::emptyGridCell(int i, int j)
{

    Cell *p = gridCells[i][j];
    gridCells[i][j] = NULL;
    delete p;
}

void Grid::moveCell(int xi, int yi, int xf, int yf)
{
    if (xf == xi && yf == yi)
    {
        return;
    }
    if (gridCells[xf][yf] != NULL)
        {
            //comment se porter si l'endroit final a déjà une cellule...
            gridCells[xi][yi]->value += gridCells[xf][yf]->value;
            emptyGridCell(xf,yf);
        }
    gridCells[xf][yf] = gridCells[xi][yi];
    gridCells[xi][yi] = NULL;
}

bool Grid::canSumUp(int xi, int yi, int xf, int yf)
{
    Cell *celli = gridCells[xi][yi];
    Cell *cellf = gridCells[xf][yf];
    if (celli->value == cellf->value)
    {
        return true;
    }
    return false;
}

void Grid::handleRight(){
    for (int j = 0;j<4;j++)
    {
        int cellToTheRight[2] = {-1};
        int holeToTheRight[2] = {-1};
        for (int i = 3;i>= 0;i--)
        { qDebug() << holeToTheRight[0];
            // si il y a une valeur...
            if (gridCells[i][j] != NULL)
            {
                // si aucune cellule avec une valeur a été trouvé
                if (cellToTheRight[0] == -1)
                {
                    // si aucun trou a été trouvé
                    if (holeToTheRight[0] == -1)
                    {
                        qDebug() << " Nova celula à direita: " <<i <<", " <<j;
                        cellToTheRight[0] = i;  //on va pas bouger la cellule
                        cellToTheRight[1] = j;
                    }
                    else
                    {
                        qDebug() << "moving 1";
                        moveCell(i,j,holeToTheRight[0],holeToTheRight[1]); // on va bouger la cellule
                        cellToTheRight[0] = holeToTheRight[0]; //maintenant elle est dans le trou
                        cellToTheRight[1] = holeToTheRight[1];
                        for (int i2 = 3; i2>=0;i2--)
                        {
                            if (gridCells[i2][j] == NULL)
                            {
                                qDebug() << "atualizando holetotheright" <<i2;
                                holeToTheRight[0] = i2;
                                holeToTheRight[1] = j;
                                break;
                            }
                        }
                    }
                }
                // si cette cellule peux sommer avec celle plus à droite
                else if(canSumUp(i,j,cellToTheRight[0],cellToTheRight[1]))
                {
                    qDebug() << "can Sum up";
                    moveCell(i,j,cellToTheRight[0],cellToTheRight[1]);
                    cellToTheRight[0] = {-1};
                    for (int i2 = 3; i2>=0;i2--)
                    {
                        if (gridCells[i2][j] == NULL)
                        {
                            qDebug() << "atualizando holetotheright depois de sum up" <<i2;
                            holeToTheRight[0] = i2;
                            holeToTheRight[1] = j;
                            break;
                        }
                    }
                }
                else if(!canSumUp(i,j,cellToTheRight[0],cellToTheRight[1]))
                {
                    cellToTheRight[0] = i;
                    cellToTheRight[1] = j;
                    if(holeToTheRight[0] != -1)
                    {
                        qDebug() << "moving 2";
                        moveCell(i,j,holeToTheRight[0],holeToTheRight[1]); // on va bouger la cellule
                        cellToTheRight[0] = holeToTheRight[0]; //maintenant elle est dans le trou
                        cellToTheRight[1] = holeToTheRight[1];
                        holeToTheRight[0] = {-1};

                    }
                }
            }
            else if(holeToTheRight[0] == -1)
            {
                holeToTheRight[0] = i;
                holeToTheRight[1] = j;
            }
        }
    }
}
void Grid::handleLeft(){
    for (int j = 0;j<4;j++)
    {
        int cellToTheLeft[2] = {-1};
        int holeToTheLeft[2] = {-1};
        for (int i = 0;i<4;i++)
        {   // si il y a une valeur...
            if (gridCells[i][j] != NULL)
            {
                // si aucune cellule avec une valeur a été trouvé
                if (cellToTheLeft[0] == -1)
                {
                    // si aucun trou a été trouvé
                    if (holeToTheLeft[0] == -1)
                    {
                        cellToTheLeft[0] = i;  //on va pas bouger la cellule
                        cellToTheLeft[1] = j;
                    }
                    else
                    {
                        qDebug() << "moving 1";
                        moveCell(i,j,holeToTheLeft[0],holeToTheLeft[1]); // on va bouger la cellule
                        cellToTheLeft[0] = holeToTheLeft[0]; //maintenant elle est dans le trou
                        cellToTheLeft[1] = holeToTheLeft[1];
                        for (int i2 = 0; i2 < 4;i2++)
                        {
                            if (gridCells[i2][j] == NULL)
                            {
                                holeToTheLeft[0] = i2;
                                holeToTheLeft[1] = j;
                                break;
                            }
                        }
                    }
                }
                // si cette cellule peux sommer avec celle plus à droite
                else if(canSumUp(i,j,cellToTheLeft[0],cellToTheLeft[1]))
                {
                    qDebug() << "can Sum up";
                    moveCell(i,j,cellToTheLeft[0],cellToTheLeft[1]);
                    cellToTheLeft[0] = {-1};
                    for (int i2 = 0; i2 < 4;i2++)
                    {
                        if (gridCells[i2][j] == NULL)
                        {
                            qDebug() << "atualizando holetotheright depois de sum up" <<i2;
                            holeToTheLeft[0] = i2;
                            holeToTheLeft[1] = j;
                            break;
                        }
                    }
                }
                else if(!canSumUp(i,j,cellToTheLeft[0],cellToTheLeft[1]))
                {
                    cellToTheLeft[0] = i;
                    cellToTheLeft[1] = j;
                    if(holeToTheLeft[0] != -1)
                    {
                        qDebug() << "moving 2";
                        moveCell(i,j,holeToTheLeft[0],holeToTheLeft[1]); // on va bouger la cellule
                        cellToTheLeft[0] = holeToTheLeft[0]; //maintenant elle est dans le trou
                        cellToTheLeft[1] = holeToTheLeft[1];
                        holeToTheLeft[0] = {-1};

                    }
                }
            }
            else if(holeToTheLeft[0] == -1)
            {
                holeToTheLeft[0] = i;
                holeToTheLeft[1] = j;
            }
        }
    }

}
void Grid::handleUp(){
    for (int i = 0;i<4;i++)
    {
        int cellAbove[2] = {-1};
        int holeAbove[2] = {-1};
        for (int j = 0;j<4;j++)
        {   // si il y a une valeur...
            if (gridCells[i][j] != NULL)
            {
                // si aucune cellule avec une valeur a été trouvé
                if (cellAbove[0] == -1)
                {
                    // si aucun trou a été trouvé
                    if (holeAbove[0] == -1)
                    {
                        cellAbove[0] = i;  //on va pas bouger la cellule
                        cellAbove[1] = j;
                    }
                    else
                    {
                        qDebug() << "moving 1";
                        moveCell(i,j,holeAbove[0],holeAbove[1]); // on va bouger la cellule
                        cellAbove[0] = holeAbove[0]; //maintenant elle est dans le trou
                        cellAbove[1] = holeAbove[1];
                        for (int j2 = 0; j2 < 4;j2++)
                        {
                            if (gridCells[i][j2] == NULL)
                            {
                                holeAbove[0] = i;
                                holeAbove[1] = j2;
                                break;
                            }
                        }
                    }
                }
                // si cette cellule peux sommer avec celle plus à droite
                else if(canSumUp(i,j,cellAbove[0],cellAbove[1]))
                {
                    qDebug() << "can Sum up";
                    moveCell(i,j,cellAbove[0],cellAbove[1]);
                    cellAbove[0] = {-1};
                    for (int j2 = 0; j2 < 4;j2++)
                    {
                        if (gridCells[i][j2] == NULL)
                        {
                            holeAbove[0] = i;
                            holeAbove[1] = j2;
                            break;
                        }
                    }
                }
                else if(!canSumUp(i,j,cellAbove[0],cellAbove[1]))
                {
                    cellAbove[0] = i;
                    cellAbove[1] = j;
                    if(holeAbove[0] != -1)
                    {
                        qDebug() << "moving 2";
                        moveCell(i,j,holeAbove[0],holeAbove[1]); // on va bouger la cellule
                        cellAbove[0] = holeAbove[0]; //maintenant elle est dans le trou
                        cellAbove[1] = holeAbove[1];
                        holeAbove[0] = {-1};

                    }
                }
            }
            else if(holeAbove[0] == -1)
            {
                holeAbove[0] = i;
                holeAbove[1] = j;
            }
        }
    }


}
void Grid::handleDown(){

    for (int i = 0;i<4;i++)
    {
        int cellBelow[2] = {-1};
        int holeBelow[2] = {-1};
        for (int j = 3;j>=0;j--)
        {   // si il y a une valeur...
            if (gridCells[i][j] != NULL)
            {
                // si aucune cellule avec une valeur a été trouvé
                if (cellBelow[0] == -1)
                {
                    // si aucun trou a été trouvé
                    if (holeBelow[0] == -1)
                    {
                        cellBelow[0] = i;  //on va pas bouger la cellule
                        cellBelow[1] = j;
                    }
                    else
                    {
                        qDebug() << "moving 1";
                        moveCell(i,j,holeBelow[0],holeBelow[1]); // on va bouger la cellule
                        cellBelow[0] = holeBelow[0]; //maintenant elle est dans le trou
                        cellBelow[1] = holeBelow[1];
                        for (int j2 = 3;j2>=0;j2--)
                        {
                            if (gridCells[i][j2] == NULL)
                            {
                                holeBelow[0] = i;
                                holeBelow[1] = j2;
                                break;
                            }
                        }
                    }
                }
                // si cette cellule peux sommer avec celle plus à droite
                else if(canSumUp(i,j,cellBelow[0],cellBelow[1]))
                {
                    qDebug() << "can Sum up";
                    moveCell(i,j,cellBelow[0],cellBelow[1]);
                    cellBelow[0] = {-1};
                    for (int j2 = 3;j2>=0;j2--)
                    {
                        if (gridCells[i][j2] == NULL)
                        {
                            holeBelow[0] = i;
                            holeBelow[1] = j2;
                            break;
                        }
                    }
                }
                else if(!canSumUp(i,j,cellBelow[0],cellBelow[1]))
                {
                    cellBelow[0] = i;
                    cellBelow[1] = j;
                    if(holeBelow[0] != -1)
                    {
                        qDebug() << "moving 2";
                        moveCell(i,j,holeBelow[0],holeBelow[1]); // on va bouger la cellule
                        cellBelow[0] = holeBelow[0]; //maintenant elle est dans le trou
                        cellBelow[1] = holeBelow[1];
                        holeBelow[0] = {-1};

                    }
                }
            }
            else if(holeBelow[0] == -1)
            {
                holeBelow[0] = i;
                holeBelow[1] = j;
            }
        }
    }
}
void Grid::keyPressEvent(QKeyEvent *e)
{    
    if (e->key() == Qt::Key_Down)
    {   qDebug() << "Key Down";
        handleDown();
        updateGrid();
    }
    if (e->key() == Qt::Key_Right)
    { qDebug() << "Key Right";
        handleRight();
        updateGrid();
    }

    if (e->key() == Qt::Key_Left)
    {   qDebug() << "Key Left";
        handleLeft();
        updateGrid();
    }

    if (e->key() == Qt::Key_Up)
    {   qDebug() << "Key Up";
        handleUp();
        updateGrid();
    }
}


QRectF Grid::boundingRect() const
{
    return QRectF(x(),y(),30,30);
}



void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(painter);
}

void Grid::show()
{
    QGraphicsItem::show();
}
void Grid::updateGrid()
{
    qDebug() << "Updating grid...";
    for (int i = 0; i<gridCells.size();i++)
    {
        for (int j = 0; j<gridCells[0].size();j++)
        {   if (gridCells[i][j] != NULL)
            {
                gridCells[i][j]->setPos(gridPositions[i][j][0],gridPositions[i][j][1]);
            }
        }
    }
    qDebug() << "Grid updated";
}
