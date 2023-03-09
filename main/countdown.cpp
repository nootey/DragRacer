#include "countdown.h"
#include "game.h"

extern Game *game;


Count::Count(QGraphicsItem *parent){
    move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(1000);

    x=3;
    cntdwn = new QGraphicsPixmapItem();
    cntdwn->setPixmap(QPixmap(":/images/"+QString::number(x)+".png"));
    cntdwn->setPos(440,60);
    cntdwn->setZValue(5);
    game->scene->addItem(cntdwn);
    cntdwn->hide();

}

void Count::move(){

    if(game->hideItems==0 && game->startej==1){
          this->setPlainText(QString::number(x));
        if(x<1){
            if (game->meterPos>=150 && game->meterPos<=300){ //preveri ce je player1 zadel zeleno mesto na baru
                game->avto->a=0.4;
            }

            if(game->player2==0){
                game->cai->a2=0.4;
            }

            if (game->meterPos2>=860 && game->meterPos2<=910) //preveri ce je player2 zadel zeleno mesto na baru
                game->cai->a2=0.4;

            game->hideItems=1;  //skrije vse elemente
            game->startRace=1; //signal naj zacne
            x=3;
            move_timer->stop();
            cntdwn->hide();
            game->startej=0;
        }
        else {
            cntdwn->show();
            cntdwn->setPixmap(QPixmap(":/images/"+QString::number(x)+".png"));
            x--;

        }
    }
    else{
        this->hide();
        cntdwn->hide();
    }



}
