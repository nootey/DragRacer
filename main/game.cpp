#include "game.h"

Game::Game(){

    //scene
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,1200,800);
    setScene(scene);
    setFixedSize(1200,800);
    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setBackgroundBrush(QBrush(QImage(":/images/mainmenu.png")));
    player2=0;
    DropGearTimer1.start();
    DropGearTimer2.start();
    DropTimeTimer1.start();
    DropTimeTimer2.start();
    fillList();

}

void Game::keyPressEvent(QKeyEvent * e){ //skrbi za pritiske tipk

 keys[e->key()] = true; QWidget::keyPressEvent(e);

}

void Game::keyReleaseEvent(QKeyEvent *e){ // skrbi za spust tipk

    keys[e->key()] = false; QWidget::keyReleaseEvent(e);

     if(e->key()==Qt::Key_Shift){

        nitros->hide();
    }

    if(e->key()==Qt::Key_W){
                  //ponastavi timer, ki zmanjsuje hitrost avta player2
                  timer->setInterval(70);
                  gearStop=DropGearTimer1.elapsed();
                  timeStop=DropTimeTimer1.elapsed();

    }

    if(e->key()==Qt::Key_Up){
                  //ponastavi timer, ki zmanjsuje hitrost avta
                  timer2->setInterval(70);
                  gearStop2=DropGearTimer2.elapsed();
                  timeStop2=DropTimeTimer2.elapsed();
    }

    if(e->key()==Qt::Key_Control){
        if(player2==1){
        nitros2->hide();}
    }
}

void Game::slowDown(){ //zmanjsuje hitrost player1

    if(avto->speed>1)avto->speed-=3;
    if(avto->speed<0) avto->speed=0;

    if(DropGearTimer1.elapsed()/1000-gearStop/1000>gearDropLimit){

        if(gears>1){

            gears--;
            maxspeed-=30;
            gearDropLimit+=1;
            gearcount->setPlainText("Gear: "+QString::number(gears));
            limit1--;
        }

    }

        sped->setPlainText("Speed: "+QString::number(avto->speed)+"km/h");
        if(meter->pos().y()<765 && hideItems==1) meter->setPos(meter->x(),meter->y()+4);
    }

void Game::slowDown2(){ //zmanjsuje hitrost player2

    if(cai->speed2>1) cai->speed2-=3;
    if(cai->speed2<0) cai->speed2=0;

     if(DropGearTimer2.elapsed()/1000-gearStop2/1000>gearDropLimit2 && player2==1){

        if(gears2>1){

            gears2--;
            maxspeed2-=30;
            gearDropLimit2+=1;
            gearcount2->setPlainText("Gear: "+QString::number(gears2));
            limit2--;
        }

    }

      sped2->setPlainText("Speed: "+QString::number(cai->speed2)+"km/h");
      if(player2==1 && meter2->pos().y()<760 && hideItems==1) meter2->setPos(meter2->x(),meter2->y()+4);

}

void Game::move(){ //premika meter player1 navzdol

    if(hideItems==0 && startej==1){
        meter->show();
        if(meter->pos().x()>(bar->x()+3))
        meter->setPos(meter->x()-1,meter->y());
        meterPos=meter->pos().x();
    }
    else{

        mtimer->stop();
        shifter->start(60);
        meter->setRotation(90);
        meter->setScale(0.4);
        meter->setPos(65,765);
        bar->hide();

        if(player2==0){
            kp1->hide();
            shifter2->start(60);
            meter2->setRotation(90);
            meter2->setScale(0.4);
            meter2->setPos(1140,765);
        }

    }
}

void Game::move2(){ //premika meter player2 navzdol

    if(hideItems==0 && player2==1 && startej==1){
        meter2->show();
        if(meter2->pos().x()>(bar2->x()+3))
        meter2->setPos(meter2->x()-1,meter2->y());
        meterPos2=meter2->pos().y();
    }

    else{
        mtimer2->stop();
        shifter2->start(60);
        meter2->setRotation(90);
        meter2->setScale(0.4);
        meter2->setPos(1140,760);
        bar2->hide();
        kp2->hide();
    }
}

void Game::shift(){ //menjalnik za player1

    if(hideItems==1 && startGame==1 && p1drive==1){

        if(meter->pos().y()>700)gearp1=1;
        if(meter->pos().y()>630) meter->setPos(meter->x(),meter->y()-2);
        if(canShift==1 && gears<=gearMax && gears<=limit1 && gearp1==1){
            canShift=0;
            gearp1=0;
            gears++;
            maxspeed+=30;
            gearcount->setPlainText("Gear: "+QString::number(gears));
            if(maxspeed>=topspeed1)maxspeed=topspeed1;
            else maxspeed=maxspeed;
            meter->setPos(meter->x(),760);
        }


       }
        else if(meter->pos().y()<760) meter->setPos(meter->x(),meter->y()+1);
}

void Game::shift2(){ //menjalnik za player2

    if(hideItems==1 && startGame==1 && p2drive==1){

        if(meter2->pos().y()>700)gearp2=1;
        if(meter2->pos().y()>630) meter2->setPos(meter2->x(),meter2->y()-2);

        if(canShift2==1 && gears2<=gearMax2 && gears2<=limit2 && gearp2==1){
            canShift2=0;
            gears2++;
            maxspeed2+=30;
            gearcount2->setPlainText("Gear: "+QString::number(gears2));
            if(maxspeed2>=topspeed2)maxspeed2=topspeed2;
            else maxspeed2=maxspeed2;
            meter2->setPos(meter2->x(),760);
            gearp2=0;
        }

        }
        else if(meter2->pos().y()<760) meter2->setPos(meter2->x(),meter2->y()+1);

    if(player2==0){
        if(shiftmajstor==1)AiShiftMasteru();
        else AiShiftu();
        }

}

