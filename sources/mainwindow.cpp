#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    initGUI();
}

MainWindow::~MainWindow(){
    delete _ui;
}


void MainWindow::initGUI(){

    _ui->display->setStyleSheet(
             "background-image:    url(\":/resources/background.png\"); "
             "background-position: center;" );

    QPixmap exitPixmap(":/resources/gui/quit.png");
    _ui->exit_btn->setStyleSheet("border: none;");
    _ui->exit_btn->setIcon(exitPixmap);
    _ui->exit_btn->setIconSize(exitPixmap.rect().size());

    QPixmap newGamePixmap(":/resources/gui/new_game.png");
    _ui->newGame_btn->setStyleSheet("border: none;");
    _ui->newGame_btn->setIcon(newGamePixmap);
    _ui->newGame_btn->setIconSize(newGamePixmap.rect().size());
    _ui->newGameTE->setFixedSize(newGamePixmap.rect().size());

    QPixmap loadGamePixmap(":/resources/gui/load_game.png");
    _ui->loadGame_btn->setStyleSheet("border: none;");
    _ui->loadGame_btn->setIcon(loadGamePixmap);
    _ui->loadGame_btn->setIconSize(loadGamePixmap.rect().size());
    _ui->loadGameTE->setFixedSize(loadGamePixmap.rect().size());

    QPixmap tutorialPixmap(":/resources/gui/tutorial.png");
    _ui->tutorial_btn->setStyleSheet("border: none;");
    _ui->tutorial_btn->setIcon(tutorialPixmap);
    _ui->tutorial_btn->setIconSize(tutorialPixmap.rect().size());

    QPixmap highscorePixmap(":/resources/gui/highscore.png");
    _ui->highscore_btn->setStyleSheet("border: none;");
    _ui->highscore_btn->setIcon(highscorePixmap);
    _ui->highscore_btn->setIconSize(highscorePixmap.rect().size());

    QPixmap confirmPixmap(":/resources/buttons/accept_btn.png");
    _ui->loadGame_conf_btn->setStyleSheet("border: none;");
    _ui->loadGame_conf_btn->setIcon(confirmPixmap);
    _ui->loadGame_conf_btn->setIconSize(confirmPixmap.rect().size());

    _ui->newGame_conf_btn->setStyleSheet("border: none;");
    _ui->newGame_conf_btn->setIcon(confirmPixmap);
    _ui->newGame_conf_btn->setIconSize(confirmPixmap.rect().size());


    _ui->highscore_frame->setStyleSheet("border:none; background-image:url(':/resources/gui/highscore_list.png');");
    _ui->highscore_frame->setVisible(false);

    _ui->highscoreList->setStyleSheet("border:none;background-image:url(:/resources/gui/highscore_list_widget.png);");
    _ui->highscoreList->setVisible(false);

}

//starting new game
void MainWindow::newGame(QString name) {
    //making new game
    _game = new Game(_ui->display, std::move(name));
    //setting scene
    _ui->display->setScene(_game);
    //setting game scene to be main scene
    _ui->display->raise();
    //setting focus on game scene
    _ui->display->setFocus();
}

//setting textEdit field visible, so user can enter his/her username
void MainWindow::on_newGame_btn_clicked() {
    setAllInvisible();
    _ui->newGameTE->setVisible(true);
    _ui->newGameTE->setEnabled(true);
    _ui->newGame_conf_btn->setVisible(true);

}

//if lenght of username is > 0, user can confirm that username
void MainWindow::on_newGameTE_textChanged() {
    if(_ui->newGameTE->toPlainText().size() > 0 )
        _ui->newGame_conf_btn->setEnabled(true);
    else
        _ui->newGame_conf_btn->setEnabled(false);
}

//checking is username alredy exist and if doesn't create new json file and start game,
//otherwise ask user if he/she want to erase old data and start game all over again
void MainWindow::on_newGame_conf_btn_clicked() {
    QString username = _ui->newGameTE->toPlainText();
    QFile qf("../RS009-escaperoom/resources/username_json/" + username + ".json");

    if(qf.exists()){
        qint32 answer = QInputDialog::getInt(this, "Korisnik vec postoji", "Ako zelite da prebriste podatke, unesite 1");
        if(answer == 1){

            //removing background before starting the game
            _ui->display->setStyleSheet("focus { background:white; }");

            writeJson(username);
            newGame(username);
            _ui->newGameTE->clear();
            setAllInvisible();
        }
    }
    else{

        //removing background before starting the game
        _ui->display->setStyleSheet("focus { background:white; }");

        writeJson(username);
        newGame(username);
        _ui->newGameTE->clear();
        setAllInvisible();
    }
}

