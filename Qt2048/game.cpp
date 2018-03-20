#include "game.h"
#include <QObject>
#include <QDebug>
#include <QVector>
#include <QtGlobal>

Game::Game(QObject *parent) : QObject(parent)
{    

}

Game::Game(QQmlContext* context ,QObject *parent) : QObject(parent)
{
     context->setContextProperty("game",this);
     gameContext = context;
}

void Game::start()
{


    //le damier
    QVector<QVector<Cell*>> vecCell =  QVector<QVector<Cell*>>(4,QVector<Cell*>(4));
    this->board = vecCell;

    //liason entre les cases QML et la classe Cell C++
    QString s;
    for (int i =0;i<4;i++)
    {
        for (int j = 0; j<4;j++)
        {
            Cell* c = new Cell(0);
            board[i][j] = c;
            s = QString("cell%1").arg(i*4 + j + 1);
            qDebug() << s;
            gameContext->setContextProperty(s,board[i][j]);
        }
    }
    board[1][3]->setValue(16);
    board[2][3]->setValue(16);
    board[3][3]->setValue(16);
    board[0][3]->setValue(16);
    //fillRandom();
    //fillRandom();


}

void Game::fillRandom()
{   QVector<Cell*> emptyCells;
    for (int i = 0; i<4;i++)
    {
        for (int j = 0; j < 4; j++)
        {
           if (board[i][j]->getVal() == 0)
           {
               emptyCells.append(board[i][j]);
           }
        }
    }

    if (emptyCells.size()>0)
    {
        //cases aléatoires
        int q1 = qrand()%(emptyCells.size());
        Cell* c1 = emptyCells[q1];

        //valeurs aléatoires
        int v1 = qrand()%5;
        if (v1<4){v1 = 2;}
        else  { v1 = 4;}
        c1->setValue(v1);
    }

}

void Game::moveCell(int xi, int yi, int xf, int yf)
{
    if (xf == xi && yf == yi)
    {
        return;
    }
    qDebug() << xi << ", " << yi << ", " << xf << ", " << yf;
    //comment se porter si l'endroit final a déjà une cellule...
    board[xf][yf]->setValue(board[xi][yi]->getVal() + board[xf][yf]->getVal());
    emptyCell(xi,yi);

}

void Game::emptyCell(int i, int j)
{
    board[i][j]->setValue(0);
}

void Game::moveRight()
{
    qDebug() << "Right arrow pressed";
    handleRight();
    fillRandom();
}

void Game::moveLeft()
{
    qDebug() << "Left arrow pressed";
    handleLeft();
    fillRandom();
}

void Game::moveUp()
{
    qDebug() << "Up arrow pressed";
    handleUp();
    fillRandom();
}

void Game::moveDown()
{
    qDebug() << "Down arrow pressed";
    handleDown();
    fillRandom();
}

void Game::handleRight()
{
    for (int i = 0;i<4;i++)
    {
        int cellToTheRight[2] = {-1};
        int holeToTheRight[2] = {-1};
        for (int j = 3;j>= 0;j--)
        {
            // si il y a une valeur...
            if (board[i][j]->notEmpty())
            {
                // si aucune cellule avec une valeur a été trouvé
                if (cellToTheRight[0] == -1)
                {
                    // si aucun trou a été trouvé
                    if (holeToTheRight[0] == -1)
                    {
                        cellToTheRight[0] = i;  //on va pas bouger la cellule
                        cellToTheRight[1] = j;
                    }
                    else
                    {
                        moveCell(i,j,holeToTheRight[0],holeToTheRight[1]); // on va bouger la cellule
                        cellToTheRight[0] = holeToTheRight[0]; //maintenant elle est dans le trou
                        cellToTheRight[1] = holeToTheRight[1];
                        for (int j2 = 3; j2>=0;j2--)
                        {
                            if (board[i][j2]->isEmpty())
                            {
                                holeToTheRight[0] = i;
                                holeToTheRight[1] = j2;
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
                    for (int j2 = 3; j2>=0;j2--)
                    {
                        if (board[i][j2]->isEmpty())
                        {
                            holeToTheRight[0] = i;
                            holeToTheRight[1] = j2;
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

void Game::handleLeft()
{
    for (int i = 0;i<4;i++)
    {
        int cellToTheLeft[2] = {-1};
        int holeToTheLeft[2] = {-1};
        for (int j = 0;j<4;j++)
        {   // si il y a une valeur...
            if (board[i][j]->notEmpty())
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
                        moveCell(i,j,holeToTheLeft[0],holeToTheLeft[1]); // on va bouger la cellule
                        cellToTheLeft[0] = holeToTheLeft[0]; //maintenant elle est dans le trou
                        cellToTheLeft[1] = holeToTheLeft[1];
                        for (int j2 = 0; j2 < 4;j2++)
                        {
                            if (board[i][j2]->isEmpty())
                            {
                                holeToTheLeft[0] = i;
                                holeToTheLeft[1] = j2;
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
                    for (int j2 = 0; j2 < 4;j2++)
                    {
                        if (board[i][j2]->isEmpty())
                        {
                            holeToTheLeft[0] = i;
                            holeToTheLeft[1] = j2;
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

void Game::handleUp()
{
    for (int j = 0;j<4;j++)
    {
        int cellAbove[2] = {-1};
        int holeAbove[2] = {-1};
        for (int i = 0;i<4;i++)
        {   // si il y a une valeur...
            if (board[i][j]->notEmpty())
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
                        for (int i2 = 0; i2 < 4;i2++)
                        {
                            if (board[i2][j]->isEmpty())
                            {
                                holeAbove[0] = i2;
                                holeAbove[1] = j;
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
                    for (int i2 = 0; i2 < 4;i2++)
                    {
                        if (board[i2][j]->isEmpty())
                        {
                            holeAbove[0] = i2;
                            holeAbove[1] = j;
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

void Game::handleDown()
{
    for (int j = 0;j<4;j++)
    {
        int cellBelow[2] = {-1};
        int holeBelow[2] = {-1};
        for (int i = 3;i>=0;i--)
        {   // si il y a une valeur...
            if (board[i][j]->notEmpty())
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
                        for (int i2 = 3;i2>=0;i2--)
                        {
                            if (board[i2][j]->isEmpty())
                            {
                                holeBelow[0] = i2;
                                holeBelow[1] = j;
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
                    for (int i2 = 3;i2>=0;i2--)
                    {
                        if (board[i2][j]->isEmpty())
                        {
                            qDebug()<<"somou: " << i2<<", "<<j;
                            holeBelow[0] = i2;
                            holeBelow[1] = j;
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

bool Game::canSumUp(int xi, int yi, int xf, int yf)
{
    Cell *celli = board[xi][yi];
    Cell *cellf = board[xf][yf];
    if (celli->getVal() == cellf->getVal())
    {
        return true;
    }
    return false;
}
