#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "headers/game.h"

namespace Ui {
    class MainWindow;
}

/**
 * @brief Class that represents main menu
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    /**
     * @brief       Explicit MainWindow constructor
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief       MainWindow destructor
     */
    ~MainWindow();

    /**
     * @brief       Initialization of main menu interface
     */
    void initGUI();

    /**
     * @brief       Function that starts new game
     * @param name  User's nickname
     */
    void newGame(QString name);

    /**
     * @brief       Function that make json file for new user
     * @param name  User's nickname
     */
    void writeJson(const QString & name);

    /**
     * @brief       Function that read json file for existing user and sent data to game constructor
     * @param name  User's nickname
     */
    void readJsonAndStartGame(const QString & name);

    /**
     * @brief       Function that set all objects in main menu to invisible
     */
    void setAllInvisible();

private slots:

    /**
     * @brief       NewGame button clicked
     */
    void on_newGame_btn_clicked();

    /**
     * @brief       Exit button clicked
     */
    void on_exit_btn_clicked();

    /**
     * @brief       NewGameTextEdit text changed
     */
    void on_newGameTE_textChanged();

    /**
     * @brief       LoadGame button clicked
     */
    void on_loadGame_btn_clicked();

    /**
     * @brief       NewGameConfirm button clicked
     */
    void on_newGame_conf_btn_clicked();

    /**
     * @brief       LoadGameConfirm button clicked
     */
    void on_loadGame_conf_btn_clicked();

    /**
     * @brief       LoadGameTextEdit text changed
     */
    void on_loadGameTE_textChanged();

    /**
     * @brief       HighScore button clicked
     */
    void on_highscore_btn_clicked();

    /**
     * @brief       Tutorial button clicked
     */
    void on_tutorial_btn_clicked();

private:
    Ui::MainWindow *_ui; //!< MainWindow user interface
    Game *_game{}; //!< Variable for startting new game
};

#endif // MAINWINDOW_H
