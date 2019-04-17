#include "headers/game.h"

#define DUMMY_X_POS (25)
#define DUMMY_Y_POS (128)

namespace SceneMeasure {
    qint16 sceneWidth = 1280;
    qint16 sceneHeight = 720;
}

static qint16 endGame = 6;

//This constructor is only being called when it's a tutorial, because player name is not being set
Game::Game(QGraphicsView *parent) :
    _parent(parent)
{
    _player = new Player("");
    itIsTutorial();
    addItem(_player);
    addItem(_player->getDummy());
    //qDebug() << "Tutorial";
    //Universal key
    _universalKey = new Key(0, QPixmap(":/resources/inventory/universal_key.png"));
    //Quit button
    _quitBtn = new QGraphicsPixmapItem(QPixmap(":/resources/buttons/exit_btn.png"));
    _quitBtn->setFlag(QGraphicsItem::ItemIsFocusable);
    _quitBtn->setPos(QUIT_BUTTON_X, QUIT_BUTTON_Y);
    addItem(_quitBtn);
    loadLevel();
}

Game::Game(QGraphicsView *parent, QString name) :
           _parent(parent)
{
    start(std::move(name));
    loadLevel();
}

Game::Game(QGraphicsView *parent, QString name, qint16 cl, bool uk, QString ctime, QString cscore) :
            _parent(parent), _scoreText(std::move(cscore)), _timeText(std::move(ctime))
{
    start(std::move(name));
    _player->setCurrentLevel(cl);
    if(uk){
        _player->keyList.push_back(_universalKey);
        _universalKey->setPos(UNIVERSAL_KEY_X, UNIVERSAL_KEY_Y);
        _universalKey->setZValue(5);
        this->addItem(_universalKey);
    }
    _isScoreLoaded = true;
    loadLevel();
}

void Game::start(QString name) {
    _player = new Player(std::move(name));
    addItem(_player);
    addItem(_player->getDummy());
    // Universal key
    _universalKey = new Key(0, QPixmap(":/resources/inventory/universal_key.png"));
    // Initializing time
    qint32 cMins = _timeText.split(':').at(0).toInt();
    qint32 cSecs = _timeText.split(':').at(1).toInt() + cMins*60;
    _startingTime = QTime::currentTime().addMSecs(-cSecs*1000);

    //Save button
    _saveBtn = new QGraphicsPixmapItem(QPixmap(":/resources/buttons/save_btn.png"));
    _saveBtn->setFlag(QGraphicsItem::ItemIsFocusable);
    _saveBtn->setPos(INGAME_BUTTON_X, SAVE_BUTTON_Y);
    addItem(_saveBtn);
    //Quit button
    _quitBtn = new QGraphicsPixmapItem(QPixmap(":/resources/buttons/exit_btn.png"));
    _quitBtn->setFlag(QGraphicsItem::ItemIsFocusable);
    _quitBtn->setPos(INGAME_BUTTON_X, QUIT_BUTTON_Y);
    addItem(_quitBtn);
}

