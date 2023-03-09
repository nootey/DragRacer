#-------------------------------------------------
#
# Project created by QtCreator 2017-12-26T19:22:11
#
#-------------------------------------------------

QT       += core gui sql
RC_FILE = myapp.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Matura
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    game.cpp \
    countdown.cpp \
    button.cpp \
    player.cpp \
    player2.cpp \
    leaderboard.cpp

HEADERS += \
    game.h \
    countdown.h \
    button.h \
    player.h \
    player2.h \
    leaderboard.h

RESOURCES += \
    res.qrc

DISTFILES +=
