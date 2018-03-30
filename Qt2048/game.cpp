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
    QVector<QVector<QPointF>> vecPos =  QVector<QVector<QPointF>>(4,QVector<QPointF>(4));
    this->board = vecCell;
    this->boardPositions = vecPos;

    //liason entre les cases QML et la classe Cell C++
    QString s;
    for (int i =0;i<4;i++)
    {
        for (int j = 0; j<4;j++)
        {
            Cell* c = new Cell(0);
            board[i][j] = c;
            s = QString("cell%1").arg(i*4 + j + 1);
            boardPositions[i][j] = QPointF(10 + j*85,10+i*85);
            gameContext->setContextProperty(s,board[i][j]);
        }
    }

    updatePositions();
    setScore(0);
    setBest(0);
    fillRandom();
    fillRandom();


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
    //comment se porter si l'endroit final a déjà une cellule...
    if (board[xf][yf]->getVal() > 0){
        setScore(scoreVal + board[xi][yi]->getVal() + board[xf][yf]->getVal());
    }
    board[xi][yi]->setValue(board[xi][yi]->getVal() + board[xf][yf]->getVal());
    emptyCell(xf,yf);
    Cell* temp = board[xf][yf];
    board[xf][yf] = board[xi][yi];
    board[xi][yi] = temp;
    somethingChanged = true;
}

void Game::emptyCell(int i, int j)
{
    board[i][j]->setValue(0);
}

void Game::moveRight()
{
    somethingChanged = false;
    handleRight();
    updatePositions();
    if (somethingChanged){
    fillRandom();
    }

}

void Game::moveLeft()
{
    somethingChanged = false;
    handleLeft();
    updatePositions();
    if (somethingChanged){
        fillRandom();
    }
}

void Game::moveUp()
{
    somethingChanged = false;
    handleUp();
    updatePositions();
    fillRandom();
    if (somethingChanged){
        fillRandom();
    }
}

void Game::moveDown()
{
    somethingChanged = false;
    handleDown();
    updatePositions();
    if (somethingChanged){
    fillRandom();
    }
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
                    moveCell(i,j,cellBelow[0],cellBelow[1]);
                    cellBelow[0] = {-1};
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
                else if(!canSumUp(i,j,cellBelow[0],cellBelow[1]))
                {
                    cellBelow[0] = i;
                    cellBelow[1] = j;
                    if(holeBelow[0] != -1)
                    {
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

void Game::newGame(){
    setGameOver(false);
    for (int i = 0;i<4;i++)
    {
        for (int j = 0; j<4;j++)
        {
            if (board[i][j]->getVal() >0)
            {
            emptyCell(i,j);
            }
        }
    }
    fillRandom();
    fillRandom();
    setScore(0);
}

QString Game::score(){
    QString s = QString::number(scoreVal);
    return s;
}
void Game::setScore(int i){
    QString s = QString::number(i);
    scoreVal = i;
    if (scoreVal > bestVal)
    {
        setBest(scoreVal);
    }
    setScore(s);
}
void Game::setScore(QString str){
    emit scoreChanged();
}

QString Game::best(){
    QString s = QString::number(bestVal);
    return s;
}
void Game::setBest(int i){
    QString s = QString::number(i);
    bestVal = i;
    setBest(s);
}
void Game::setBest(QString str){
    emit bestChanged();
}

void Game::updatePositions()
{
    for (int i = 0;i<4;i++)
    {
        for (int j = 0; j<4;j++)
        {
            board[i][j]->setXpos(boardPositions[i][j].x());
            board[i][j]->setYpos(boardPositions[i][j].y());
        }
    }
    setGameOver(checkGameOver());
}

bool Game::gameOver(){
    return gameOverVal;

}
void Game::setGameOver(bool b){
    gameOverVal = b;
    emit gameOverChanged();
}

bool Game::checkGameOver(){
    bool gameover = true;

    //check if any cell is empty
    for (int i = 0; i<4;i++)
    {
        for (int j = 0; j<4; j++)
        {
            if (board[i][j]->getVal() == 0)
            {
                gameover = false;
                return gameover;
            }
        }
    }

    //checking horizontal movements
    for (int i = 0; i<4;i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (board[i][j+1]->getVal() == board[i][j]->getVal())
            {
                gameover = false;
                return gameover;
            }
        }
    }

    //checking vertical movements
    for (int j = 0; j<4;j++)
    {
        for (int i = 0; i<3; i++)
        {
            if (board[i+1][j]->getVal() == board[i][j]->getVal())
            {
                gameover = false;
                return gameover;
            }
        }
    }

    return gameover;

}