void Game::AiShiftu(){ //shifting za ai, interval 70-95% gearboxa

    if(meter2->pos().y()<=AiShift && gears2<=gearMax2 && gearp2==1){
        srand (time(NULL));
        AiShift = rand() % 42 + 630;
        canShift2=0;
        gears2++;
        maxspeed2+=30;
        cai->speed2-=4; //ko shifta zgubi malce hitrosti zaradi switcha
        gearcount2->setPlainText("Gear: "+QString::number(gears2));
        if(maxspeed2>=topspeed2)maxspeed2=topspeed2;
        else maxspeed2=maxspeed2;
        meter2->setPos(meter2->x(),760);
        gearp2=0;
    }

}

void Game::AiShiftMasteru(){ //shifting za ai, interval 85-90% gearboxa

    if(meter2->pos().y()<=AiShift && gears2<=gearMax2 && gearp2==1){
        srand (time(NULL));
        AiShift = rand() % 32 + 635;
        canShift2=0;
        gears2++;
        maxspeed2+=30;
        cai->speed2-=4; //ko shifta zgubi malce hitrosti zaradi switcha
        gearcount2->setPlainText("Gear: "+QString::number(gears2));
        if(maxspeed2>=topspeed2)maxspeed2=topspeed2;
        else maxspeed2=maxspeed2;
        meter2->setPos(meter2->x(),760);
        gearp2=0;
    }

}

void Game::increaseTime(){ //zvisuje cas

    if(startRace==1){

        if(avto->speed<5)driveTime=1;
            if(gears>1)gearTimeLimit=gears-1;
            if((topspeed1/3.6)/driveTime>1)driveTime++;
            if((avto->speed/3.6)/driveTime<gearTimeLimit){
                if(gears<5)driveTime-=(gears-1);
                else driveTime-=(gears-2);
            }
    }
}

void Game::increaseTime2(){ //zvisuje cas

    if(startRace==1){

        if(cai->speed2<5)driveTime2=1;
            if(gears2>1)gearTimeLimit2=gears2-1;
            if((topspeed2/3.6)/driveTime2>1)driveTime2++;
            if((cai->speed2/3.6)/driveTime2<gearTimeLimit2){
                if(gears2<5)driveTime2-=(gears2-1);
                else driveTime2-=(gears2-2);
           }
    }
}

int Game::zmaga(int proga){ //doloci zmagovalca

    if(shiftmajstor==1){
    if(gears==gearMax){
        winnerP1=1;
        konec();
    }
    if(gears2==gearMax2){
        winnerP2=1;
        konec();
    }
    }
    else {
    if(avto->distance>=proga){

        if(koncenvnos==0)P1EndTime = (pt1->elapsed()/1000);
        winnerP1=1;
        konec();
    }

    if(cai->distance2>=proga){

        if(koncenvnos==0)P2EndTime = (pt2->elapsed()/1000);
        winnerP2=1;
        konec();
    }
    }
}

void Game::versus(){ //zacne igro z dvema igralcema
     player2=1;
     vehicleSelection();
}

void Game::replay(){ //omogoci ponovno igro

    removeAllItems();
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/images/mainmenu.png")));
    player2=0;
    QGraphicsRectItem *yolo = new QGraphicsRectItem();
    yolo->setRect(0,0,1200,800);
    yolo->setBrush(QBrush(Qt::black));
    yolo->setZValue(10);
    scene->addItem(yolo);

    Button* solo = new Button(QString("SOLO"));
    int txPos = this->width()/2 - solo->boundingRect().width()/2;
    solo->setPos(txPos,300);
    connect(solo,SIGNAL(clicked()),this,SLOT(pickGameMode()));
    scene->addItem(solo);
    solo->setZValue(11);

    Button* versus = new Button(QString("VERSUS"));
    txPos = this->width()/2 - versus->boundingRect().width()/2;
    versus->setPos(txPos,360);
    connect(versus,SIGNAL(clicked()),this,SLOT(versus()));
    scene->addItem(versus);
    versus->setZValue(11);
}

void Game::timerEvent(QTimerEvent *event){ //funkcija ki cekira pritisk tipk

    if(winnerP1==0 && winnerP2==0){

    if(keys[Qt::Key_W]){
        if(startRace==1){
           startGame=1; // pricne igro
           p1drive=1;
           if(timeIncrease->isActive()==false)timeIncrease->start(500);
           avto->move();
           if(player2==0){
               p2drive=1;
               start2=1;
           }

           timer->setInterval(1000);//zazene timer
         }
           if(hideItems==0 && meter->pos().x()<370 && startGame==0){
           meter->setPos(meter->x()+25,meter->y());
           meterPos=meter->pos().x();
           }
    }

    if(keys[Qt::Key_Up]){

         if(startRace==1 && player2==1){
            startGame=1; // pricne igro
            start2=1;
            p2drive=1;
            cai->move();
            timer2->setInterval(1000);//zazene timer
         }

         if(hideItems==0 && meter2->pos().x()<1080 && startGame==0 && player2==1){

         meter2->setPos(meter2->x()+25,meter2->y());
         meterPos2=meter2->pos().x();}
         }

         if(keys[Qt::Key_H]){
            if(meter->pos().y()<=663 && meter->pos().y()>=630 && keys[Qt::Key_W]==false){ //cekria ce je menjalnik med 80 in 90% in gas

                canShift=1;
                limit1++;
                }
            }

            if(keys[Qt::Key_Shift]){
                avto->boost();
            }

            if(keys[Qt::Key_P]){
                if(player2==1){

                if(meter2->pos().y()<=663 && meter2->pos().y()>=630 && keys[Qt::Key_Up]==false){
                   canShift2=1;
                   limit2++;
                 }

                }

              }

            if(keys[Qt::Key_Control]){

                    if(player2==1){
                    cai->boost2();
                      }
               }

      }
}

