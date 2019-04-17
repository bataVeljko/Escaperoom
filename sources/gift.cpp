#include "headers/gift.h"

Gift::Gift(const QPixmap& pic)
{
    setPixmap(pic);
}

void Gift::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //checking mouse click and player distance from gift
    if(event->button() == Qt::LeftButton && this->distance() < 100.0 ){
        //qDebug() << "You got universal key";
        getLog()->setText("You got universal key");
        getPlayer()->keyList.push_back(getUK());
        _gotKey = true;
    }
    getPlayer()->setFocus();
}

bool Gift::hasKey()
{
    return _gotKey;
}
