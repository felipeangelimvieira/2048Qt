#include "game.h"
#include <QObject>
#include <QDebug>
#include <QVector>
#include <QtGlobal>
#include <time.h>

// default constructor
Game::Game(QObject *parent) : QObject(parent)
{    

}

// contructeur que prend en compte le context de l'application
Game::Game(QQmlContext* context ,QObject *parent) : QObject(parent)
{
    //on attache le nom "game" dans le QML à cette instance
    // de Game
     context->setContextProperty("game",this);
     gameContext = context;
}

void Game::start()
{


    //Initialisation du damier
    QVector<QVector<Cell*>> vecCell =  QVector<QVector<Cell*>>(4,QVector<Cell*>(4));
    QVector<QVector<QPointF>> vecPos =  QVector<QVector<QPointF>>(4,QVector<QPointF>(4));
    this->board = vecCell;
    this->boardPositions = vecPos;
    this->turn = 0;
    this->myMemory.firstPlay = NULL;
    this->myMemory.lastPlay = NULL;

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

    // définition du score, du best et tirage au sort
    // de deux cellules
    setScore(0);
    setBest(0);
    fillRandom();
    fillRandom();
    saveMemory();
    updatePositions();

}

// cherche une cellule vide et attribue
// une valeur à cette cellule
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
        time_t seconds;
        seconds = time(NULL);

        long int t = static_cast<long int>(seconds);
        int q1 = t%emptyCells.size();
        Cell* c1 = emptyCells[q1];

        //valeurs aléatoires
        int v1 = qrand()%5;
        if (v1<4){v1 = 2;}
        else  { v1 = 4;}
        c1->setValue(v1);
    }

}

// déplace une cellule de (xi,yi) à (xf,yf)
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

    // on change le placement de la cellule à (xi,yi)
    // avec la position de celle à (xf,yf)
    Cell* temp = board[xf][yf];
    board[xf][yf] = board[xi][yi];
    board[xi][yi] = temp;
    somethingChanged = true;
}

// vider une cellule
void Game::emptyCell(int i, int j)
{
    board[i][j]->setValue(0);
}

// fonction appellé au moment que l'interface QML
// reçoit l'event de clic du boutton à droit
void Game::moveRight()
{
    somethingChanged = false;
    handleRight();
    updatePositions();
    if (somethingChanged){
        fillRandom();
        deletePlaysAfter();
        turn++;
        saveMemory();
    }
}

// similairement, appellée quand l'interface
// reçoit l'event du clic du boutton gauche
void Game::moveLeft()
{
    somethingChanged = false;
    handleLeft();
    updatePositions();
    if (somethingChanged){
        fillRandom();
        deletePlaysAfter();
        turn++;
        saveMemory();
    }
}

// boutton Up
void Game::moveUp()
{
    somethingChanged = false;
    handleUp();
    updatePositions();
    if (somethingChanged){
        fillRandom();
        deletePlaysAfter();
        turn++;
        saveMemory();
    }
}

//boutton down
void Game::moveDown()
{
    somethingChanged = false;
    handleDown();
    updatePositions();
    if (somethingChanged){
        fillRandom();
        deletePlaysAfter();
        turn++;
        saveMemory();
    }

}

// gestion des mouvement des cellules vers la droite
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
                // si cette cellule peut sommer avec celle plus à droite
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
                // si cette cellule ne peut pas être sommée avec celle plus à droite...
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
            // si cette cellule est le trou plus à droite
            else if(holeToTheRight[0] == -1)
            {
                holeToTheRight[0] = i;
                holeToTheRight[1] = j;
            }
        }
    }

}

// gestion des mouvement des cellules vers la gauche
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


// gestion des mouvement des cellules vers le haut
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

// gestion des mouvement des cellules vers le bas
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

// vérifie si les cellules à (xi,yi) et (xf,yf) peuvent
// être sommées
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

// recommence le jeu
void Game::newGame(){
    setGameOver(false);
    for (int i = 0;i<4;i++)
    {
        for (int j = 0;j < 4;j++)
        {
            if (board[i][j]->getVal() >0)
            {
            emptyCell(i,j);
            }
        }
    }

    //on revient aux configurations initiales
    fillRandom();
    fillRandom();
    setScore(0);
    deleteAll();
    turn = 0;
    saveMemory();
}

// marche-arrière
void Game::returnArrow(){
    Play* reach;

    if(turn == 0)
    {
        return;
    }

    turn--;
    int count;

    if(turn > lastTurnS/2)
    {
        count = lastTurnS;
        reach = myMemory.lastPlay;

        while(count != turn)
        {
            reach = reach->prePlay;
            count--;
        }

        for (int i = 0;i < 4;i++)
        {
            for (int j = 0;j < 4;j++)
            {
                board[i][j]->setValue(reach->playMemory[i][j]);
            }
        }
    }
    else
    {
        count = 0;
        reach = myMemory.firstPlay;

        while(count != turn)
        {
            reach = reach->nextPlay;
            count++;
        }

        for (int i = 0;i < 4;i++)
        {
            for (int j = 0;j < 4;j++)
            {
                board[i][j]->setValue(reach->playMemory[i][j]);
            }
        }
    }
    updatePositions();
    setScore(reach->playScore);
}

