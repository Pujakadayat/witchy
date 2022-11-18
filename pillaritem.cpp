#include "pillaritem.h"
#include "birditem.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include "scene.h"
#include <QDebug>

PillarItem::PillarItem():
    topPillar(new QGraphicsPixmapItem(QPixmap(":/image/pillarup.png"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/image/pillardown.png"))),
    pastBird(false)
{

    topPillar-> setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2,
                                              topPillar -> boundingRect().height()+ 80));
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2,
                                                80));

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos =  QRandomGenerator::global()->bounded(150);
    int XRandomizer  = QRandomGenerator::global()-> bounded(180);

    setPos(QPoint(0,0) + QPoint(260 + XRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this,"x",this);
    xAnimation-> setStartValue(260 + XRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);

    connect (xAnimation, &QPropertyAnimation::finished,[=](){
        qDebug()<< "Animation finished";
        scene() -> removeItem(this);
        delete this;
    });
    xAnimation->start();


}
PillarItem::~PillarItem(){
    qDebug() << "Deleting pillar";
    delete topPillar;
    delete bottomPillar;
}
qreal PillarItem::x() const
{
    return m_x;

}

void PillarItem::freezeInPlace()
{
    xAnimation->stop();

}
void PillarItem::setX(qreal x)
{
    qDebug()<<"Pillar position: "<<x;
    m_x = x;
    if(x<0 && !pastBird){
        pastBird = true;
        QGraphicsScene * mScene= scene();
        Scene * myScene = dynamic_cast<Scene *>(mScene);
        if(myScene){
            myScene->incrementScore();
        }


    }


    if(collidesWithBird()){
        emit collidefail();
    }
    setPos(QPointF(0,0) + QPointF(x,yPos));
}

bool PillarItem::collidesWithBird()
{
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());
    foreach (QGraphicsItem * Item,collidingItems){
        BirdItem * birdItem = dynamic_cast<BirdItem *>(Item);
        if(birdItem){
            return true;
        }
    }
    return false;
}
//PillarItem::PillarItem(QGraphicsPixmapItem *topPillar, QGraphicsPixmapItem *bottomPillar) : topPillar(topPillar),
// bottomPillar(bottomPillar)
