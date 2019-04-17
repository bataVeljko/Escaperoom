#include "headers/door.h"

Door::Door(const QPixmap& picture)
    :_log(nullptr)
{
    setPixmap(picture);
}

void Door::mousePressEvent(QGraphicsSceneMouseEvent *){

}

void Door::mousePressEvent(QGraphicsSceneMouseEvent *event, const QPixmap& pic, qint32 xCoord) {
    //checking mouse click and player distance from the door
    if(event->button() == Qt::LeftButton && this->distance() < CHECK_DISTANCE){
        //checking if user have level key and the door isn't alredy opened
        if(getPlayer()->keyList.contains(getLK()) && !isOpened()){
            //qDebug() << "Door unlocked and opened using level key";
            getLog()->setText("Door unlocked and opened using level key");
            this->setPixmap(pic);
            this->setX(xCoord);
            getPlayer()->keyList.removeOne(getLK());
            openDoor(true);
            delete getLK();
        }
        //checking if user have universal key and the door isn't alredy opened
        else if(getPlayer()->keyList.contains(getUK()) && !isOpened()){
            //qDebug() << "Door unlocked using universal key";
            getLog()->setText("Door unlocked using universal key");
            this->setPixmap(pic);
            this->setX(xCoord);
            getPlayer()->keyList.removeOne(getUK());
            openDoor(true);
            delete getUK();
        }/*
        else if(isOpened()){
            qDebug() << "Door already opened";
            getLog()->setText("Door already opened");
        }*/
        else{
            //qDebug() << "Door locked, you need key";
            getLog()->setText("Door locked, you need key");
        }
    }
}

QLineEdit *Door::getLog(){
    return _log;
}

void Door::setLog(QLineEdit *l){
    _log = l;
}

bool Door::isOpened() {
    return _opened;
}

void Door::openDoor(bool o) {
    _opened = o;
}
