#include "player2.h"
#include <QTimer>
#include "game.h"

extern Game* game;

Player2::Player2(QGraphicsItem *parent){

    move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(60);
    speed2=0;
    a2=0;
    distance2=0;
    nitro2=0;
    shownitro=0;
    randBoost=0;
    velocity2=0;
    boostTimerStop=0;
    tractionForce2=0.06;
    boostTimer.start();
}

void Player2::calcSpeed(){

    if(game->gears2==game->gearMax2)game->maxspeed2=game->topspeed2;
    if(speed2<game->maxspeed2){
        velocity2=(game->maxspeed2-speed2);

             a2=velocity2/game->driveTime2;
             if(game->driveTime2<8){
                 if(game->player2==1)a2=a2*tractionForce2+(game->startBoost2/2);
                 else a2=(a2*tractionForce2)*0.99;

             }
             if(a2>0)speed2+=a2 + nitro2;

         }
         else speed2=game->maxspeed2;
}

void Player2::boost2()
{
    if(nitro2<0.15){
        nitro2+=0.03;
        game->nitros2->setPos(game->cai->pos().x()-50,game->cai->pos().y()+15);
        game->nitros2->show();
        shownitro=1;
    }
    else game->nitros2->hide();
    shownitro=0;

}

void Player2::stopBoost2()
{
    //zmanjsevanje nitrota
    if(shownitro==0){
        if(nitro2>=0)
            nitro2-=0.02;
              if(nitro2<0)nitro2=0;
    }
}

void Player2::move()
{
    if(game->player2==1)move_timer->stop();

    if(game->startGame==1 && game->start2==1){

        //racunanje hitrosti
        calcSpeed();
        //izpis razdalje
        distance2+=(speed2/3.6/game->driveTime2);

        if(distance2>80 && game->player2==0){

        srand (time(NULL));
        randBoost = rand() % 4 + 1;

        if(randBoost==2){

            boostTimerStop=boostTimer.elapsed();
            boost2();
            if(boostTimer.elapsed()/1000-boostTimerStop/1000>3)randBoost = rand() % 4 + 1;
        }
        else stopBoost2();
            }

        //izpis na mapi
        if(game->trackLength==400 && game->progm2->x()<game->prog->x()+900)game->progm2->setPos(game->progm2->x()+speed2/22,game->progm2->y());
        else if(game->trackLength==800 && game->progm2->x()<game->prog->x()+900) game->progm2->setPos(game->progm2->x()+speed2/44,game->progm2->y());


      if(speed2>game->avto->speed)game->drawSpeed=speed2;
      else game->drawSpeed=game->avto->speed;

     //izpis hitrosti
     game->sped2->setPlainText("Speed: "+QString::number(speed2)+"km/h");

     //cekira zmagovalca
     game->zmaga(game->trackLength);

     //izpis distance
     game->distant2->setPlainText("Distance: "+QString::number(distance2)+"m");

   }
}