void Game::leaderboard(){ //izrise leaderboards

    removeAllItems();
    QString querry;

    QString choose="FULL";
    lboardGameMode="PLAYERS";
    scene->setSceneRect(0,0,1200,800);
    setScene(scene);
    if(gamemode==0) {
       lboardGameMode="PLAYERS";
       gamemode=1;
    }
    else if(gamemode==1){
            lboardGameMode="SHIFTMASTERS";
            gamemode=0;
    }


     querry="SELECT * FROM "+lboardGameMode+" WHERE time!='Not Finnished' ORDER BY cast(time as int) asc";

    Button* mode = new Button(QString(lboardGameMode));
    int txPos = this->width()/2 - mode->boundingRect().width()/2;
    mode->setPos(txPos,550);
    mode->setZValue(11);
    connect(mode,SIGNAL(clicked()),this,SLOT(leaderboard()));
    scene->addItem(mode);

    connOpen(mydb);

     Lboard * lboard= new Lboard();
     QFontDatabase::addApplicationFont(":/fonts/FredokaOne-Regular.ttf");
     QFont f("Fredoka One", 12, QFont::Normal);
     QSqlQuery query;
     query.exec(querry);

     QGridLayout * layout=new QGridLayout;
     int counter=0;

     while(query.next()){

       value1 = new QLabel;
       value2 = new QLabel;
       value3 = new QLabel;
       value4 = new QLabel;

       value1->setFont(f);
       value2->setFont(f);
       value3->setFont(f);
       value4->setFont(f);

       value1->setStyleSheet("color: white");
       value2->setStyleSheet("color: white");
       value3->setStyleSheet("color: white");
       value4->setStyleSheet("color: white");

       value1->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
       value2->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
       value3->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
       value4->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);

       value1->setText(query.value(0).toString());
       value2->setText(query.value(1).toString());
       value3->setText(query.value(2).toString());
       value4->setText(query.value(3).toString());

       layout->addWidget(value1,counter,0,Qt::AlignHCenter);
       layout->addWidget(value2,counter,1,Qt::AlignHCenter);
       layout->addWidget(value3,counter,2,Qt::AlignHCenter);
       layout->addWidget(value4,counter,3,Qt::AlignHCenter);
       counter++;
        }

     lboard->setStyleSheet("background-color: black");
     lboard->setLayout(layout);
     scene->addWidget(lboard->scrollArea)->setPos(358,240);

     connClose(mydb);

     Button* back = new Button(QString("BACK"));
     back->setPos(txPos,610);
     connect(back,SIGNAL(clicked()),this,SLOT(displayMainMenu()));
     back->setZValue(12);
     scene->addItem(back);

     connClose(mydb);
}

void Game::drawRoad(){  //rise cesto, premika elemente


    if(player2==0) drawSpeed=avto->speed;

    if((avto->x()<gear->x() && cai->x()<gear->x()) && ((keys[Qt::Key_W]==false && keys[Qt::Key_Up] == false)
            ||(keys[Qt::Key_W]==false && cai->x()<gear->x())
               || (keys[Qt::Key_Up]==false && avto->x()<gear->x())) ){

        drawSpeed=0;
        if(keys[Qt::Key_W] && avto->x()<gear->x()) avto->setPos(avto->x()+10,avto->y());
        if(keys[Qt::Key_Up] && avto->x()<gear->x())cai->setPos(cai->x()+10,cai->y());
    }

    avto->setPos(avto->x()+avto->speed,avto->y());
    cai->setPos(cai->x()+cai->speed2,cai->y());
    if(avto->x()>700 || (player2==1 && cai->x()>700)){
    QRectF rect = scene->sceneRect();
    rect.translate(drawSpeed, 0);
    scene->setSceneRect(rect);

    steer->setPos(steer->x()+drawSpeed,steer->y());
    prog->setPos(prog->x()+drawSpeed,prog->y());
    progm->setPos((progm->x()+drawSpeed),progm->y());
    progm2->setPos((progm2->x()+drawSpeed),progm2->y());
    gear->setPos(gear->x()+drawSpeed,gear->y());
    meter->setPos(meter->x()+drawSpeed,meter->y());
    sped->setPos(sped->x()+drawSpeed,sped->y());
    sped2->setPos(sped2->x()+drawSpeed,sped->y());
    distant->setPos(distant->x()+drawSpeed,distant->y());
    distant2->setPos(distant2->x()+drawSpeed,distant->y());
    nitros->setPos(nitros->x()+avto->speed,nitros->y());
    gearcount->setPos(gearcount->x()+drawSpeed,gearcount->y());
    gearcount2->setPos(gearcount2->x()+drawSpeed,gearcount2->y());
    gear2->setPos(gear2->x()+drawSpeed,gear2->y());
    meter2->setPos(meter2->x()+drawSpeed,meter2->y());
    nitros2->setPos(nitros2->x()+cai->speed2,nitros2->y());

    }

}

