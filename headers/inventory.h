#ifndef INVENTORY_H
#define INVENTORY_H

#include "headers/ingameobjects.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

/**
 * @brief In-game static object used to stash Keys.
 */
class Inventory : public QGraphicsPixmapItem {

public:

    /**
     * @brief           Inventory constructor.
     * @param picture   Sets the pixmap of the Inventory.
     */
    Inventory(const QPixmap& picture);


    /**
     * @brief       Inventory destructor.
     */
    ~Inventory() = default;
};

#endif // INVENTORY_H
