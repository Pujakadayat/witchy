#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false),score(0),
    bestscore(0)
{

    setUpPillarTimer();
}

void Scene::addBird()
{
    bird= new BirdItem(QPixmap(":/image/w3.png"));
    addItem(bird);

}


void Scene::startGame()
{
    //Bird
    bird->startFlying();
    //Pillars
    if(!pillarTimer->isActive()){
        cleanPillars();
        setGameOn(true);
        hideGameOvergraphics();
        pillarTimer->start(1000);
    }
}


void Scene::setUpPillarTimer()
{
    pillarTimer =  new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=]()
    {
        PillarItem * pillarItem = new PillarItem();
        connect(pillarItem,&::PillarItem::collidefail,[=](){
            pillarTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);
            showGameOverGraphics();
        });
        addItem(pillarItem);
    });

    pillarTimer->start(1000);

}

void Scene::freezeBirdAndPillarsInPlace()
{
    //freeze bird
    bird->freezeInPlace();
    //freeze pillars
    QList<QGraphicsItem *>sceneItems = items();
    foreach(QGraphicsItem * items,sceneItems){

        PillarItem * pillar = dynamic_cast<PillarItem*>(items);
        if(pillar){
            pillar->freezeInPlace();
        }
    }
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool newGameOn)
{
    gameOn = newGameOn;
}

void Scene::incrementScore()
{
    score++;
    if(score> bestscore)
        bestscore = score;
    qDebug() << "Score:" <<score << "Best Score:"<< bestscore;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        if(gameOn){
            bird->shootup();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}
void Scene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if(event->button() == Qt::LeftButton){
        if(gameOn){
            bird->shootup(); }
    }
}

void Scene::showGameOverGraphics()
{
    gameOverPix = new QGraphicsPixmapItem(QPixmap(":/image/gameover.png"));
    addItem(gameOverPix);
    gameOverPix-> setPos(QPointF(0,0) - QPointF(gameOverPix->boundingRect().width()/2,
                                                gameOverPix->boundingRect().height()/2));

    scoreTextItem = new QGraphicsTextItem();
    addItem(scoreTextItem);
    scoreTextItem->setPos(QPointF(0,0) - QPointF(scoreTextItem->boundingRect().width()/2,
                                                 -gameOverPix->boundingRect().height()/2));

}
void Scene::hideGameOvergraphics()
{if(gameOverPix){
        removeItem(gameOverPix);
        delete gameOverPix;
        gameOverPix = nullptr;
    }
    if(scoreTextItem){
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }

}

void Scene::cleanPillars()
{
    QList<QGraphicsItem *>sceneItems = items();
    foreach(QGraphicsItem * items,sceneItems){

        PillarItem * pillar = dynamic_cast<PillarItem*>(items);
        if(pillar){
            removeItem(pillar);
            delete pillar;
        }
    }
    // QGraphicsScene::mousePressEvent(event);

}