void Game::start(){ //zacne igro

    /*////////////////////____ZACETNI MAGIC ;)____////////////////////*/

    removeAllItems();
    scene->setSceneRect(0,0,1200,800);
    setScene(scene);  
    rando=1;
    srand (time(NULL));
    crando=1;
    srand (time(NULL));
    crando = rand() % 4 + 1;
    setBackgroundBrush(QBrush(QImage(":/images/cesta"+QString::number(crando)+".png")));
    if(trackLength==800){
        dust=1;
        setBackgroundBrush(QBrush(QImage(":/images/dusty"+QString::number(crando)+".png")));
    }
    else dust=0;

    if(DropGearTimer1.elapsed()>0)DropGearTimer1.restart();
    if(DropGearTimer2.elapsed()>0)DropGearTimer2.restart();
    if(DropTimeTimer1.elapsed()>0)DropTimeTimer1.restart();
    if(DropTimeTimer2.elapsed()>0)DropTimeTimer2.restart();

    setFocusPolicy(Qt::StrongFocus); //?

    /*////////////////////____SPREMENJLIVKE____////////////////////*/

    timerId = startTimer(60); //pozene timer za cekiranje tipk
    startej=0;
    winnerP1=0;
    winnerP2=0;
    koncenvnos=0;
    topspeed2=300; // default vrednost za ai
    startGame=0;
    meterPos =0;
    meterPos2=0;
    speedCheck=0;
    speedCheck2=0;
    gearDropLimit=2;
    gearDropLimit2=2;
    brisi=1;
    hideItems=0;
    maxspeed = 60.0;
    maxspeed2 = 60.0;
    limit1=1;
    limit2=1;
    gearp1=1;
    gearp2=1;
    listPos=0;
    izberi=0;
    driveTime=1;
    driveTime2=1;
    P1EndTime = 0.0;
    P2EndTime = 0.0;
    startRace=0;
    canShift=0;
    canShift2=0;
    drawSpeed=0;
    start1=0;
    start2=0;
    leaders=0;
    gamemode=0;
    gears=1;
    gears2=1;
    name1="Player1";
    name2="Player2";
    konc=0;
    p1drive=0;
    p2drive=0;
    AiShift=656;
    if(shiftmajstor==1)lboardGameMode="SHIFTMASTERS";
    else lboardGameMode="PLAYERS";
    if(player2==0)gearMax2=6;

    //ustvari text za countdown
    Count * cnt = new Count();
    scene->addItem(cnt);

    //ime za player1
    name1 = QInputDialog::getText(this,"Player1","Enter your name!");

    //ime za player2
    if(player2==1){
    name2 = QInputDialog::getText(this,"Player2","Enter your name!");
    }

    startej=1;

    /*////////////////////____TIMERJI____////////////////////*/

    //timer za znizevanje hitrost player1
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(slowDown()));
    timer->start(1000);

    //timer za znizevanje hitrost player2
    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(slowDown2()));
    timer2->start(1000);

    //timer za koncni cas player1
    pt1 = new QElapsedTimer();
    pt1->start();

    //timer za koncni cas player2
    pt2 = new QElapsedTimer();
    pt2->start();

    //timer za meter
    mtimer = new QTimer(this);
    connect(mtimer,SIGNAL(timeout()),this,SLOT(move()));
    mtimer->start(5);

    //timer za meter player2
    if(player2==1){
        mtimer2 = new QTimer(this);
        connect(mtimer2,SIGNAL(timeout()),this,SLOT(move2()));
        mtimer2->start(5);
    }

    //timer za gearbox player1
    shifter = new QTimer(this);
    connect(shifter,SIGNAL(timeout()),this,SLOT(shift()));

    //timer za gearbox player2
    shifter2 = new QTimer(this);
    connect(shifter2,SIGNAL(timeout()),this,SLOT(shift2()));

    //timer za cas player1
    timeIncrease = new QTimer(this);
    connect(timeIncrease,SIGNAL(timeout()),this,SLOT(increaseTime()));
    timeIncrease->start(500);

    //timer za cas player2
    timeIncrease2 = new QTimer(this);
    connect(timeIncrease2,SIGNAL(timeout()),this,SLOT(increaseTime2()));
    timeIncrease2->start(500);

    //timer za premikanje viewa
    move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(drawRoad()));
    move_timer->start(70);

    /*////////////////////____MODELI____////////////////////*/

    //avto player1
    avto = new Player();
    avto->setPixmap(QPixmap(":/images/"+cname+".png"));
    avto->setPos(100,350);
    scene->addItem(avto);

    //avto player2
    cai = new Player2();
    cai->setPos(100,435);
    scene->addItem(cai);

    //izbira avta za ai (city)
    rando = rand() % 3 + 1;
    cai->setPixmap(QPixmap(":/images/cai"+QString::number(rando)+".png"));
    if(player2==1)cai->setPixmap(QPixmap(":/images/"+cname2+".png"));

    //izbira avta za ai (desert)
    if(dust==1){
    rando = rand() % 3 + 4;
    cai->setPixmap(QPixmap(":/images/cai"+QString::number(rando)+".png"));
    if(player2==1)cai->setPixmap(QPixmap(":/images/"+cname2+".png"));
    }

    //starting bar za zacetni pospesek player1
    bar = new QGraphicsPixmapItem;
    bar->setPixmap(QPixmap(":/images/bar.png"));
    bar->setPos(90,550);
    bar->setZValue(2);
    scene->addItem(bar);

    //starting bar za zacetni pospesek player2
    if(player2==1){
    bar2 = new QGraphicsPixmapItem;
    bar2->setPixmap(QPixmap(":/images/bar.png"));
    bar2->setPos(800,550);
    bar2->setZValue(3);
    scene->addItem(bar2);
    }

    //meter player1
    meter = new QGraphicsPixmapItem;
    meter->setPixmap(QPixmap(":/images/meter.png"));
    meter->setPos(bar->x()+150,bar->y());
    meter->setZValue(3);
    scene->addItem(meter);

    //meter player2
    meter2 = new QGraphicsPixmapItem;
    meter2->setPixmap(QPixmap(":/images/meter.png"));

    if(player2==1)meter2->setPos(bar2->x()+150,bar2->y());
    else meter2->setPos(1140,765);

    meter2->setZValue(4);
    scene->addItem(meter2);

    if(player2==0){
        meter2->setScale(0.4);
        meter2->setPos(1140,765);
    }

    //zgornji minimap pozicije avtov
    prog = new QGraphicsPixmapItem;
    prog->setPixmap(QPixmap(":/images/pos.png"));
    prog->setPos(130,10);
    prog->setZValue(3);
    prog->setScale(0.8);
    scene->addItem(prog);

    //zacetna legenda tipkovnice player1
    if(player2==0){
    kp1 = new QGraphicsPixmapItem;
    kp1->setPixmap(QPixmap(":/images/keyboardp1.png"));
    scene->addItem(kp1);
    }

    //zacetna legenda tipkovnice player2
    if(player2==1){
    kp2 = new QGraphicsPixmapItem;
    kp2->setPixmap(QPixmap(":/images/keyboardp2.png"));
    scene->addItem(kp2);
    }

    //enota na minimapi player1
    progm = new QGraphicsPixmapItem;
    progm->setPixmap(QPixmap(":/images/progm1.png"));
    progm->setPos(130,15);
    progm->setZValue(4);
    scene->addItem(progm);

    //enota na minimapi player2
    progm2 = new QGraphicsPixmapItem;
    progm2->setPixmap(QPixmap(":/images/progm2.png"));
    progm2->setPos(130,30);
    progm2->setZValue(4);
    scene->addItem(progm2);

    //gearbox player1
    gear = new QGraphicsPixmapItem;
    gear->setPixmap(QPixmap(":/images/gear.png"));
    gear->setZValue(2);
    gear->setPos(50,630);
    scene->addItem(gear);

    //gearbox za player2
    gear2 = new QGraphicsPixmapItem;
    gear2->setPixmap(QPixmap(":/images/gear.png"));
    gear2->setPos(1130,630);
    gear2->setZValue(3);
    scene->addItem(gear2);

    //armatura
    steer = new QGraphicsPixmapItem;
    steer->setPixmap(QPixmap(":/images/dash.png"));
    steer->setPos(0,515);
    scene->addItem(steer);

    //nitro ogenj za player 1
    nitros = new QGraphicsPixmapItem;
    nitros->setPixmap(QPixmap(":/images/nitro.png"));
    nitros->hide();
    nitros->setPos(avto->x(),avto->y()+65);
    scene->addItem(nitros);

    //nitro ogenj za player2
    nitros2 = new QGraphicsPixmapItem;
    nitros2->setPixmap(QPixmap(":/images/nitro.png"));
    nitros2->hide();
    scene->addItem(nitros2);

    /*////////////////////____TEXTI____////////////////////*/

    //merilec hitrosti player1
    sped= new QGraphicsTextItem();
    sped->setPlainText("Speed: "+QString::number(avto->speed)+"km/h");
    sped->setDefaultTextColor(Qt::white);
    sped->setScale(2);
    sped->setPos(100,630);
    scene->addItem(sped);

    //merilec hitrosti player2
    sped2= new QGraphicsTextItem();
    sped2->setPlainText("Speed: "+QString::number(cai->speed2)+"km/h");
    sped2->setDefaultTextColor(Qt::white);
    sped2->setScale(2);
    sped2->setPos(900,630);
    sped2->setZValue(3);
    scene->addItem(sped2);

    //merilec prestav player1
    gearcount= new QGraphicsTextItem();
    gearcount->setPlainText("Gear: "+QString::number(gears));
    gearcount->setDefaultTextColor(Qt::white);
    gearcount->setScale(2);
    gearcount->setPos(100,730); 
    gearcount->setZValue(3);
    scene->addItem(gearcount);

    //merilec prestav player2
    gearcount2= new QGraphicsTextItem();
    gearcount2->setPlainText("Gear: "+QString::number(gears2));
    gearcount2->setDefaultTextColor(Qt::white);
    gearcount2->setScale(2);
    gearcount2->setPos(900,730);
    gearcount2->setZValue(3);
    scene->addItem(gearcount2);

    //prikaz dolzine player1
    distant= new QGraphicsTextItem();
    distant->setPlainText("Distance: "+QString::number(avto->distance)+"m");
    distant->setDefaultTextColor(Qt::white);
    distant->setScale(2);
    distant->setPos(100,680);
    scene->addItem(distant);

    //prikaz dolzine player1player2
    distant2= new QGraphicsTextItem();
    distant2->setPlainText("Distance: "+QString::number(cai->distance2)+"m");
    distant2->setDefaultTextColor(Qt::white);
    distant2->setScale(2);
    distant2->setPos(900,680);
    distant2->setZValue(3);
    scene->addItem(distant2);
}