//make json file for new user or rewrite data for old one
void MainWindow::writeJson(const QString & name) {
    QFile qf("../RS009-escaperoom/resources/username_json/" + name + ".json");
    if(qf.open(QIODevice::WriteOnly)){
        QJsonDocument qjd;
        QJsonObject qjo;
        qjo.insert("CurrentLevel", QJsonValue(1));
        qjo.insert("UniversalKey", QJsonValue(false));
        qjo.insert("Time", QJsonValue("00:00"));
        qjo.insert("Score", QJsonValue("0"));
        qjd.setObject(qjo);
        qf.write(qjd.toJson());
        qf.close();
    }
}

//load old user's data from json and start game where he/she left off
void MainWindow::readJsonAndStartGame(const QString & name) {
    QFile qf("../RS009-escaperoom/resources/username_json/" + name + ".json");
    if(qf.open(QIODevice::ReadOnly)){
        QJsonDocument qjd = QJsonDocument::fromJson(qf.readAll());
        qf.close();
        qint32 currLevel = qjd["CurrentLevel"].toInt();
        bool doesHaveUniversalKey = qjd["UniversalKey"].toBool();
        QString currentTime = qjd["Time"].toString();
        QString currentScore = qjd["Score"].toString();

        //making new game
        _game = new Game(_ui->display, name, qint16(currLevel), doesHaveUniversalKey, currentTime, currentScore);
        //_game.get()->getPlayer()->setUsername(" ");
        //setting scene
        _ui->display->setScene(_game);
        //setting game scene to be main scene
        _ui->display->raise();
        //setting focus on game scene
        _ui->display->setFocus();
    }
}

//setting textEdit field visible, so user can enter his/her existing username
void MainWindow::on_loadGame_btn_clicked() {
    setAllInvisible();
    _ui->loadGameTE->setVisible(true);
    _ui->loadGameTE->setEnabled(true);
    _ui->loadGame_conf_btn->setVisible(true);
}

//if lenght of username is > 0, user can confirm that username
void MainWindow::on_loadGameTE_textChanged() {
    if(_ui->loadGameTE->toPlainText().size() > 0 )
        _ui->loadGame_conf_btn->setEnabled(true);
    else
        _ui->loadGame_conf_btn->setEnabled(false);
}

//checking is username alredy exist and if does loas json file and continue game
void MainWindow::on_loadGame_conf_btn_clicked() {
    QString username = _ui->loadGameTE->toPlainText();
    QFile qf("../RS009-escaperoom/resources/username_json/" + username + ".json");

    if(qf.exists()){

        //removing background before starting the game
        _ui->display->setStyleSheet("focus { background:white; }");

        setAllInvisible();
        readJsonAndStartGame(username);
        _ui->loadGameTE->clear();
    }
    else{
        _ui->loadGameTE->clear();
        _ui->loadGameTE->setPlaceholderText("Username dosen't exist");
    }
}

//read highscores txt file, sort all data by score and write it in list on left side
void MainWindow::on_highscore_btn_clicked() {
    _ui->highscoreList->clear();
    setAllInvisible();
    _ui->highscoreList->setVisible(true);
    _ui->highscore_frame->setVisible(true);
    QFile qf("../RS009-escaperoom/resources/highscores.txt");
    QString line;
    if(qf.open(QIODevice::ReadOnly)){
        QVector<QPair<QString, qint32>> players;
        while((line = qf.readLine()) != nullptr){
            if(line.trimmed().size() == 0) continue;
            QStringList reci = line.split(' ');
            QPair<QString, qint32> onePlayer(reci.at(0).trimmed(),
                                             reci.at(1).trimmed().toInt());
            players.push_back(onePlayer);
        }
        std::sort(std::begin(players), std::end(players),
                  [](const QPair<QString, qint32> &first, const QPair<QString, qint32> &second) {return first.second > second.second;});
        //qDebug() << players.size();
        for(const auto & player: players) {
             QListWidgetItem* list_widget_item = new QListWidgetItem(player.first + "\t" + QString::number(player.second));
             list_widget_item->setTextAlignment(Qt::AlignCenter);
             list_widget_item->setFont(QFont("Arial", 13, QFont::Normal));
             list_widget_item->setTextColor("yellow");
             _ui->highscoreList->addItem(list_widget_item);
        }
        qf.close();
    }
}

void MainWindow::on_exit_btn_clicked(){
    this->close();
}

void MainWindow::on_tutorial_btn_clicked()
{
    _ui->display->setStyleSheet("focus { background:white; }");
    setAllInvisible();
    //making a new game, but we are not setting a player name.
    _game = new Game(_ui->display);

    //setting scene
    _ui->display->setScene(_game);
    //setting game scene to be main scene
    _ui->display->raise();
    //setting focus on game scene
    _ui->display->setFocus();
}

void MainWindow::setAllInvisible(){
    _ui->loadGameTE->setVisible(false);
    _ui->newGameTE->setVisible(false);
    _ui->newGame_conf_btn->setVisible(false);
    _ui->loadGame_conf_btn->setVisible(false);
    _ui->highscoreList->setVisible(false);
    _ui->highscore_frame->setVisible(false);
}
