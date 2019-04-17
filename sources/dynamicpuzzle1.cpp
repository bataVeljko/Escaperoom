#include "headers/dynamicpuzzle1.h"

namespace Coordinates {
    qint16 boatIsland1X = 900;
    qint16 boatIsland1Y = 500;
    qint16 boatIsland2X = 150;
    qint16 boatIsland2Y = 250;

    qint16 wolfIsland1X = 1050;
    qint16 wolfIsland1Y = 300;
    qint16 wolfIsland2X = 0;
    qint16 wolfIsland2Y = 200;

    qint16 goatIsland1X = 1050;
    qint16 goatIsland1Y = 400;
    qint16 goatIsland2X = 30;
    qint16 goatIsland2Y = 300;

    qint16 lettuceIsland1X = 1170;
    qint16 lettuceIsland1Y = 480;
    qint16 lettuceIsland2X = 0;
    qint16 lettuceIsland2Y = 380;
}

DynamicPuzzle1::DynamicPuzzle1(QGraphicsView *parent, QGraphicsScene *scene, qint16 cl) :
    Puzzle(parent, scene, cl)
{
    setBackgroundBrush(QImage(":/resources/puzzles/dp1.png"));
    setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //adding close button item to the scene
    _closeBtn = new QGraphicsPixmapItem(QPixmap(":/resources/buttons/close_btn.png"));
    _closeBtn->moveBy(CLOSE_BTN_POSITION, 0);
    _closeBtn->setFlag(QGraphicsItem::ItemIsFocusable);
    this->addItem(_closeBtn);

    _boat = new QGraphicsPixmapItem(QPixmap(":/resources/pictures/boat.png"));
    _boat->setPos(QPoint(Coordinates::boatIsland1X, Coordinates::boatIsland1Y));
    this->addItem(_boat);

    _wolf = new QGraphicsPixmapItem(QPixmap(":/resources/pictures/wolf.png"));
    _wolf->setPos(QPoint(Coordinates::wolfIsland1X, Coordinates::wolfIsland1Y));
    this->addItem(_wolf);

    _goat = new QGraphicsPixmapItem(QPixmap(":/resources/pictures/goat.png"));
    _goat->setPos(QPoint(Coordinates::goatIsland1X, Coordinates::goatIsland1Y));
    this->addItem(_goat);

    _lettuce = new QGraphicsPixmapItem(QPixmap(":/resources/pictures/lettuce.png"));
    _lettuce->setPos(QPoint(Coordinates::lettuceIsland1X, Coordinates::lettuceIsland1Y));
    this->addItem(_lettuce);

}

void DynamicPuzzle1::puzzleOver(){
    //delete current scene
    this->deleteLater();
    //raise old scene
    getView()->setScene(getScene());
}

void DynamicPuzzle1::checkForEating(qint16 boatIslandNumber){
    switch (boatIslandNumber) {
        case 1: {
            if(_wolfPosition == island2 && _goatPosition == island2){
                _fail_sound->setLoops(SET_SOUND_LOOP);
                _fail_sound->play();
                puzzleOver();
                //qDebug() << "Wolf has eaten goat! Be careful next time";
                getLog()->setText("Wolf has eaten goat! Be careful next time");
            }
            if(_goatPosition == island2 && _lettucePosition == island2){
                _fail_sound->setLoops(SET_SOUND_LOOP);
                _fail_sound->play();
                puzzleOver();
                //qDebug() << "Goat has eaten lettuce! Be careful next time";
                getLog()->setText("Goat has eaten lettuce! Be careful next time");
            }
            break;
        }
        case 2: {
            if(_wolfPosition == island1 && _goatPosition == island1){
                _fail_sound->setLoops(SET_SOUND_LOOP);
                _fail_sound->play();
                puzzleOver();
                //qDebug() << "Wolf has eaten goat! Be careful next time";
                getLog()->setText("Wolf has eaten goat! Be careful next time");
            }
            if(_goatPosition == island1 && _lettucePosition == island1){
                _fail_sound->setLoops(SET_SOUND_LOOP);
                _fail_sound->play();
                puzzleOver();
                //qDebug() << "Goat has eaten lettuce! Be careful next time";
                getLog()->setText("Goat has eaten lettuce! Be careful next time");
            }
            break;
        }
    }
}

void DynamicPuzzle1::checkForWinning(){
    if((_wolfPosition == island2) && (_goatPosition == island2) && (_lettucePosition == island2)){
        getLK()->setKeyAvailability(true);
        //qDebug() << "Chest unlocked, click to get key";
        getLog()->setText("Chest unlocked, click to get key");
        puzzleOver();
    }
}

