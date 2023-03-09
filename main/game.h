#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsScene>
#include "qdebug"
#include <QTimer>
#include <QGraphicsRectItem>
#include <QObject>
#include "countdown.h"
#include "QLabel"
#include "button.h"
#include <QElapsedTimer>
#include <QGraphicsItem>
#include "player.h"
#include "player2.h"
#include <QInputDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableView>
#include <QHBoxLayout>
#include <QGraphicsProxyWidget>
#include "leaderboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QFontDatabase>
#include <QLineEdit>


class Game: public QGraphicsView{
    Q_OBJECT
public:

    /*////////////////////____RANDOM MAGIC ;)____////////////////////*/

    Game(); //konstruktor
    QGraphicsScene * scene; //zacetna scena
    QMap<int, bool> keys; //shranjevanje tipk
    QSqlDatabase mydb; //podatkovna baza
    QVector<QVector<QString> > list2d;
    QVector<QString> list;

    /*////////////////////____FUNKCIJE____////////////////////*/

    int zmaga(int proga); //najavi zmagovalca
    void keyPressEvent(QKeyEvent * e); //pregleduje pritiske tipk
    void keyReleaseEvent(QKeyEvent *e); //pregleduje spust tipk
    void removeAllItems(); //odstrani vse elemente iz scene
    void insert(QString name, QString time, QString car, QString distance); //vstavi podatke v podatkovno bazo
    bool connOpen(QSqlDatabase mydb);  //odpre povezavo z podatkovno bazo
    void connClose(QSqlDatabase mydb); //zapre povezavo z podatkovno bazo
    void fillList(); //napolni list avtov
    void AiShiftu(); //shifting za ai
    void AiShiftMasteru(); //shifting za ai v shiftmasters


    /*////////////////////____SPREMENLJIVKE____////////////////////*/

    bool winnerP1; //deklaracija zmagovalca player1
    bool winnerP2; //deklaracija zmagovalca ai ali player 2
    bool startGame; //zacetek igre po izbranem zacetnem pospesku
    int meterPos; //pozicija metra za player1
    int meterPos2; //pozicija metra za player2
    int hideItems; //skrivanje elementov na sceni
    float maxspeed; //max hitrost za player1 glede na prestave
    float maxspeed2; //max hitrost za player2 glede na prestave


    int driveTime; //prevozni cas player1
    int driveTime2; //prevozni cas player2
    float P1EndTime; //koncni cas player1
    float P2EndTime; //koncni cas player2 ali ai
    bool player2; //spremenljivka za dolocitev 1 ali 2 igralcev
    bool startRace; //signal za zacetek
    int trackLength; // dolzina proge
    float drawSpeed; //hitrost za risanje ceste
    bool start1; //pogon player1
    bool start2; //pogon player2
    bool dust; //spremanljivka za izbiro mape
    bool koncenvnos; // spremanljivka za vnos v bazo
    int timerId; //id timerja game classa
    bool konc; //dodatna spremenljivka za cekiranje zmagovalca
    bool canShift; //shift ja/ne player1
    bool canShift2; //shift ja/ne player2 / ai

    QString cname; //ime avta player1
    QString cname2; //ime avta player2
    QString carname1; //polno ime avta
    QString carname2; //polno ime avta
    int topspeed1; //najvecja hitrost za player1
    int topspeed2; //najvecja hitrost za player2
    QString accu1; //0-100km/h
    QString accu2; //0-100km/h
    int gearMax; // merilec prestav za player1
    int gearMax2; //menerilec prestav za player2
    float startBoost; //dodana vrednost zacetnega pospeska glede na avto player1
    float startBoost2; //dodana vrednost zacetnega pospeska glede na avto player2

    int gears; //prestave player1
    int gears2; //prestave player2
    bool izberi; //izbira player1 ali 2 za avte
    int limit1; //dodatna limita prestav player1
    int limit2; //dodatna limita prestav player2
    bool gearp1; //dodatna limita prestav player1
    bool gearp2; //dodatna limita prestav player2
    bool p1drive; //avto vozi / ne player1
    bool p2drive; //avto vozi / ne player2
    int rando; //izbira naklucnih avtomobilov ai
    QString tajmu; //koncni cas za vnos v bazo player 1
    QString tajmu2; //koncni cas za vnos v bazo player 1
    bool leaders; //izbira full / top5 leaderboards
    bool gamemode; //izbira gamemode na prikazu leaderboard
    int crando; //izbira naklucne mape
    bool brisi; //ustavi timerje ja / ne
    int AiShift; //pozicija ai shiftanja (70%-90%)
    QString distancu; //koncni vnost dolzine proge

