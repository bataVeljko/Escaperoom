#ifndef INVERTEDFLOOR_H
#define INVERTEDFLOOR_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>

/**
 * @brief In-game object that goes with level pictures and help us with collision
 */
class InvertedFloor : public QGraphicsPixmapItem {
public:

    /**
     * @brief       InvertedFloor constructor
     * @param bg    Picture of the inverted floor
     */
    InvertedFloor(const QPixmap& bg);

    /**
     * @brief       InvertedFloor destructor
     */
    ~InvertedFloor() = default;
};

#endif // FLOOR_H

