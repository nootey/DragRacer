#include "button.h"
#include <QBrush>


Button::Button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){

    setRect(0,0,250,50);
    QPen pen(Qt::white, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setPen(pen);

    text = new QGraphicsTextItem(name,this);
    text->setDefaultTextColor(Qt::white);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    QFont f("Arial", 10, QFont::Bold);
    text->setFont(f);
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QColor color;
    color="#1f82f2";
    QPen pen(color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setPen(pen);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QPen pen(Qt::white, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setPen(pen);
}
