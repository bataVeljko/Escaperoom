#ifndef INGAMEOBJECTS_H
#define INGAMEOBJECTS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <QDebug>
#include <QObject>
#include <QLineEdit>
#include "headers/player.h"
#include "headers/key.h"

/**
 * @brief Abstract class for all clickable objects on the scene
 */
class InGameObjects : public QGraphicsPixmapItem {

public:

    /**
     * @brief       Virtual method which is used for event handling.
     * @param event An event which should be handled.
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;

    /**
     * @brief       Player getter.
     */
    Player *getPlayer();

    /**
     * @brief       Universal Key getter.
     */
    Key *getUK();

    /**
     * @brief       Level Key getter.
     */
    Key *getLK();

    /**
     * @brief       Player setter.
     */
    void setPlayer(Player *p);

    /**
     * @brief       Universal Key setter.
     */
    void setUK(Key *uk);

    /**
     * @brief       Level Key setter.
     */
    void setLK(Key *lk);

    /**
     * @brief       In-game log getter.
     */
    QLineEdit *getLog();

    /**
     * @brief       In-game log setter.
     */
    void setLog(QLineEdit *l);

protected:

    /**
     * @brief       InGameObjects constructor.
     */
    explicit InGameObjects() = default;

    /**
     * @brief       InGameObjects destructor.
     */
    ~InGameObjects() = default;

    /**
     * @brief       Distance between Player and InGameObjects.
     *              We use it to check if the player can click on the object.
     */
    qreal distance();

private:
    Player *_player {}; //!< Controllable object.
    Key *_universalKey {}; //!< Key which is in Gift.
    Key *_levelKey {}; //!< Key which is in Chest.
    QLineEdit *_log {}; //!< In-game log which shows messages.
};

#endif // INGAMEOBJECTS_H
