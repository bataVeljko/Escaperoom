#ifndef PUZZLE_H
#define PUZZLE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QLayout>
#include <QDebug>
#include <QLineEdit>
#include <QSound>
#include "headers/player.h"
#include "headers/key.h"

/**
 * @brief Abstract class for puzzles
 */
class Puzzle : public QGraphicsScene {


public:

    /**
     * @brief       Pure virtual method that will be implemented in subclass's
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;

    /**
     * @brief       Return current level
     */
    qint16 getCl();

    /**
     * @brief       Return current main view
     */
    QGraphicsView *getView();

    /**
     * @brief       Return current scene
     */
    QGraphicsScene *getScene();

    /**
     * @brief       Setter for player
     */
    void setPlayer(Player *p);

    /**
     * @brief       Setter for level key
     */
    void setLevelKey(Key *lk);

    /**
     * @brief       Return player
     */
    Player *getPlayer();

    /**
     * @brief       Return level key
     */
    Key *getLK();

    /**
     * @brief       Return user log
     */
    QLineEdit *getLog();

    /**
     * @brief       Setter for user's log
     */
    void setLog(QLineEdit *l);

    QSound *_fail_sound = new QSound(QString(":/resources/sounds/fail_Windows.wav")); //!< Sound that will be played if user send wrong solution for check

protected:

    /**
     * @brief           Explicit constructorfor Puzzle abstract class
     * @param parent    Main view
     * @param scene     Current scene
     * @param cl        Current level
     */
    explicit Puzzle(QGraphicsView *parent, QGraphicsScene *scene, qint16 cl);
    QGraphicsPixmapItem *_closeBtn{}; //!< Close button,for closing puzzle scene

private:
    QGraphicsView *_parent; //!< Main view
    QGraphicsScene *_scene; //!< Current scene
    qint16 cLevel; //!< Current level
    Player *_player{}; //!< Object of class Player
    Key *_levelKey{}; //!< Level key
    QLineEdit *_log{}; //!< User's log
};

#endif // PUZZLE_H
