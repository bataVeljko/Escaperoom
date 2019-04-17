#include "headers/chest.hpp"

Chest::Chest(const QPixmap& picture) {
    setPixmap(picture);
}

void Chest::mousePressEvent(QGraphicsSceneMouseEvent *){}

void Chest::mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsView *view){
    //checking mouse click and player distance from the chest
    if(event->button() == Qt::LeftButton && this->distance() < CHECK_DISTANCE){
        //if player already have level key, user won't be able to open puzzle again
        if(!getPlayer()->keyList.contains(getLK())){
            switch (getPlayer()->getCurrentLevel()) {
                case DYNAMIC_LEVEL_2:{
                    //setting scene for second dynamic puzzle
                    auto *dynamicPuzzle2Scene = new DynamicPuzzle2(view, view->scene(), getPlayer()->getCurrentLevel());
                    dynamicPuzzle2Scene->setPlayer(this->getPlayer());
                    dynamicPuzzle2Scene->setLevelKey(this->getLK());
                    dynamicPuzzle2Scene->setLog(getLog());
                    view->setScene(dynamicPuzzle2Scene);
                    break;
                }
                case DYNAMIC_LEVEL_1: {
                    //setting scene for first dynamic puzzle
                    auto *dynamicPuzzle1Scene = new DynamicPuzzle1(view, view->scene(), getPlayer()->getCurrentLevel());
                    dynamicPuzzle1Scene->setPlayer(this->getPlayer());
                    dynamicPuzzle1Scene->setLevelKey(this->getLK());
                    dynamicPuzzle1Scene->setLog(getLog());
                    view->setScene(dynamicPuzzle1Scene);
                    break;
                }
                default: {
                    //setting new scene for static puzzles
                    auto *puzzleScene = new StaticPuzzle(view, view->scene(), getPlayer()->getCurrentLevel());
                    puzzleScene->setPlayer(this->getPlayer());
                    puzzleScene->setLevelKey(this->getLK());
                    puzzleScene->setLog(getLog());
                    view->setScene(puzzleScene);
                }
            }
        }
    }
}

bool Chest::isOpened() {
    return _opened;
}

void Chest::openChest(bool o) {
    _opened = o;
}
