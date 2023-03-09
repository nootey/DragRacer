#ifndef PLAYERLIST_H
#define PLAYERLIST_H
#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QScrollArea>

class Lboard: public QWidget{
public:
    Lboard(QWidget * parent=NULL);
    QScrollArea *scrollArea;
    QScrollBar *scrollBar;

};

#endif // PLAYERLIST_H