void Game::displayMainMenu(){ //pokaze glavni meni

    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/images/mainmenu.png")));
    Button* solo = new Button(QString("SOLO"));
    int txPos = this->width()/2 - solo->boundingRect().width()/2;
    solo->setPos(txPos,300);
    connect(solo,SIGNAL(clicked()),this,SLOT(pickGameMode()));
    scene->addItem(solo);

    Button* versus = new Button(QString("VERSUS"));
    txPos = this->width()/2 - versus->boundingRect().width()/2;
    versus->setPos(txPos,360);
    connect(versus,SIGNAL(clicked()),this,SLOT(versus()));
    scene->addItem(versus);

    Button* lboards = new Button(QString("LEADERBOARDS"));
    txPos = this->width()/2 - lboards->boundingRect().width()/2;
    lboards->setPos(txPos,420);
    connect(lboards,SIGNAL(clicked()),this,SLOT(leaderboard()));
    scene->addItem(lboards);

    Button* quit = new Button(QString("QUIT"));
    txPos = this->width()/2 - quit->boundingRect().width()/2;
    quit->setPos(txPos,480);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quit);
}

void Game::dolzina(){ //omogoca izbiro dolzine proge

    removeAllItems();
    Button* stiri = new Button(QString("400M"));
    int txPos = this->width()/2 - stiri->boundingRect().width()/2;
    stiri->setPos(txPos,400);
    stiri->setZValue(11);
    connect(stiri,SIGNAL(clicked()),this,SLOT(dg1()));
    scene->addItem(stiri);

    Button* osem = new Button(QString("800M"));
    osem->setPos(txPos,460);
    osem->setZValue(11);
    connect(osem,SIGNAL(clicked()),this,SLOT(dg2()));
    scene->addItem(osem);
}

