#include "player.h"
#include <QTimer>
#include "game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

extern Game* game;

Player::Player(QGraphicsItem *parent){
    speed=0;
    a=0;
    distance=0;
    nitro=0;
    velocity=0;
    tractionForce=0.06;
    slowDown=0;

}

void Player::calcSpeed(){

    if(game->gears==game->gearMax)game->maxspeed=game->topspeed1;
    if(speed<game->maxspeed){

        velocity=(game->maxspeed-speed);


             a=velocity/game->driveTime;
             if(game->driveTime<8){
                 a=a*tractionForce+(game->startBoost/2);
             }
             if(a>0)speed+=a + nitro;
         }
    else speed=game->maxspeed;
}

void Player::stopBoost(){

    if(game->nitros->isVisible()==false){
       if(nitro>=0)nitro-=0.02;
        if(nitro<0)nitro=0;
    }
}

void Player::boost(){

    if(nitro<0.15){
        nitro+=0.03;
        game->nitros->setPos(game->avto->pos().x()-50,game->avto->pos().y()+15);
        game->nitros->show();
    }
    else game->nitros->hide();

}

void Player::move(){

    if(game->startGame==1){

        //racunanje hitrosti
        calcSpeed();

        //racunanje distance
        distance+=(speed/3.6)/game->driveTime;

        //premik na mapi
        if(game->trackLength==400 && game->progm->x()<game->prog->x()+900)game->progm->setPos(game->progm->x()+speed/22,game->progm->y());
        else if(game->progm->x()<game->prog->x()+900 && game->trackLength==800) game->progm->setPos(game->progm->x()+speed/44,game->progm->y());

        //zmanjsevanje nitrota
        stopBoost();

        if(speed>game->cai->speed2)game->drawSpeed=speed;
         else game->drawSpeed=game->cai->speed2;

        //izpis hitrosti
        game->sped->setPlainText("Speed: "+QString::number(speed)+"km/h");

        //cekira zmagovalca
        game->zmaga(game->trackLength);

        //izpis distance
        game->distant->setPlainText("Distance: "+QString::number(distance)+"m");
}
}
