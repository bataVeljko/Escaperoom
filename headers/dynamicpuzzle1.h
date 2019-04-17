#ifndef DYNAMICPUZZLE1_H
#define DYNAMICPUZZLE1_H

#include "headers/puzzle.h"

#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define SET_SOUND_LOOP (1)
#define MAX_NUM_OF_ITEMS (2)
#define FIRST_ISLAND (1)
#define SECOND_ISLAND (2)
#define POSITION_CORRECTION (20)
#define CLOSE_BTN_POSITION (1080)
//help for mousePressEvent function
enum ItemPosition{ island1, island2, boat };

namespace Coordinates {
    extern qint16 boatIsland1X;
    extern qint16 boatIsland1Y;
    extern qint16 boatIsland2X;
    extern qint16 boatIsland2Y;

    extern qint16 wolfIsland1X;
    extern qint16 wolfIsland1Y;
    extern qint16 wolfIsland2X;
    extern qint16 wolfIsland2Y;

    extern qint16 goatIsland1X;
    extern qint16 goatIsland1Y;
    extern qint16 goatIsland2X;
    extern qint16 goatIsland2Y;

    extern qint16 lettuceIsland1X;
    extern qint16 lettuceIsland1Y;
    extern qint16 lettuceIsland2X;
    extern qint16 lettuceIsland2Y;
}


/**
 * @brief Interactive puzzle.
 *
 * In this puzzle, you can click on objects and interact with them, unlike with StaticPuzzle class objects.
 */

class DynamicPuzzle1 : public Puzzle {

public:

    /**
     * @brief           DynamicPuzzle1 constructor.
     * @param parent    Parent object.
     * @param scene     Current scene.
     * @param cl        Current level.
     */
    DynamicPuzzle1(QGraphicsView *parent, QGraphicsScene *scene, qint16 cl);

    /**
     * @brief           Override from Puzzle
     * @param event     An event which should be handled.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsPixmapItem *_boat; //!< An item which represents a boat.
    QGraphicsPixmapItem *_goat; //!< An item which represents a goat.
    QGraphicsPixmapItem *_wolf; //!< An item which represents a wolf.
    QGraphicsPixmapItem *_lettuce; //!< An item which represents a lettuce.
    qint16 _numberOfItemsOnTheBoat = 1; //!< Current number of items on the boat.
    qint8 _boatIsland = 1; //!< Current island.
    ItemPosition _wolfPosition = island1; //!< Position in scene of a private member _wolf.
    ItemPosition _goatPosition = island1; //!< Position in scene of a private member _goat.
    ItemPosition _lettucePosition = island1; //!< Position in scene of a private member _lettuce.

    /**
     * @brief                   Checks if there's a constraint issue.
     * @param boatIslandNumber  Island ID number.
     */
    void checkForEating(qint16 boatIslandNumber);

    /**
     * @brief       Closes the puzzle.
     */
    void puzzleOver();

    /**
     * @brief       Checks if the player has solved the puzzle.
     */
    void checkForWinning();
};

#endif // DYNAMICPUZZLE1_H
