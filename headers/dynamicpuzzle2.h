#ifndef DYNAMICPUZZLE2_H
#define DYNAMICPUZZLE2_H

#include "headers/puzzle.h"

#define NUM_OF_ITERS (100)
#define NUM_OF_ROWS (4)
#define NUM_OF_COLS (4)
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define MOVE_VAL (151)
#define STARTING_X (337)
#define STARTING_Y (58)
#define EMPTY_TILE (15)

/**
* @brief Interactive puzzle.
*
* In this puzzle, you can click on objects and interact with them, unlike with StaticPuzzle class objects.
*/
class DynamicPuzzle2 : public Puzzle {

public:

    /**
     * @brief           DynamicPuzzle1 constructor.
     * @param parent    Parent object.
     * @param scene     Current scene.
     * @param cl        Current level.
     */
    DynamicPuzzle2(QGraphicsView *parent, QGraphicsScene *scene, qint16 cl);

    /**
     * @brief           Override from Puzzle
     * @param event     An event which should be handled.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:

    /**
     * @brief       Initializing puzzle. Randomizes tiles with swaping tiles in loop.
     */
    void initializePuzzle();

    /**
     * @brief       Checking if the player has solved the puzzle.
     */
    void checkResult();

    /**
     * @brief               Function which puzzle swaps tiles.
     * @param position      Current position.
     * @param nextPosition  Next position.
     */
    void swapTiles(int& position, int nextPosition);

    /**
     * @brief       Closes the puzzle.
     */
    void puzzleOver();

    QVector<QPair<QGraphicsPixmapItem*, qint16>> _tiles; //!< Vector of tiles which construct the puzzle.
};
#endif // DYNAMICPUZZLE2_H
