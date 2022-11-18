#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
//#include "birditem.h"
Widget::Widget(QWidget *parent) :
     QWidget(parent),
     ui(new Ui::Widget)
{
    ui->setupUi(this);


    scene = new Scene(this);
    scene->setSceneRect(-250,-300,500,600);

    QGraphicsPixmapItem * pixItem = new QGraphicsPixmapItem(QPixmap(":/image/background5.png"));
    scene->addItem(pixItem);
    pixItem->setPos(QPointF(0,0) - QPointF(pixItem->boundingRect().width()/2,
                                           pixItem->boundingRect().height()/2));
    scene->addLine(-400,0,400,0,QPen(Qt::blue));
     scene->addLine(0,-400,0,400,QPen(Qt::blue));

  // BirdItem * bird = new BirdItem(QPixmap(":/image/w3.png"));
    // scene->addItem(bird);

     ui->startGameButtin->setScene(scene);
    scene->addBird();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
   db.setDatabaseName("/Users/pujakadayat/Desktop/flap.db");

    if(db.open()){
        QMessageBox::information (this, "Connection","Database connected successfully");
    }
    else{
        QMessageBox::information(this,"not connected", "Database not connected");
    }

}


void Widget::on_pushButton_2_clicked()
{

}

