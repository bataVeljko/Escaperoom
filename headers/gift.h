#ifndef GIFT_H
#define GIFT_H

#include "ingameobjects.h"



/**
 * @brief Static colidable object.
 *
 * Contains the universal Key.
 */
class Gift : public InGameObjects {

public:

    /**
     * @brief           Gift constructor.
     * @param picture   Sets the pixmap of the Gift.
     */
    Gift(const QPixmap& picture);

    /**
     * @brief       Gift destructor.
     *              Destroys Gift object.
     */
    ~Gift() = default;

    /**
     * @brief           Overrides from InGameObjects.
     * @param event     An event which should handled.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief       Checks if the player has universal Key.
     */
    bool hasKey();

private:
    bool _gotKey = false; //!< Indicator of universal Key ownership.
};

#endif // GIFT_H