void Game::loadLevel(){

    // Setting background music
    _background_music->setSource(QUrl("qrc:/resources/sounds/background.wav"));
    _background_music->setLoopCount(QSoundEffect::Infinite);
    _background_music->setVolume(0.4);
    _background_music->play();

    QFile qf;
    //reading json file, depends on level
    QString levelJson = ":/resources/levels_json/level_" + QString::number(_player->getCurrentLevel()) + ".json";
    qf.setFileName(levelJson);
    qDebug() << levelJson;
    qf.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument qjd = QJsonDocument::fromJson(qf.readAll());
    qf.close();

    //background of scene
    setBackgroundBrush(QImage(qjd["background"].toString()));

    //Key for current level
    _levelKey = new Key(_player->getCurrentLevel(), QPixmap(":/resources/inventory/level_key.png"));

    // Adding log
    addLog();
    // Adding stopwatch
    addStopwatch();

    qDebug() << _stopwatch->getTime();
    _timeText = _stopwatch->getTime();
    // Adding score
    addScore();
    // We may lose precision, but it doesn't really matter that much.
    _player->setPos(SceneMeasure::sceneWidth/2.0, SceneMeasure::sceneHeight/2.0);
    //setting player ahead of gift, because first we add player to the scene, then gift, so gift's z-value is lower than player's
    _player->setZValue(5);
    //enabling keyboard inputs
    _player->setFlag(QGraphicsItem::ItemIsFocusable);
    //focusing item, so it can catch keyboard inputs
    _player->setFocus();

    //setting position for player's dummy object and adding (25,128), so that dummy will be by his legs
    //We may lose precision, but it doesn't really matter that much.
    _player->getDummy()->setPos(SceneMeasure::sceneWidth/2.0+DUMMY_X_POS, SceneMeasure::sceneHeight/2.0+DUMMY_Y_POS);

    //adding object so we can trace player not to got over edges of room
    _player->setInvertedFloor(new InvertedFloor(QPixmap(qjd["floor"].toString())));
    addItem(_player->getInvertedFloor());
    QJsonObject giftJsonObject = qjd["gift"].toObject();
    if(giftJsonObject["on_scene"].toBool()){
        _gift = new Gift(QPixmap(giftJsonObject["pixmap"].toString()));
        _gift->setPos(giftJsonObject["x_pos"].toInt(), giftJsonObject["y_pos"].toInt());
        _gift->setFlag(QGraphicsItem::ItemIsFocusable);
        _gift->setLog(_log);
        _gift->setPlayer(_player);
        _gift->setUK(_universalKey);
        addItem(_gift);
    }

    QJsonObject doorJsonObject = qjd["door"].toObject();
    if(doorJsonObject["on_scene"].toBool()){
        _door = new Door(QPixmap(doorJsonObject["pixmapClose"].toString()));
        _openDoorPic = QPixmap(doorJsonObject["pixmapOpen"].toString());
        _openDoorXCoord = doorJsonObject["x_pos_open"].toInt();
        _door->setPos(doorJsonObject["x_pos_close"].toInt(), doorJsonObject["y_pos_close"].toInt());
        _door->setFlag(QGraphicsItem::ItemIsFocusable);
        _door->setLog(_log);
        _door->setPlayer(_player);
        _door->setUK(_universalKey);
        _door->setLK(_levelKey);
        addItem(_door);
    }

    QJsonObject chestJsonObject = qjd["chest"].toObject();
    if(chestJsonObject["on_scene"].toBool()){
        _chest = new Chest(QPixmap(chestJsonObject["pixmapClose"].toString()));
        _openChestPic = QPixmap(chestJsonObject["pixmapOpen"].toString());
        _chest->setPos(chestJsonObject["x_pos"].toInt(), chestJsonObject["y_pos"].toInt());
        _chest->setFlag(QGraphicsItem::ItemIsFocusable);
        _chest->setLog(_log);
        _chest->setPlayer(_player);
        _chest->setLK(_levelKey);
         addItem(_chest);
    }

    QJsonObject inventoryJsonObject = qjd["inventory"].toObject();
    if(inventoryJsonObject["on_scene"].toBool()){
        _inventory = new Inventory(QPixmap(inventoryJsonObject["pixmap"].toString()));
        _inventory->setPos(inventoryJsonObject["x_pos"].toInt(), inventoryJsonObject["y_pos"].toInt());
        addItem(_inventory);
    }

    //adding text explaining how to play this game.
    if(isTutorial()){
        _help = new Help(QPixmap(":/resources/tutorijal/pop1.png"));
        _help->setPos(500, 5);
        _help->setZValue(5);
        addItem(_help);

        _help_text = new Help(QPixmap(":/resources/tutorijal/text1.png"));
        _help_text->setPos(5, 415);
        _help_text->setZValue(5);
        addItem(_help_text);
        //qDebug() << "Tutorijal je";
    }else{
        //qDebug() << "Nije tutorijal";
    }

    //setting scene, setting origin in top, left corner, size to 1280x720
    setSceneRect(0, 0, SceneMeasure::sceneWidth, SceneMeasure::sceneHeight);
    _parent->setFrameStyle(0);
}

