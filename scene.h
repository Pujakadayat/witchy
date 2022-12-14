#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>
#include <QTimer>
#include "pillaritem.h"
#include "birditem.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void addBird();
    void startGame();
    bool getGameOn() const;
    void setGameOn(bool newGameOn);
    void incrementScore();

signals:

public slots:
      // QGraphicsScene interface
protected:
     void keyPressEvent(QKeyEvent *event);
     void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
     void showGameOverGraphics();
     void hideGameOvergraphics();
     void cleanPillars();
    void setUpPillarTimer();
    void freezeBirdAndPillarsInPlace();
     QTimer * pillarTimer;
     BirdItem * bird;
     bool gameOn;
     int score;
     int bestscore;
     QGraphicsPixmapItem * gameOverPix;
     QGraphicsTextItem * scoreTextItem;



};

#endif // SCENE_H
