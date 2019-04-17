#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <cmath>
#include <QDebug>
#include "headers/sprite.h"
#include "headers/key.h"
#include "headers/invertedfloor.h"

/**
 * @brief Class that represent player, his picture and key collection
 */
class Player : public QGraphicsPixmapItem {

public:

    /**
     * @brief       Player constructor
     * @param name  User's nickname
     */
    Player(QString name);

    /**
     * @brief       Player destructor
     */
    ~Player();

    /**
     * @brief       Player's key list, that can hold one universal key and one level key
     */
    QList<Key*> keyList;

    /**
     * @brief       Keyboar press event function for player's moving
     * @param key   Represent which key is pressed
     */
    void keyPressEvent(QKeyEvent *key);

    /**
     * @brief       Returns current level
     */
    qint16 getCurrentLevel();

    /**
     * @brief       Return object of class InvertedFloor
     */
    InvertedFloor *getInvertedFloor();

    /**
     * @brief       Return player's dummy
     */
    QGraphicsPixmapItem *getDummy();

    /**
     * @brief       Set current level
     */
    void setCurrentLevel(qint16 cl);

    /**
     * @brief       Set object of class InvertedFloor
     */
    void setInvertedFloor(InvertedFloor *iFloor);

    /**
     * @brief       Set player's dummy
     */
    void setDummy(QGraphicsPixmapItem *dummy);

    /**
     * @brief       Return user's nickname
     */
    QString getUsername();

    /**
     * @brief       Initialize player's sprite sheet for player's moving
     */
    void initSpriteSheets();

    /**
     * @brief       Set player's sprite sheet
     */
    void setSprite(Sprite& sprite);
private:
    qreal _step = 3.0; //!< Player's speed on y axis
    qreal _doubleStep = 2 * _step; //!< Player's speed on x axis
    qint16 _currentLevel; //!< Current level
    InvertedFloor *_invertedfloor{}; //!< Object that represent inverted floor
    QGraphicsPixmapItem* _dummy; //!< Object that always goes with player and help us to solve collision
    QString _username; //!< User nickname
    Sprite _wSpriteSheet; //!< SpriteSheet for moving up
    Sprite _aSpriteSheet; //!< SpriteSheet for moving left
    Sprite _sSpriteSheet; //!< SpriteSheet for moving down
    Sprite _dSpriteSheet; //!< SpriteSheet for moving right

    bool checkCollision(); //!< Cheking collision between player and the rest of the scene
};

#endif // PLAYER_H
