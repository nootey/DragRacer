#include "leaderboard.h"
#include <QDialog>
#include <QScrollArea>


Lboard::Lboard(QWidget *parent){
    //setFixedSize(400,900);
    setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    scrollArea = new QScrollArea;
    //scrollBar= new QScrollBar;
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(500,300);
    scrollArea->setWidget(this);
    scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    //scrollArea->setVerticalScrollBar(scrollBar);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
