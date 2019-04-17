#ifndef GAME_HPP
#define GAME_HPP

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QJsonObject>
#include <QJsonDocument>
#include "headers/player.h"
#include "headers/gift.h"
#include "headers/door.h"
#include "headers/chest.hpp"
#include "headers/key.h"
#include "headers/invertedfloor.h"
#include "headers/inventory.h"
#include "headers/stopwatch.h"
#include "headers/help.h"
#include <QDebug>
#include <QLineEdit>
#include <QLabel>
#include <QSound>
#include <QSoundEffect>
#include <QPointer>


#define LOG_PIXMAP_X (0)
#define LOG_PIXMAP_Y (662)
#define LOG_WIDTH (470)
#define LOG_HEIGHT (40)
#define LOG_X (5)
#define LOG_Y (677)
#define SCORE_PIXMAP_X (995)
#define SCORE_PIXMAP_Y (3)
#define SCORE_WIDTH (100)
#define SCORE_HEIGHT (30)
#define SCORE_X (1090)
#define SCORE_Y (100)
#define QUIT_BUTTON_X (1070)
#define QUIT_BUTTON_Y (655)
#define UNIVERSAL_KEY_X (1175)
#define UNIVERSAL_KEY_Y (296)
#define SAVE_BUTTON_Y (585)
#define INGAME_BUTTON_X (1070)

namespace SceneMeasure {
    extern qint16 sceneWidth;
    extern qint16 sceneHeight;
}


/**
 * @brief Main class which is a scene where everything happens.
 */

class Game : public QGraphicsScene {

public:

    /**
     * @brief           Game constructor for the tutorial.
     * @param parent    Game parent.
     */
    Game(QGraphicsView *parent);

    /**
     * @brief           Game constructor for a new game.
     * @param parent    Game parent.
     * @param name      A name which user gives to the game which is used to track highscore.
     */
    Game(QGraphicsView *parent, QString name);

    /**
     * @brief           Game constructor which is used when loading a Game from savefile.
     * @param parent    Game parent.
     * @param name      A name which user gave to the game which is used to track highscore.
     * @param cl        Current level.
     * @param uk        Variable which checks if the player has universal Key or not.
     * @param ctime     Current time.
     * @param cscore    Current score.
     */
    Game(QGraphicsView *parent, QString name, qint16 cl, bool uk, QString ctime, QString cscore);

    /**
     * @brief       Game destructor. Destroys Game object.
     */
    ~Game() = default;

    /**
     * @brief       Function which initializes Game.
     * @param name  User name.
     */
    void start(QString name);

    /**
     * @brief       Function which deinitializes Game.
     */
    void quit();

    /**
     * @brief       Function which handles mouse events such as clicks on Door, Chest, etc.
     * @param event An event which should be handled.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief       Function which is used to not lose focus from the Player object.
     * @param event An event which should be handled.
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief       Player getter.
     */
    Player *getPlayer();

    /**
     * @brief       Function which adds a score to highscores.
     */
    void addToHighscore();

    /**
     * @brief       Function which checks if user started the tutorial or not.
     */
    void itIsTutorial();

    /**
     * @brief       Function which checks if user is in tutorial or not.
     */
    bool isTutorial();

    /**
     * @brief       Function which adds log widget to the scene.
     */
    void addLog();

    /**
     * @brief       Function which adds score widget to the scene.
     */
    void addScore();

    /**
     * @brief       Function which adds Stopwatch widget to the scene.
     */
    void addStopwatch();

private:
    QGraphicsView *_parent {};         //!< Game's parent.
    Player *_player {};                //!< Controllable object.
    Gift *_gift {};                    //!< Generous gift in shape of a Key. Universal key which opens every door.
    Door *_door {};                    //!< InGameObjects for which you need a Key to open it.
    Chest *_chest {};                  //!< InGameObjects which opens a Puzzle which when solved gives you a Key.
    Key *_universalKey {};             //!< Key which is in Gift.
    Key *_levelKey {};                 //!< Key which is in Chest.
    Inventory *_inventory {};          //!< Object which contains Keys.
    QLineEdit *_log {};                //!< Message log which informs you of events.
    QSound *_door_knock_sound = new QSound(QString(":/resources/sounds/knock_on_the_door.wav"));    //!< Door knock sound.
    QSound *_door_opening_sound = new QSound(QString(":/resources/sounds/door_opening.wav"));       //!< Door opening sound.
    QSound *_key_sound = new QSound(QString(":/resources/sounds/keys.wav"));                        //!< Colected Key sound.
    QSoundEffect *_background_music = new QSoundEffect();                                           //!< Soundtrack in game.
    QLabel *_score {};                 //!< Score in game. Calculated with some random function.
    QString _scoreText = "0";       //!< Score in game used for saving purpose.
    QTime _startingTime;            //!< Starting game time. We use time to calculate score.
    Stopwatch *_stopwatch {};          //!< Stopwatch for tracking in-game time.
    QPixmap _openChestPic;          //!< Pixmap used when Chest is opened.
    QPixmap _openDoorPic;           //!< Pixmap used when Door is opened.
    qint32 _openDoorXCoord {};         //!< Coordinate for Door which is changed due to different opened door and closed door Pixmaps.
    QGraphicsPixmapItem *_saveBtn {};  //!< Button which saves current state of the game.
    QGraphicsPixmapItem *_quitBtn {};  //!< Button which brings you back to main menu.
    bool _tutorial = false;         //!< Indicator if the player has started the tutorial.
    Help *_help {};                    //!< Help shown during tutorial.
    Help *_help_text {};               //!< Help shown during tutorial.
    QString _timeText = "00:00";    //!< Time in game used for saving purpose.
    bool _isScoreLoaded = false;    //!< Checking if the score is loaded or not.

    /**
     * @brief       Function which load levels from JSON files.
     */
    void loadLevel();
};

#endif // GAME_HPP