// reprendre la main sur la partie à l'endroit où il se trouve
void Game::forwardArrow(){
    Play* reach;

    if(turn == lastTurnS)
    {
        return;
    }

    turn++;
    int count;

    if(turn > lastTurnS/2)
    {
        count = lastTurnS;
        reach = myMemory.lastPlay;

        while(count != turn)
        {
            reach = reach->prePlay;
            count--;
        }

        for (int i = 0;i < 4;i++)
        {
            for (int j = 0;j < 4;j++)
            {
                board[i][j]->setValue(reach->playMemory[i][j]);
            }
        }
    }
    else
    {
        count = 0;
        reach = myMemory.firstPlay;

        while(count != turn)
        {
            reach = reach->nextPlay;
            count++;
        }

        for (int i = 0;i < 4;i++)
        {
            for (int j = 0;j < 4;j++)
            {
                board[i][j]->setValue(reach->playMemory[i][j]);
            }
        }
    }
    updatePositions();
    setScore(reach->playScore);
}

void Game::saveMemory(){
    Play* p;
    p = new Play;
    p->playMemory = new int*[4];
    p->playScore = scoreVal;

    for (int i = 0; i < 4; ++i)
        p->playMemory[i] = new int[4];

    for (int i = 0;i < 4;i++)
    {
        for (int j = 0;j < 4;j++)
        {
            p->playMemory[i][j] = board[i][j]->getVal();
        }
    }
    qDebug() << "CRIANDO :" << p;


    if(myMemory.firstPlay == NULL)
    {
        p->prePlay = NULL;
        p->nextPlay = NULL;
        myMemory.firstPlay = p;
        myMemory.lastPlay = p;
        qDebug() << "Pre Play 1: " << myMemory.lastPlay->prePlay;
        qDebug() << "Play " << myMemory.lastPlay;
        qDebug() << "Next Play 1: " << myMemory.lastPlay->nextPlay;
    }
    else{
        p->prePlay = myMemory.lastPlay;

        p->nextPlay = NULL;
        myMemory.lastPlay->nextPlay = p;
        myMemory.lastPlay = p;
        qDebug() << "Pre Play 1: " << myMemory.lastPlay->prePlay;
        qDebug() << "Play " << myMemory.lastPlay;
        qDebug() << "Next Play 1: " << myMemory.lastPlay->nextPlay;
    }


    lastTurnS = turn;
}

void Game::deletePlaysAfter(){
    Play* r;
    Play* pre;
    int count = lastTurnS;

    r = myMemory.lastPlay;

    while(count > turn)
    {
        pre = r->prePlay;
        for (int i = 0; i < 4; ++i)
            delete [] r->playMemory[i];
        qDebug() << "DELETE PLAYS AFTER: " << r;
        delete [] r->playMemory;
        delete r->nextPlay;
        delete r;
        r = pre;
        count--;
    }
    myMemory.lastPlay = r;
    r->nextPlay = NULL;
}

void Game::deleteAll(){

        Play* r;
        Play *pre;


        r = myMemory.lastPlay;

        while(r != NULL)
        {
            pre = r->prePlay;
            for (int i = 0; i < 4; ++i)
                delete [] r->playMemory[i];
            qDebug() << "Delete All : r= " << r << ", pre = " << pre;
            delete [] r->playMemory;
            delete r->nextPlay;
            delete r;
            r = pre;

        }

    myMemory.firstPlay = NULL;
    myMemory.lastPlay = NULL;
}

//communication du score avec l'interface QML
QString Game::score(){
    QString s = QString::number(scoreVal);
    return s;
}

//définition du nouveau score
void Game::setScore(int i){
    QString s = QString::number(i);
    scoreVal = i;
    if (scoreVal > bestVal)
    {
        setBest(scoreVal);
    }
    setScore(s);
}

//définition du nouveau score et
// émission du signal
void Game::setScore(QString str){
    Q_UNUSED(str);
    emit scoreChanged();
}

// communication du best avec l'interface QML
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
    Q_UNUSED(str);
    emit bestChanged();
}

//changement des coordonnées X et Y des cellules
// à partir des nouvelles positions
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

// communication de la fin du jeu
// à l'interface QML
bool Game::gameOver(){
    return gameOverVal;

}

void Game::setGameOver(bool b){
    gameOverVal = b;
    emit gameOverChanged();
}


// vérifie si on est arrivé
// à la fin du jeu (si on a perdu)
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