void Game::dg1(){ //izbira dolzine proge
    trackLength=400;
    start();
}

void Game::dg2(){ //izbira dolzine proge
    trackLength=800;
    start();
}

void Game::vehicleSelection(){ //izbira avtov

    if(izberi==0){
     cname=list2d[listPos][0];
     carname1=list2d[listPos][1];
     topspeed1=list2d[listPos][2].toInt();
     startBoost=1+((list2d[listPos][3].toFloat())/10);
     gearMax=list2d[listPos][4].toInt();
    }

    if(izberi==1){
     cname2=list2d[listPos][0];
     carname2=list2d[listPos][1];
     topspeed2=list2d[listPos][2].toInt();
     startBoost2=(list2d[listPos][3].toFloat())/10;
     gearMax2=list2d[listPos][4].toInt();
    }

    removeAllItems();
    //text ki pove kateri player izbbira avto
    QGraphicsTextItem * text= new QGraphicsTextItem();
    if(izberi==1)text->setPlainText("CHOOSE YOUR CAR, PLAYER2");
    else text->setPlainText("CHOOSE YOUR CAR, PLAYER1");
    text->setDefaultTextColor(Qt::white);
    text->setPos(450,200);
    text->setScale(2);
    scene->addItem(text);

    QGraphicsPixmapItem * selecto = new QGraphicsPixmapItem();
    selecto->setPixmap(QPixmap(":/images/selection.png"));
    selecto->setPos(460,250);
    selecto->setZValue(5);
    scene->addItem(selecto);

    QGraphicsPixmapItem * one = new QGraphicsPixmapItem();
    if(izberi==1)one->setPixmap(QPixmap(":/images/"+cname2+".png"));
    else one->setPixmap(QPixmap(":/images/"+cname+".png"));
    one->setPos(selecto->pos().x()+70,selecto->pos().y()+20);
    scene->addItem(one);

    QGraphicsTextItem * text1= new QGraphicsTextItem();
    if(izberi==1)text1->setPlainText(carname2);
    else text1->setPlainText(carname1);
    text1->setDefaultTextColor(Qt::white);
    text1->setScale(1.5);
    text1->setPos(selecto->pos().x()+60,selecto->pos().y()+100);
    scene->addItem(text1);

    QGraphicsTextItem * text11= new QGraphicsTextItem();
    if(izberi==1)text11->setPlainText("Max speed: "+QString::number(topspeed2)+"km/h");
    else text11->setPlainText("Max speed: "+QString::number(topspeed1)+"km/h");
    text11->setDefaultTextColor(Qt::white);
    text11->setScale(1.5);
    text11->setPos(selecto->pos().x()+60,selecto->pos().y()+140);
    scene->addItem(text11);

    QGraphicsTextItem * text12= new QGraphicsTextItem();
    if(izberi==1)text12->setPlainText("0-100km/h: "+QString::number((startBoost2*10))+"s");
    else text12->setPlainText("0-100km/h: "+QString::number(((startBoost-1)*10))+"s");
    text12->setDefaultTextColor(Qt::white);
    text12->setScale(1.5);
    text12->setPos(selecto->pos().x()+60,selecto->pos().y()+180);
    scene->addItem(text12);

    QGraphicsTextItem * text13= new QGraphicsTextItem();
    if(izberi==1)text13->setPlainText("Gears: "+QString::number(gearMax2));
    else text13->setPlainText("Gears: "+QString::number(gearMax));
    text13->setDefaultTextColor(Qt::white);
    text13->setScale(1.5);
    text13->setPos(selecto->pos().x()+60,selecto->pos().y()+220);
    scene->addItem(text13);

    Button * right = new Button("");
    right->setBrush(QBrush(QImage(":/images/right.png")));
    right->setRect(right->pos().x(),right->pos().y(),50,50);
    right->setPos(selecto->pos().x()+310,selecto->pos().y()+125);
    scene->addItem(right);
    connect(right,SIGNAL(clicked()),this,SLOT(rightu()));

    Button * left = new Button("");
    left->setBrush(QBrush(QImage(":/images/left.png")));
    left->setRect(left->pos().x(),left->pos().y(),50,50);
    left->setPos(selecto->pos().x()-60,selecto->pos().y()+125);
    scene->addItem(left);
    connect(left,SIGNAL(clicked()),this,SLOT(leftu()));

    Button* choose1 = new Button(QString("CHOOSE"));
    choose1->setPos(selecto->pos().x()+25,selecto->pos().y()+310);
    scene->addItem(choose1);
    if(izberi==1) connect(choose1,SIGNAL(clicked()),this,SLOT(P2select()));
    else connect(choose1,SIGNAL(clicked()),this,SLOT(P1select()));

}