void DynamicPuzzle1::mousePressEvent(QGraphicsSceneMouseEvent *){
    if(_closeBtn->isUnderMouse()){
        puzzleOver();
    }
    else if(_wolf->isUnderMouse()){
        if(_numberOfItemsOnTheBoat < MAX_NUM_OF_ITEMS && _wolfPosition == island1 && _boatIsland == FIRST_ISLAND){
            _wolfPosition = boat;
            _numberOfItemsOnTheBoat++;
            _wolf->setPos(Coordinates::boatIsland1X+POSITION_CORRECTION, Coordinates::boatIsland1Y);
        }
        else if(_wolfPosition == boat && _boatIsland == FIRST_ISLAND){
            _numberOfItemsOnTheBoat--;
            _wolfPosition = island1;
            _wolf->setPos(Coordinates::wolfIsland1X, Coordinates::wolfIsland1Y);
        }
        else if(_numberOfItemsOnTheBoat < MAX_NUM_OF_ITEMS && _wolfPosition == island2 && _boatIsland == SECOND_ISLAND){
            _numberOfItemsOnTheBoat++;
            _wolfPosition = boat;
            _wolf->setPos(Coordinates::boatIsland2X+POSITION_CORRECTION, Coordinates::boatIsland2Y);
        }
        else if(_wolfPosition == boat && _boatIsland == MAX_NUM_OF_ITEMS){
            _numberOfItemsOnTheBoat--;
            _wolfPosition = island2;
            _wolf->setPos(Coordinates::wolfIsland2X, Coordinates::wolfIsland2Y);
            checkForWinning();
        }
        else{
            //qDebug() << "No more space on the boat";
        }
    }
    else if(_goat->isUnderMouse()){
        if(_numberOfItemsOnTheBoat < MAX_NUM_OF_ITEMS && _goatPosition == island1 && _boatIsland == FIRST_ISLAND){
            _goatPosition = boat;
            _numberOfItemsOnTheBoat++;
            _goat->setPos(Coordinates::boatIsland1X+POSITION_CORRECTION, Coordinates::boatIsland1Y);
        }
        else if(_goatPosition == boat && _boatIsland == FIRST_ISLAND){
            _numberOfItemsOnTheBoat--;
            _goatPosition = island1;
            _goat->setPos(Coordinates::goatIsland1X, Coordinates::goatIsland1Y);
        }
        else if(_numberOfItemsOnTheBoat < MAX_NUM_OF_ITEMS && _goatPosition == island2 && _boatIsland == SECOND_ISLAND){
            _numberOfItemsOnTheBoat++;
            _goatPosition = boat;
            _goat->setPos(Coordinates::boatIsland2X+POSITION_CORRECTION, Coordinates::boatIsland2Y);
        }
        else if(_goatPosition == boat && _boatIsland == SECOND_ISLAND){
            _numberOfItemsOnTheBoat--;
            _goatPosition = island2;
            _goat->setPos(Coordinates::goatIsland2X, Coordinates::goatIsland2Y);
            checkForWinning();
        }
        else{
            //qDebug() << "No more space on the boat";
        }
    }
    else if(_lettuce->isUnderMouse()){
        if(_numberOfItemsOnTheBoat < MAX_NUM_OF_ITEMS && _lettucePosition == island1 && _boatIsland == FIRST_ISLAND){
            _lettucePosition = boat;
            _numberOfItemsOnTheBoat++;
            _lettuce->setPos(Coordinates::boatIsland1X+POSITION_CORRECTION, Coordinates::boatIsland1Y);
        }
        else if(_lettucePosition == boat && _boatIsland == FIRST_ISLAND){
            _numberOfItemsOnTheBoat--;
            _lettucePosition = island1;
            _lettuce->setPos(Coordinates::lettuceIsland1X, Coordinates::lettuceIsland1Y);
        }
        else if(_numberOfItemsOnTheBoat < MAX_NUM_OF_ITEMS && _lettucePosition == island2 && _boatIsland == SECOND_ISLAND){
            _numberOfItemsOnTheBoat++;
            _lettucePosition = boat;
            _lettuce->setPos(Coordinates::boatIsland2X+POSITION_CORRECTION, Coordinates::boatIsland2Y);
        }
        else if(_lettucePosition == boat && _boatIsland == SECOND_ISLAND){
            _numberOfItemsOnTheBoat--;
            _lettucePosition = island2;
            _lettuce->setPos(Coordinates::lettuceIsland2X, Coordinates::lettuceIsland2Y);
            checkForWinning();
        }
        else{
            //qDebug() << "No more space on the boat";
        }

    }
    else if(_boat->isUnderMouse()){
        if(_numberOfItemsOnTheBoat == MAX_NUM_OF_ITEMS && _boatIsland == FIRST_ISLAND){
            //ship to island 2
            _boat->setPos(Coordinates::boatIsland2X, Coordinates::boatIsland2Y);
            _boatIsland = SECOND_ISLAND;
            if(_wolfPosition == boat){
                _wolf->setPos(Coordinates::boatIsland2X+POSITION_CORRECTION, Coordinates::boatIsland2Y);
            }
            if(_goatPosition == boat){
                _goat->setPos(Coordinates::boatIsland2X+POSITION_CORRECTION, Coordinates::boatIsland2Y);
            }
            if(_lettucePosition == boat){
                _lettuce->setPos(Coordinates::boatIsland2X+POSITION_CORRECTION, Coordinates::boatIsland2Y);
            }

            //if (wolf and goat) or (goat and lettuce) are alone on the island1, puzzle over and start again
            checkForEating(SECOND_ISLAND);
        }
        else if(_boatIsland == SECOND_ISLAND){
            //ship to island 1
            _boat->setPos(Coordinates::boatIsland1X, Coordinates::boatIsland1Y);
            _boatIsland = FIRST_ISLAND;
            if(_wolfPosition == boat){
                _wolf->setPos(Coordinates::boatIsland1X+POSITION_CORRECTION, Coordinates::boatIsland1Y);
            }
            if(_goatPosition == boat){
                _goat->setPos(Coordinates::boatIsland1X+POSITION_CORRECTION, Coordinates::boatIsland1Y);
            }
            if(_lettucePosition == boat){
                _lettuce->setPos(Coordinates::boatIsland1X+POSITION_CORRECTION, Coordinates::boatIsland1Y);
            }

            //if (wolf and goat) or (goat and lettuce) are alone on the island2, puzzle over and start again
            checkForEating(FIRST_ISLAND);
        }
    }
}
