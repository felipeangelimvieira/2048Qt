#include "grid.h"
#include <QKeyEvent>
#include "cell.h"
#include "QDebug"
#include "game.h"
#include "damierexc.h"

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


    Cell *cell1 = new Cell(gridPositions[0][0][0],gridPositions[0][0][1],4);

    gridCells[0][0] = cell1;

    game->scene->addItem(cell1);

    Cell *cell2 = new Cell(gridPositions[2][2][0],gridPositions[2][2][1],2);
    game->scene->addItem(cell2);

    gridCells[2][2] = cell2;

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
                        int cellToTheRight[2] = {i,j};  //on va pas bouger la cellule
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
                                int holeToTheRight[2] = {i2,j};
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
                    int cellToTheRight[2] = {-1};
                }
                else if(holeToTheRight[0] != -1)
                {
                    qDebug() << "moving 2";
                    moveCell(i,j,holeToTheRight[0],holeToTheRight[1]); // on va bouger la cellule
                    cellToTheRight[0] = holeToTheRight[0]; //maintenant elle est dans le trou
                    cellToTheRight[1] = holeToTheRight[1];
                    int holeToTheRight[2] = {-1};

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

}
void Grid::handleUp(){

}
void Grid::handleDown(){

}
void Grid::keyPressEvent(QKeyEvent *e)
{    
    if (e->key() == Qt::Key_Down)
    {   qDebug() << "Key Down";
        for (int i = 0; i<gridCells.size();i++)
        {
            for (int j = gridCells[0].size()-1; j>= 0;j--)
            {
              if (gridCells[i][j] != NULL)
              {
                    moveCell(i,j,i,3);
               }
            }
        }
        updateGrid();
    }
    if (e->key() == Qt::Key_Right)
    { qDebug() << "Key Right";
        handleRight();
        updateGrid();
    }

    if (e->key() == Qt::Key_Left)
    {   qDebug() << "Key Left";
        for (int i = 0; i<gridCells.size();i++)
        {
            for (int j = gridCells[0].size()-1; j>= 0;j--)
            {
                if (gridCells[i][j] != NULL)
                {
                    moveCell(i,j,0,j);
                }
            }
        }
        updateGrid();
    }

    if (e->key() == Qt::Key_Up)
    {   qDebug() << "Key Up";
        for (int i = 0; i<gridCells.size();i++)
        {
            for (int j = 0; j< gridCells.size();j++)
            {
                if (gridCells[i][j] != NULL)
                {
                    moveCell(i,j,i,0);
                }
            }
        }
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
