#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>


class PillarItem : public QObject , public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX )
public:
    explicit PillarItem();
   ~PillarItem();
    //PillarItem(QGraphicsPixmapItem *topPillar, QGraphicsPixmapItem *bottomPillar);
    qreal x() const;
void freezeInPlace();

signals:
    void collidefail();
public slots:
    void  setX(qreal x);

private:
    bool collidesWithBird();
    QGraphicsPixmapItem * topPillar;
      QGraphicsPixmapItem * bottomPillar;
      QPropertyAnimation * xAnimation;
      int yPos;
      qreal m_x;
      bool pastBird;
};

#endif // PILLARITEM_H
