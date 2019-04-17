#include "headers/player.h"
#include "headers/game.h"

#define X_DUMMY_POS (50)
#define Y_DUMMY_POS (128)

Player::Player(QString name) :
    _username(std::move(name))
{
    setPixmap(QPixmap(":/resources/outfits/dframe1.png"));
    _currentLevel = 1;
    _dummy = new QGraphicsPixmapItem;
    _dummy->setPixmap(QPixmap(":/resources/outfits/dummy.png"));
    initSpriteSheets();
}

Player::~Player() = default;

void Player::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
     case Qt::Key_A:
        _dummy->setPos(x()-_doubleStep+X_DUMMY_POS,y()+Y_DUMMY_POS);
        if(checkCollision()) {
            setPos(x()-_doubleStep, y() - _step);
            this->setSprite(_aSpriteSheet);

        }
        else {
            this->setPixmap(_aSpriteSheet.startingSprite());
        }
        break;
     case Qt::Key_D:
        _dummy->setPos(x()+_doubleStep+X_DUMMY_POS,y()+_step+Y_DUMMY_POS);
        if(checkCollision()) {
            setPos(x()+_doubleStep,y()+_step);
            this->setSprite(_dSpriteSheet);

        }
        else{
            this->setPixmap(_dSpriteSheet.startingSprite());
        }
        break;
     case Qt::Key_W:
        _dummy->setPos(x()+_doubleStep+X_DUMMY_POS,y()-_step+Y_DUMMY_POS);
        if(checkCollision()) {
            setPos(x()+_doubleStep,y()-_step);
            this->setSprite(_wSpriteSheet);
        }
        else {
            this->setPixmap(_wSpriteSheet.startingSprite());
        }
        break;
     case Qt::Key_S:
        _dummy->setPos(x()-_doubleStep+X_DUMMY_POS,y()+_step+Y_DUMMY_POS);
        if(checkCollision()) {
            setPos(x()-_doubleStep,y()+_step);
            this->setSprite(_sSpriteSheet);
        }
        else {
         this->setPixmap(_sSpriteSheet.startingSprite());
        }
        break;

    default: break;
    }
}
// We're checking if there's one more collision besides collision with the player.
bool Player::checkCollision() {
    return this->_dummy->collidingItems().size() <= 1;
}

qint16 Player::getCurrentLevel(){
    return _currentLevel;
}

InvertedFloor *Player::getInvertedFloor(){
    return _invertedfloor;
}

QGraphicsPixmapItem *Player::getDummy(){
    return _dummy;
}

void Player::setCurrentLevel(qint16 cl){
    _currentLevel = cl;
}

void Player::setInvertedFloor(InvertedFloor *iFloor){
    _invertedfloor = iFloor;
}

void Player::setDummy(QGraphicsPixmapItem *dummy){
    _dummy = dummy;
}

QString Player::getUsername() {
    return _username;
}
// It would be much nicer if we had more different frames/sprites for spritesheet
void Player::initSpriteSheets(){
    _aSpriteSheet.addSprite(":/resources/outfits/aframe1.png");
    _aSpriteSheet.addSprite(":/resources/outfits/aframe1.png");
    _aSpriteSheet.addSprite(":/resources/outfits/aframe1.png");
    _aSpriteSheet.addSprite(":/resources/outfits/aframe2.png");
    _aSpriteSheet.addSprite(":/resources/outfits/aframe2.png");
    _aSpriteSheet.addSprite(":/resources/outfits/aframe2.png");
    _aSpriteSheet.addSprite(":/resources/outfits/aframe1.png");
    _aSpriteSheet.addSprite(":/resources/outfits/aframe1.png");
    _aSpriteSheet.addSprite(":/resources/outfits/aframe1.png");
    _aSpriteSheet.addSprite(":/resources/outfits/aframe3.png");
    _aSpriteSheet.addSprite(":/resources/outfits/aframe3.png");
    _aSpriteSheet.addSprite(":/resources/outfits/aframe3.png");


    _wSpriteSheet.addSprite(":/resources/outfits/wframe1.png");
    _wSpriteSheet.addSprite(":/resources/outfits/wframe1.png");
    _wSpriteSheet.addSprite(":/resources/outfits/wframe1.png");
    _wSpriteSheet.addSprite(":/resources/outfits/wframe2.png");
    _wSpriteSheet.addSprite(":/resources/outfits/wframe2.png");
    _wSpriteSheet.addSprite(":/resources/outfits/wframe2.png");
    _wSpriteSheet.addSprite(":/resources/outfits/wframe1.png");
    _wSpriteSheet.addSprite(":/resources/outfits/wframe1.png");
    _wSpriteSheet.addSprite(":/resources/outfits/wframe1.png");
    _wSpriteSheet.addSprite(":/resources/outfits/wframe3.png");
    _wSpriteSheet.addSprite(":/resources/outfits/wframe3.png");
    _wSpriteSheet.addSprite(":/resources/outfits/wframe3.png");

    _sSpriteSheet.addSprite(":/resources/outfits/sframe1.png");
    _sSpriteSheet.addSprite(":/resources/outfits/sframe1.png");
    _sSpriteSheet.addSprite(":/resources/outfits/sframe1.png");
    _sSpriteSheet.addSprite(":/resources/outfits/sframe2.png");
    _sSpriteSheet.addSprite(":/resources/outfits/sframe2.png");
    _sSpriteSheet.addSprite(":/resources/outfits/sframe2.png");
    _sSpriteSheet.addSprite(":/resources/outfits/sframe1.png");
    _sSpriteSheet.addSprite(":/resources/outfits/sframe1.png");
    _sSpriteSheet.addSprite(":/resources/outfits/sframe1.png");
    _sSpriteSheet.addSprite(":/resources/outfits/sframe3.png");
    _sSpriteSheet.addSprite(":/resources/outfits/sframe3.png");
    _sSpriteSheet.addSprite(":/resources/outfits/sframe3.png");

    _dSpriteSheet.addSprite(":/resources/outfits/dframe1.png");
    _dSpriteSheet.addSprite(":/resources/outfits/dframe1.png");
    _dSpriteSheet.addSprite(":/resources/outfits/dframe1.png");
    _dSpriteSheet.addSprite(":/resources/outfits/dframe2.png");
    _dSpriteSheet.addSprite(":/resources/outfits/dframe2.png");
    _dSpriteSheet.addSprite(":/resources/outfits/dframe2.png");
    _dSpriteSheet.addSprite(":/resources/outfits/dframe1.png");
    _dSpriteSheet.addSprite(":/resources/outfits/dframe1.png");
    _dSpriteSheet.addSprite(":/resources/outfits/dframe1.png");
    _dSpriteSheet.addSprite(":/resources/outfits/dframe3.png");
    _dSpriteSheet.addSprite(":/resources/outfits/dframe3.png");
    _dSpriteSheet.addSprite(":/resources/outfits/dframe3.png");

}

void Player::setSprite(Sprite& sprite){
    this->setPixmap(sprite.nextSprite());
}
