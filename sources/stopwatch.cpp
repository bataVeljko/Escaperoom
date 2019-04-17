#include <headers/stopwatch.h>

#define START_TIME (1000)

Stopwatch::Stopwatch(QTime startingTime)
    :_startingTime(startingTime)
{
    this->setFont(QFont("Arial", 20, QFont::Bold));
    this->setStyleSheet("QLabel { background-color : darkRed; color : yellow; }");
    this->move(STOPWATCH_X, STOPWATCH_Y);
    this->setAlignment(Qt::AlignCenter);
    this->setFixedSize(STOPWATCH_WIDTH, STOPWATCH_HEIGHT);
    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stopwatch::showElapsedTime);
    timer->start(START_TIME);

}

QString Stopwatch::showElapsedTime() {
    int diff = _startingTime.msecsTo(QTime::currentTime());
    QTime time = QTime(0,0,0).addMSecs(diff);
    QString text = time.toString("mm:ss");
    this->setText(text);
    return text;
};

QString Stopwatch::getTime(){
    return showElapsedTime();
}