void Game::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //gift only exist on first level
    //if user clicks on gift, keyPressEvent function from gift class will be called
    //if player already has universal key, user won't be able to 'open' the gift again
    if(_player->getCurrentLevel()==1 && _gift->isUnderMouse() && !_gift->hasKey()){
        _gift->mousePressEvent(event);
        if(_gift->hasKey()){
            _key_sound->setLoops(1);
            _key_sound->play();
            _universalKey->setPos(1175, 296);
            _universalKey->setZValue(5);
            this->addItem(_universalKey);

            //moving to the next step in case of a tutorial
            if(isTutorial() && _help->currentStep() == 1){
                _help->setPixmap(QPixmap(":/resources/tutorijal/pop2.png"));
                _help->nextStep();
                _help_text->setPixmap(QPixmap(":/resources/tutorijal/text2.png"));
                _help_text->nextStep();
            }
        }
    }
    //If user clicks on door, keyPressEvent function from door class will be called
    else if(_door->isUnderMouse()){
        //if door hasn't been opened yet, mousePressEvent from door will be called
        if(_door->pixmap() == QPixmap(":/resources/doors/close_door.png")){

            //In tutorial game, steps cannot be skipped in order to finish faster!!
            if(isTutorial() && _help->currentStep() != 3){

            }else {
                _door->mousePressEvent(event, _openDoorPic, _openDoorXCoord);
            }
            //sound of door opening or knocking, as a reminder that a key is required in order to open the door
            if(_door->isOpened()){
                _door_opening_sound->setLoops(1);
                _door_opening_sound->play();
            }else{
                _door_knock_sound->setLoops(1);
                _door_knock_sound->play();
            }
        }
        //if door has already been opened, clicking on the door will get you to next level
        else{

            //if we are in tutorial, game is over
            if(isTutorial() && _help->currentStep() == 3){
                quit();
            }
            else {
                _player->setCurrentLevel(_player->getCurrentLevel()+1);

                if(_player->getCurrentLevel() >= endGame){
                    qDebug() << "********************************************\r\n"
                                "*****        Congratulations           *****\r\n"
                                "********************************************";

                    // score is added on levelLoad
                    //after finishing game, username and score are added to highscore file                    
                    _scoreText = QString::number((_scoreText.toInt()+100));
                    addToHighscore();
                    quit();
                }
                else{

                    //deleting every graphics item from the scene, except the player, because he won't be changed
                    for(QGraphicsItem *item: this->items()){
                        if(item != _player && item != _player->getDummy() && item != _universalKey && item != _saveBtn && item != _quitBtn)
                            delete item;
                    }

                    //loading next level
                    loadLevel();
                }
            }
        }
    }
    //If user clicks on chest, chest hasn't been opened yet and user hasn't solved the puzzle yet, keyPressEvent function from chest class will be called
    else if(_chest->isUnderMouse() && !_chest->isOpened() && !_levelKey->shouldGetKey()){

        //in a tutorial, the chest cannot be opened in the wrong step
        if(isTutorial() && _help->currentStep() != 2){

        } else{
            _chest->mousePressEvent(event, this->_parent);
        }
    }
    //If user click on chest, chest hasn't been opened yet and the user solved the puzzle, levelKey will be added to user's list and chest will open
    else if(_chest->isUnderMouse() && !_chest->isOpened() && _levelKey->shouldGetKey()){
        _chest->openChest(true);
        _player->keyList.append(_levelKey);
        _key_sound->setLoops(1);
        _key_sound->play();
        //qDebug() << "You got level key";
        _log->setText("You got level key");
        _levelKey->setPos(1175, 407);
        addItem(_levelKey);
        _chest->setPixmap(_openChestPic);

        //moving to the final step if it is a tutorial game
        if(isTutorial() && _help->currentStep() == 2){
            _help->setPixmap(QPixmap(":/resources/tutorijal/pop3.png"));
            _help->nextStep();
            _help_text->setPixmap(QPixmap(":/resources/tutorijal/text3.png"));
            _help_text->nextStep();
        }
    }
    else if(!isTutorial() && _saveBtn->isUnderMouse()){
        qDebug() << "SAVE";
        QFile qf("../RS009-escaperoom/resources/username_json/" + _player->getUsername() + ".json");
        qf.open(QIODevice::WriteOnly);
        QJsonDocument qjd;
        QJsonObject qjo;
        qjo.insert("CurrentLevel", QJsonValue(_player->getCurrentLevel()));
        qjo.insert("UniversalKey", QJsonValue(_player->keyList.contains(_universalKey)));
        qjo.insert("Time", QJsonValue(_stopwatch->getTime()));
        qjo.insert("Score", QJsonValue(_scoreText));
        qjd.setObject(qjo);
        qf.write(qjd.toJson());
        qf.close();
    }
    else if(_quitBtn->isUnderMouse()){
        qDebug() << "QUIT";
        quit();
    }
    else{
        //qDebug() << "Click!";
    }
}

