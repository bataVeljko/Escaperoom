#ifndef DOOR_H
#define DOOR_H

#include <QLineEdit>
#include "ingameobjects.h"

#define CHECK_DISTANCE (100)

namespace Coordinates {
    extern qint16 openDoorX;
    extern qint16 openDoorY;
}
/**
 * @brief Static colidable object.
 *
 * This is an InGameObjects which is opened with the Key class object.
 * It is static, meaning that it doesn't change it's position during game.
 **/
class Door : public InGameObjects {

public:

    /**
     * @brief           Door constructor.
     * @param picture   Sets the pixmap of the door.
     */
    Door(const QPixmap& picture);

    /**
     * @brief           Door destructor.
     *                  Destroys Door object.
     */
    ~Door() = default;

    /**
     * @brief           Overrides from InGameObjects.
     * @param event     An event which should handled.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief           Detects if the object is mouse clicked.
     * @param event     An event which shoudl be handled.
     * @param pic       Opened door pixmap.
     * @param xCoord    Corrective coordinate because of pixmap width and height differences.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event, const QPixmap& pic, qint32 xCoord);

    /**
     * @brief       Returns in-game log.
     *              The log is shown in the bottom left corner.
     */
    QLineEdit *getLog();

    /**
     * @brief       Sets the value of in-game log.
     * @param l     The new value of in-game log.
     */
    void setLog(QLineEdit *l);

    /**
     * @brief       Checks if the door is opened.
     */
    bool isOpened();

    /**
     * @brief       Sets the status of the door.
     * @param o     Changes the value of private member _opened;
     */
    void openDoor(bool o);

private:
    QLineEdit *_log; //!< In-game log.
    bool _opened = false; //!< Door status. Depending on the status, the door pixmap is changed.
};

#endif // DOOR_H
