#-------------------------------------------------
#
# Project created by QtCreator 2018-11-26T16:33:48
#
#-------------------------------------------------

QT       += core gui \
        multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EscapeRoomV01
TEMPLATE = app


SOURCES += sources/main.cpp\
        sources/mainwindow.cpp\
        sources/game.cpp\
    sources/player.cpp \
    sources/gift.cpp \
    sources/key.cpp \
    sources/door.cpp \
    sources/ingameobjects.cpp \
    sources/chest.cpp \
    sources/staticpuzzle.cpp \
    sources/invertedfloor.cpp \
    sources/dynamicpuzzle1.cpp \
    sources/puzzle.cpp \
    sources/inventory.cpp \
    sources/dynamicpuzzle2.cpp \
    sources/stopwatch.cpp \
    sources/sprite.cpp \
    sources/help.cpp

HEADERS  += headers/mainwindow.h \
    headers/game.h \
    headers/player.h \
    headers/gift.h \
    headers/key.h \
    headers/door.h \
    headers/ingameobjects.h \
    headers/chest.hpp \
    headers/staticpuzzle.h \
    headers/invertedfloor.h \
    headers/dynamicpuzzle1.h \
    headers/puzzle.h \
    headers/inventory.h \
    headers/dynamicpuzzle2.h \
    headers/stopwatch.h \
    headers/sprite.h \
    headers/help.h

FORMS    += ui/mainwindow.ui

RESOURCES += \
    images.qrc \
    json.qrc \
    sounds.qrc

DISTFILES += \
    ../document.json