void Game::P1select(){ //izbira 1 za player1

   if(player2==1){
        izberi=1;
        listPos=0;
        vehicleSelection();
    }
    else dolzina();
}

void Game::P2select(){ //izbira 1 za player1

    dolzina();
}

void Game::endScreen(){ //izpis koncnega rezultata in leaderboards

    removeAllItems();
    QString querry;
    querry="SELECT * FROM "+lboardGameMode+" ORDER BY cast(time as int) asc  LIMIT 5";
    QString choose="FULL";
    scene->setSceneRect(0,0,1200,800);
    setScene(scene);
    setBackgroundBrush(Qt::black);

    if(leaders==0) {
       querry="SELECT * FROM "+lboardGameMode+" WHERE time!='Not Finnished' ORDER BY cast(time as int) asc  LIMIT 5";
       choose="FULL";
       leaders=1;
    }
    else if(leaders==1){
            querry="SELECT * FROM "+lboardGameMode+" ORDER BY Time";
            choose="TOP5";
            leaders=0;
    }

    Button* replay = new Button(QString("REPLAY"));
    int txPos = this->width()/2 - replay->boundingRect().width()/2;
    replay->setPos(txPos,510);
    replay->setZValue(11);
    connect(replay,SIGNAL(clicked()),this,SLOT(replay()));
    scene->addItem(replay);

    Button* quit = new Button(QString("QUIT"));
    txPos = this->width()/2 - quit->boundingRect().width()/2;
    quit->setPos(txPos,570);
    quit->setZValue(12);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quit);

    Button* lead = new Button(QString(choose));
    lead->setPos(txPos,450);
    lead->setZValue(11);
    connect(lead,SIGNAL(clicked()),this,SLOT(endScreen()));
    scene->addItem(lead);

    connOpen(mydb);

    Lboard * lboard= new Lboard();

    QFontDatabase::addApplicationFont(":/fonts/FredokaOne-Regular.ttf");
    QFont f("Fredoka One", 12, QFont::Normal);

    QSqlQuery query;
    query.exec(querry);

    QGridLayout * layout=new QGridLayout;
         int counter=0;

    while(query.next()){

               value1 = new QLabel;
               value2 = new QLabel;
               value3 = new QLabel;
               value4 = new QLabel;

               value1->setFont(f);
               value2->setFont(f);
               value3->setFont(f);
               value4->setFont(f);

               value1->setStyleSheet("color: white");
               value2->setStyleSheet("color: white");
               value3->setStyleSheet("color: white");
               value4->setStyleSheet("color: white");

               value1->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
               value2->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
               value3->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);
               value4->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum);

               value1->setText(query.value(0).toString());
               value2->setText(query.value(1).toString());
               value3->setText(query.value(2).toString());
               value4->setText(query.value(3).toString());

               layout->addWidget(value1,counter,0,Qt::AlignHCenter);
               layout->addWidget(value2,counter,1,Qt::AlignHCenter);
               layout->addWidget(value3,counter,2,Qt::AlignHCenter);
               layout->addWidget(value4,counter,3,Qt::AlignHCenter);
               counter++;
    }

    lboard->setStyleSheet("background-color: black");
    lboard->setLayout(layout);
    scene->addWidget(lboard->scrollArea)->setPos(358,145);

    connClose(mydb);

   //ustvari koncni cas na zaslonu
   endtime= new QGraphicsTextItem();
   if(shiftmajstor==1){
       endtime->setPlainText("PLAYER1 GEARS: "+QString::number(gears)+"     "+"PLAYER2 GEARS: "+QString::number(gears2));
   }
   else{
       if(player2==0) endtime->setPlainText("PLAYER1 TIME: "+tajmu+"     "+"PLAYER2 TIME: "+QString::number(P2EndTime)+"s");
       else endtime->setPlainText("PLAYER1 TIME: "+tajmu+"     "+"PLAYER2 TIME: "+tajmu2);
   }


   endtime->setDefaultTextColor(Qt::white);
   endtime->setZValue(12);
   endtime->setScale(2);
   txPos = this->width()/2 - endtime->boundingRect().width()/2;
   endtime->setPos(400,60);
   scene->addItem(endtime);
}

void Game::rightu(){

    if(listPos<9){
    listPos++;
    vehicleSelection();
    }
}

void Game::leftu(){

    if(listPos>0){
    listPos--;
    vehicleSelection();
    }
}

void Game::pickGameMode(){

    removeAllItems();
    Button* race = new Button(QString("Race"));
    int txPos = this->width()/2 - race->boundingRect().width()/2;
    race->setPos(txPos,400);
    race->setZValue(11);
    connect(race,SIGNAL(clicked()),this,SLOT(vehicleSelection()));
    scene->addItem(race);

    Button* shiftu = new Button(QString("ShiftMasters"));
    shiftu->setPos(txPos,460);
    shiftu->setZValue(11);
    connect(shiftu,SIGNAL(clicked()),this,SLOT(shiftMasters()));
    scene->addItem(shiftu);

    Button* back = new Button(QString("BACK"));
    back->setPos(txPos,580);
    connect(back,SIGNAL(clicked()),this,SLOT(displayMainMenu()));
    back->setZValue(12);
    scene->addItem(back);

}

void Game::shiftMasters(){

    shiftmajstor=1;
    vehicleSelection();
}

