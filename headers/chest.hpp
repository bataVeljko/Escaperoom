#ifndef CHEST_HPP
#define CHEST_HPP

#include <QGraphicsView>
#include "headers/ingameobjects.h"
#include "headers/puzzle.h"
#include "headers/staticpuzzle.h"
#include "headers/dynamicpuzzle1.h"
#include "headers/dynamicpuzzle2.h"


#define DYNAMIC_LEVEL_1 (4)
#define DYNAMIC_LEVEL_2 (5)
#define CHECK_DISTANCE (100)

/**Static collidable object.
 * @brief
 *
 * This is an InGameObjects which contains key for the level's door.
 * It is static, meaning that it doesn't change it's position during game.
 */
class Chest : public InGameObjects {

public:
    /**
     * @brief           Chest constructor.
     * @param picture   Sets the pixmap of the chest.
     */
    Chest(const QPixmap& picture);
    /**
     * @brief           Chest destructor.
     *                  Destroys Chest object.
     */
    ~Chest() = default;
    /**
     * @brief       Overrides from InGameObjects.
     * @param event An event which should handled.
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief       Detects if the object is mouse clicked.
     * @param event An event which shoudl be handled.
     * @param *     We have to add main view as an argument, so we can swap scenes between puzzles and game.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event, QGraphicsView *);

    /**
     * @brief       Checks if chest is opened.
     */
    bool isOpened();

    /**
     * @brief       Sets the status of chest.
     * @param o     Changes value of private member _opened.
     */
    void openChest(bool o);

private:
    bool _opened = false; //!< Checks if the player has solved the puzzle and changes the pixmap.
};

#endif // CHEST_HPP
