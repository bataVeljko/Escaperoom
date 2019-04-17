#ifndef HELP_H
#define HELP_H

#include "ingameobjects.h"

/**
 * @brief Class used during a tutorial for navigation through the tutorial.
 */
class Help : public InGameObjects {

public:

    /**
     * @brief           Help constructor.
     * @param picture   Sets the pixmap of the Help.
     */
    Help(const QPixmap& picture);

    /**
     * @brief       Help destructor.
     *              Destroys Help object.
     */
    ~Help() = default;

    /**
     * @brief           Overrides from InGameObjects.
     * @param event     An event which should handled.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *);

    /**
     * @brief       Returns the current step of the tutorial.
     */
    qint16 currentStep();

    /**
     * @brief       Sets the next step of the tutorial.
     */
    void nextStep();

private:
    qint16 _step = 1; //!< Current step in the tutorial. Tutorial is divided in three steps.
};

#endif // HELP_H