void Game::removeAllItems(){ //odstrani vse elemente iz scene

    if(brisi==1 && timer->isActive()){

    timer->stop();
    timer2->stop();
    mtimer->stop();
    if(player2==1)mtimer2->stop();
    shifter->stop();
    shifter2->stop();
    timeIncrease->stop();
    timeIncrease2->stop();
    move_timer->stop();
    killTimer(timerId);
    cai->move_timer->stop();
    }

    QList<QGraphicsItem *> stvari = scene->items();
    for(int i=0, n=stvari.size();i<n;i++){
        if((typeid(*(stvari[i]))==typeid(Button)) ||
            (typeid(*(stvari[i]))==typeid(QTableView)) ||
            (typeid(*(stvari[i]))==typeid(Count)) ||
            (typeid(*(stvari[i]))==typeid(Player)) ||
            (typeid(*(stvari[i]))==typeid(Player2)) ||
            (typeid(*(stvari[i]))==typeid(QGraphicsRectItem)) ||
            (typeid(*(stvari[i]))==typeid(QGraphicsTextItem)) ||
            (typeid(*(stvari[i]))==typeid(QGraphicsPixmapItem))
           )

            scene->removeItem(stvari[i]);
    }

}

void Game::insert(QString name, QString car, QString time, QString distance){ //doda podatke v podatkovno bazo

    QSqlQuery query;
    query.prepare("CREATE TABLE players (name VARCHAR(20) PRIMARY KEY NOT NULL,"
                  "car varchar(20) NOT NULL, time VARCHAR(20) NOT NULL, distance varchar(20) NOT NULL)");
    query.exec();
    query.prepare("CREATE TABLE shiftmasters (name VARCHAR(20) PRIMARY KEY NOT NULL,"
                  "car varchar(20) NOT NULL, time VARCHAR(20) NOT NULL, distance varchar(20) NOT NULL)");
    query.exec();
    qDebug()<<query.lastError();

    if(name==""){
        query.exec("select count(*) from "+lboardGameMode+";");
        qDebug() << query.value(0);
        query.next();
        name="player "+QString::number(query.value(0).toInt()+1);
    }

    query.prepare("INSERT INTO "+lboardGameMode+"(name, car, time, distance) values(:name,:car,:time,:distance)");
    query.bindValue(":name",name);
    query.bindValue(":car",car);
    query.bindValue(":time",time);
    query.bindValue(":distance",distance);
    query.exec();

    qDebug()<<query.lastError();
}

void Game::connClose(QSqlDatabase mydb){ //zapre povezavo z podatkovno bazo

    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

void Game::fillList(){

    list.push_back("agera");
    list.push_back("Koenigsegg Agera RS");
    list.push_back("320");
    list.push_back("2.9");
    list.push_back("6");
    list2d.push_back(list);
    list.clear();

    list.push_back("ferari");
    list.push_back("Ferrari 488 GTB");
    list.push_back("305");
    list.push_back("3.6");
    list.push_back("6");
    list2d.push_back(list);
    list.clear();

    list.push_back("vanquish");
    list.push_back("Aston Martin Vanquish");
    list.push_back("300");
    list.push_back("4.2");
    list.push_back("6");
    list2d.push_back(list);
    list.clear();

    list.push_back("mclaren");
    list.push_back("McLaren 650S Coupe ");
    list.push_back("299");
    list.push_back("4.1");
    list.push_back("6");
    list2d.push_back(list);
    list.clear();

    list.push_back("tuatara");
    list.push_back("SSC Tuatara");
    list.push_back("313");
    list.push_back("3.6");
    list.push_back("6");
    list2d.push_back(list);
    list.clear();

    list.push_back("i8");
    list.push_back("BMW i8 SuperCharged");
    list.push_back("296");
    list.push_back("4");
    list.push_back("6");
    list2d.push_back(list);
    list.clear();

    list.push_back("huracan");
    list.push_back("Lamborghini Huracan");
    list.push_back("325");
    list.push_back("3.2");
    list.push_back("6");
    list2d.push_back(list);
    list.clear();

    list.push_back("porche");
    list.push_back("Porsche 911");
    list.push_back("318");
    list.push_back("3.3");
    list.push_back("6");
    list2d.push_back(list);
    list.clear();

    list.push_back("tesla");
    list.push_back("Tesla Model S");
    list.push_back("289");
    list.push_back("4.1");
    list.push_back("6");
    list2d.push_back(list);
    list.clear();

    list.push_back("camaro");
    list.push_back("Chevrolet Camaro SS");
    list.push_back("301");
    list.push_back("3.6");
    list.push_back("6");
    list2d.push_back(list);
    list.clear();
}

bool Game::connOpen(QSqlDatabase mydb){ //odpre povezavo z podatkovno bazo

    QString dbPath = QCoreApplication::applicationDirPath();
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(qApp->applicationDirPath()
                        + QDir::separator()
                        + "lboards.db" );
    //mydb.setDatabaseName("D:/QT/Matura/lboards.db");
    if(mydb.open())
        qDebug() << "CONNECTED";
    else
        qDebug() << "NOT CONNECTED";
}

void Game::konec(){ //konca igro

     if(winnerP1==1 || winnerP2==1){

         if(konc==0){

            removeAllItems();
            konc=1;
            if(koncenvnos==0){

               if(P1EndTime==0) tajmu="Not Finnished";
               else tajmu=QString::number(P1EndTime)+"s";

               distancu=QString::number(trackLength)+"m";

         connOpen(mydb);

         if(shiftmajstor==1){
             if(gears>gears2)tajmu="First";
             else tajmu="Second";
             distancu="Gears: "+QString::number(gears);
         }

         qDebug() << name1 << cname <<tajmu << distancu;
         insert(name1,cname,tajmu,distancu);

         if(player2==1){

             if(P2EndTime==0) tajmu2="Not Finnished";
             else tajmu2=QString::number(P2EndTime)+"s";

             insert(name2,cname2,tajmu2,distancu);

         }

         connClose(mydb);
         koncenvnos=1;

              }

      endScreen();

         }

     }

}
