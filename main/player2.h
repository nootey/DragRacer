#ifndef PLAYER1_H
#define PLAYER1_H

#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsItem>
#include <QObject>
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QElapsedTimer>

class Player2: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Player2(QGraphicsItem * parent = 0);
    QTimer * move_timer;
    QElapsedTimer boostTimer; //timer za bost ai

    //spremenljivke
    float a2;
    float speed2;
    int distance2;
    float nitro2;
    bool shownitro;
    int randBoost;
    float velocity2;
    float tractionForce2;
    bool slowDown2;
    int boostTimerStop;


    //funkcije
    void calcSpeed();
    void boost2();
    void stopBoost2();
public slots:
   void move();
};


#endif // PLAYER1_H
