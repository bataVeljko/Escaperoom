#include "headers/key.h"

Key::Key(qint16 id, const QPixmap& bg) :
    _id(id)
{
    setPixmap(bg);
}

bool Key::shouldGetKey() {
    return _getKey;
}

void Key::setKeyAvailability(bool k) {
    _getKey = k;
}