    int gearStop; //zmanjsevanje prestav ob ustavitvi avta player1
    int gearStop2; //zmanjsevanje prestav ob ustavitvi avta player2
    int gearDropLimit; //zmanjsevanje prestav glede na cas player1
    int gearDropLimit2; //zmanjsevanje prestav glede na cas player1
    int timeStop; //ce se avto ustavi se zmanjsuje ongoing cas player1
    int timeStop2; //ce se avto ustavi se zmanjsuje ongoing cas player2
    int speedCheck; //cekira ce se avto ustavlja ali ne pospesuje vec player1
    int speedCheck2; //cekira ce se avto ustavlja ali ne pospesuje vec player2
    bool startej; //da se zacetni bar zacne premikati
    int gearTimeLimit; //limitiranje casa glede na prestave player1
    int gearTimeLimit2; //limitiranje casa glede na prestave player1
    int listPos; //pozicija lista za izbiro avta
    bool shiftmajstor; //shiftmasters ja ali ne
    QString lboardGameMode; //izbira shiftmasters oz drag race


    /*////////////////////____TIMERJI____////////////////////*/

    QTimer * timeIncrease; //timer za cas player1
    QTimer * timeIncrease2; //timer za cas player2
    QTimer * timer; //timer ki zmanjsuje hitrost player1
    QTimer * timer2; //timer ki zmanjsuje hitrost player2
    QTimer * shifter; //timer za gearbox player1
    QTimer * shifter2; //timer za gearbox player2
    QTimer * mtimer; //timer za meter za player1
    QTimer * mtimer2; //timer za meter za player2
    QTimer * move_timer; //timer za premikanje ceste
    QElapsedTimer DropGearTimer1; //timer za zmanjsevanje prestav player1
    QElapsedTimer DropGearTimer2; //timer za zmanjsevanje prestav player2
    QElapsedTimer DropTimeTimer1; //timer za zmanjsevanje hitrosti/outgoing casa player1
    QElapsedTimer DropTimeTimer2; //timer za zmanjsevanje hitrosti/outgoing casa player2
    QElapsedTimer * pt1; //koncni cas player1
    QElapsedTimer * pt2; //koncni cas player2/cpu


    /*////////////////////____MODELI____////////////////////*/

    Player * avto; //avto za player1
    Player2 * cai; //avto za player2
    QGraphicsPixmapItem * nitros; // nitros player1
    QGraphicsPixmapItem * nitros2; // nitros player2
    QGraphicsPixmapItem * bar; //side bar za zacetni pospesek player1
    QGraphicsPixmapItem * bar2; //side bar za zacetni pospesek player2
    QGraphicsPixmapItem * meter; //meter za side bar player1
    QGraphicsPixmapItem * meter2; //meter za side bar player2
    QGraphicsPixmapItem * gear; //gearbox player1
    QGraphicsPixmapItem * gear2; //gearbox player2
    QGraphicsPixmapItem * steer; //armatura
    QGraphicsPixmapItem * prog; //top minibar
    QGraphicsPixmapItem * progm; //enota player1 na minibar
    QGraphicsPixmapItem * progm2; //enota player2 na minibar
    QGraphicsPixmapItem * kp1; //legenda tipk player1
    QGraphicsPixmapItem * kp2; //legenda tipk player2

    /*////////////////////____TEXTI____////////////////////*/

    QString name1; //ime za player1
    QString name2; //ime za player2
    QGraphicsTextItem * sped; //merilec hitrosti player1
    QGraphicsTextItem * sped2; //merilec hitrosti player2
    QGraphicsTextItem * gearcount; //merilec prestav player1
    QGraphicsTextItem * gearcount2; //merilec prestav player2
    QGraphicsTextItem * endtime; //koncni cas
    QGraphicsTextItem * distant; //distance player1
    QGraphicsTextItem * distant2; //distance player2
    QLabel * value1; //vnos v podatkovno bazo
    QLabel * value2; //vnos v podatkovno bazo
    QLabel * value3; //vnos v podatkovno bazo
    QLabel * value4; //vnos v podatkovno bazo

public slots:
    void slowDown(); //funkcija zmanjsuje hitrost ce ne pritiskamo pospesi player1
    void slowDown2(); //funkcija zmanjsuje hitrost ce ne pritiskamo pospesi player2
    void move(); //fukcija za meter player1
    void move2(); //fukcija za meter player2
    void shift(); //fukcija za gearbox player1
    void shift2(); //fukcija za gearbox player1
    void increaseTime(); //funkcija za cas player1
    void increaseTime2(); //funkcija za cas player2
    void drawRoad(); //rise cesto
    void start(); //zacetek igre
    void konec(); //konec igre
    void versus(); //fukcija za dolocitev 2 igralcev
    void replay(); //funkcija za replay
    void timerEvent(QTimerEvent *event); //cekira tipke
    void leaderboard(); //funkcija za leaderboards
    void displayMainMenu(); //main meni
    void dolzina(); //izbira dolzine poti
    void dg1(); //400m
    void dg2(); //800m
    void vehicleSelection(); //izbira vozila
    void P1select(); //izbira 1 player1
    void P2select(); //izbira 1 player1
    void endScreen(); //koncni izpis rezultatov in leaderboards
    void rightu(); //izbira avta -> desno
    void leftu(); //izbira avta -> levo
    void pickGameMode(); //izira nacina igre
    void shiftMasters(); //shiftmasters...
};

#endif // GAME_H