void Game::quit() {
    _parent->lower();
    for(QGraphicsItem *item: this->items()){
        delete item;
    }
    _background_music->stop();
    this->deleteLater();

    _parent->setStyleSheet(
                "background-image:    url(\":/resources/background.png\"); "
                "background-position: center;" );
}

//if user press double click somewhere on the scene, player will stay in focus
void Game::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    if(event->KeyPress)
        _player->setFocus();
}

Player *Game::getPlayer() {
    return _player;
}

//adding score from current user to highscore file
void Game::addToHighscore() {
    QFile qf("../RS009-escaperoom/resources/highscores.txt");
    if(qf.open(QIODevice::Append)){
        QTextStream out(&qf);
        out << '\n' << _player->getUsername() << " " << _scoreText;
    }
    //time on the end of the game
    _timeText = _stopwatch->getTime();
    qDebug() << _timeText;
    qf.close();
}

void Game::itIsTutorial(){
    _tutorial = true;
}

bool Game::isTutorial(){
    return _tutorial;
}

void Game::addLog(){
    //Log for the user
    QGraphicsPixmapItem *logPixmap = new QGraphicsPixmapItem(QPixmap(":/resources/gui/log.png"));
    logPixmap->setPos(LOG_PIXMAP_X, LOG_PIXMAP_Y);
    addItem(logPixmap);
    _log = new QLineEdit();
    //frame size and style
    _log->setFixedSize(LOG_WIDTH, LOG_HEIGHT);
    _log->setAlignment(Qt::AlignCenter);
    _log->setFont(QFont("Arial", 17, QFont::Bold));
    _log->setStyleSheet("background-color : darkRed; color : yellow; border:none");

    //frame position
    _log->move(LOG_X, LOG_Y);
    //invisible frame
    addWidget(_log);
    //_log->setText(_player->getUsername());


}
void Game::addScore(){
    QGraphicsPixmapItem *scorePixmap = new QGraphicsPixmapItem(QPixmap(":/resources/gui/score.png"));
    scorePixmap->setPos(SCORE_PIXMAP_X, SCORE_PIXMAP_Y);
    addItem(scorePixmap);
    _score = new QLabel();
    _score->setFont(QFont("Arial", 20, QFont::Bold));
    _score->setStyleSheet("QLabel { background-color : darkRed; color : yellow; }");
    _score->move(SCORE_X, SCORE_Y);
    _score->setAlignment(Qt::AlignCenter);
    _score->setFixedSize(SCORE_WIDTH, SCORE_HEIGHT);
    // Getting minutes and seconds from the time spent in game so we could do something with it to change score.
    int mins = _timeText.split(':').at(0).trimmed().toInt();
    int secs = _timeText.split(':').at(1).trimmed().toInt();
    if(_isScoreLoaded) {
        _isScoreLoaded = false;
    }
    // Random function just to give some variety to the score.
    else {
        _scoreText = QString::number((_scoreText.toInt())+((_player->getCurrentLevel()-1)*100/(mins*10+secs/6+1)));
    }
    _score->setText(_scoreText);
    addWidget(_score);
    qDebug() << _score->text();
}

void Game::addStopwatch(){
    // Simple setting up and then adding the stopwatch.
    QGraphicsPixmapItem *stopwatchPixmap = new QGraphicsPixmapItem(QPixmap(":/resources/gui/time.png"));
    stopwatchPixmap->setPos(STOPWATCH_PIXMAP_X, STOPWATCH_PIXMAP_Y);
    addItem(stopwatchPixmap);
    _stopwatch = new Stopwatch(_startingTime);
    addWidget(_stopwatch);
}
