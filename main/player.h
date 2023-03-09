#ifndef PLAYER2_H
#define PLAYER2_H

#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsItem>
#include <QObject>

class Player: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:

    //items
    Player(QGraphicsItem * parent = 0);

    //spremenljivke
    float a;
    float speed;
    int distance;
    float nitro;
    float velocity;
    float tractionForce;
    bool slowDown;

    //funkcije
    void boost();
    void calcSpeed();
    void stopBoost();
public slots:
   void move();
};


#endif // PLAYER2_H
