#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QObject>
#include <QTimer>

class Count: public QGraphicsTextItem{
    Q_OBJECT
public:
    Count(QGraphicsItem *parent=0);
    QTimer * move_timer;
    int x;
    QGraphicsPixmapItem * cntdwn;

public slots:
    void move();
};


#endif // COUNTDOWN_H
