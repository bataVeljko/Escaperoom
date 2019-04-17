#include "headers/ingameobjects.h"


qreal InGameObjects::distance(){
    qreal deltaX = this->x() - _player->x();
    qreal deltaY = this->y() - _player->y();
    return (std::sqrt(deltaX*deltaX+deltaY*deltaY));
}

Player* InGameObjects::getPlayer(){
    return _player;
}

Key* InGameObjects::getUK(){
    return _universalKey;
}

Key* InGameObjects::getLK(){
    return _levelKey;
}

void InGameObjects::setPlayer(Player *p){
    _player = p;
}

void InGameObjects::setUK(Key *uk){
    _universalKey = uk;
}

void InGameObjects::setLK(Key *lk){
    _levelKey = lk;
}

QLineEdit *InGameObjects::getLog(){
    return _log;
}

void InGameObjects::setLog(QLineEdit *l){
    _log = l;
}
