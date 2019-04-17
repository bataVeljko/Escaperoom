#include "headers/staticpuzzle.h"
#include<QSound>

#define CLOSE_BTN_X_POS (1080)
#define CLOSE_BTN_Y_POS (0)
#define ANS_WIDTH (200)
#define ANS_HEIGHT (50)
#define ANS_WIDTH_L2 (200)
#define ANS_HEIGHT_L2 (57)

StaticPuzzle::StaticPuzzle(QGraphicsView *parent, QGraphicsScene *scene, qint16 cl) :
    Puzzle(parent, scene, cl)
{
    loadPuzzle();

    //adding close button item to the scene
    _closeBtn = new QGraphicsPixmapItem(QPixmap(":/resources/buttons/close_btn.png"));
    _closeBtn->moveBy(CLOSE_BTN_X_POS, CLOSE_BTN_Y_POS);
    _closeBtn->setFlag(QGraphicsItem::ItemIsFocusable);
    this->addItem(_closeBtn);

    //adding accept button
    _accBtn = new QGraphicsPixmapItem(QPixmap(":/resources/buttons/accept_btn.png"));
    _accBtn->setFlag(QGraphicsItem::ItemIsFocusable);
    this->addItem(_accBtn);
}

void StaticPuzzle::loadPuzzle(){
    QFile qf;
    //reading json file, depends on level
    QString levelPuzzleJson = ":/resources/puzzles_json/puzzle_" + QString::number(getCl()) + ".json";
    qf.setFileName(levelPuzzleJson);
    qDebug() << levelPuzzleJson;
    qf.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument qjd = QJsonDocument::fromJson(qf.readAll());
    qf.close();
    //setting background picture
    setBackgroundBrush(QImage(qjd["background"].toString()));
    setSceneRect(0, 0, 1280, 720);

    //getting array with answers
    QJsonArray answersJsonObject = qjd["answers"].toArray();
    QJsonArray answerPositionX = qjd["aPositionX"].toArray();
    QJsonArray answerPositionY = qjd["aPositionY"].toArray();

    //number of answers
    _ansNum = answersJsonObject.size();
    //setting two vectors to right size
    _answers.resize(_ansNum);
    _rightAnswers.resize(_ansNum);
    //adding a widget with layout, so we can place text fields wherever we'd like
    auto *answerWidget = new QWidget;
    answerWidget->setContentsMargins(0,0,0,0);
    auto *answerLayout = new QVBoxLayout;
    answerLayout->setMargin(0);
    answerLayout->setSpacing(1);
    answerWidget->move(answerPositionX.at(0).toString().toInt(), answerPositionY.at(0).toString().toInt());
    for(int i = 0; i < _ansNum; i++){
        //making _ansNum TextEdit fields
        _answers[i] = new QTextEdit();
        _answers[i]->move(answerPositionX.at(i).toString().toInt(), answerPositionY.at(i).toString().toInt());
        // just a simple example of how should we handle multiple answers, depending on the current puzzle
        if(getCl() == 2) {
            _answers[i]->setFixedSize(ANS_WIDTH_L2, ANS_HEIGHT_L2);
            _answers[i]->setStyleSheet("border-bottom:1px solid green; background:black; color:green");
            _answers[i]->setFont(QFont(QFont("Arial", 15, QFont::Bold)));
            _answers[i]->setAlignment(Qt::AlignCenter);
        }
        else{
            _answers[i]->setFixedSize(ANS_WIDTH,ANS_HEIGHT);
        }
        _answers[i]->setPlaceholderText("Double click! Answer here");
        answerLayout->addWidget(_answers[i]);
        //putting right answers in our vector
        _rightAnswers[i] = new QString(answersJsonObject.at(i).toString());
    }

    answerWidget->setLayout(answerLayout);
    addWidget(answerWidget);
}

void StaticPuzzle::mousePressEvent(QGraphicsSceneMouseEvent *){
    if(_closeBtn->isUnderMouse()){
        //delete current scene
        this->deleteLater();
        //raise old scene
        getView()->setScene(getScene());
    }
    if(_accBtn->isUnderMouse()){
        //if answers in EditText fields are correct, user will get level key
        bool correct = true;
        for(int i = 0; i < _ansNum; i++){
            if(_answers.at(i)->toPlainText().toLower().trimmed() != _rightAnswers.at(i)){
                correct = false;
                break;
            }
        }
        if(correct){
            getLK()->setKeyAvailability(true);
            //qDebug() << "Chest unlocked, click to get key";
            getLog()->setText("Chest unlocked, click to get key");
            //delete current scene
            this->deleteLater();
            //raise old scene
            getView()->setScene(getScene());
        }
        //otherwise, his/her answer will be deleted, and message will occurre
        else{
            _fail_sound->setLoops(1);
            _fail_sound->play();
            for(int i = 0; i < _ansNum; i++){
                //only incorrect answers will be deleted
                if(_answers[i]->toPlainText() != _rightAnswers[i]){
                    _answers[i]->setText("");
                    _answers[i]->setPlaceholderText("Wrong answer, try again");
                }
            }
        }
    }
}
