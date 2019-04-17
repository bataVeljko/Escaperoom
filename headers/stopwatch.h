#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QTime>
#include <QGraphicsEffect>


#define STOPWATCH_PIXMAP_X (3)
#define STOPWATCH_PIXMAP_Y (3)
#define STOPWATCH_X (94)
#define STOPWATCH_Y (100)
#define STOPWATCH_WIDTH (100)
#define STOPWATCH_HEIGHT (30)

/**
 * @brief Timer for player
 */
class Stopwatch : public QLabel {
    Q_OBJECT
public:

    /**
     * @brief       Stopwatch constructor
     * @param startingTime     Starting time for timer, depends on current time and saved time inside user json file
     */
    Stopwatch(QTime startingTime);

    /**
     * @brief       Returns current time in stopwatch
     */
    QString getTime();

private slots:

    /**
     * @brief       Slot for showing elapsed time inside stopwatch
     */
    QString showElapsedTime();

private:
    QTime _startingTime; //!< Starting time for timer, depends on current time and saved time inside user json file
    QString time; //!< Text inside stopwatch object
};

#endif // STOPWATCH_H
