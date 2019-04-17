#include "headers/sprite.h"

Sprite::Sprite() = default;

Sprite::~Sprite() = default;

QPixmap Sprite::nextSprite(){
    _current = (_current + 1) % _spritesheet.size();
    return _spritesheet.at(_current);
};

QPixmap Sprite::startingSprite(){
    return _spritesheet.at(0);
}

void Sprite::addSprite(const QString & spriteName){
    _spritesheet.push_back(QPixmap(spriteName));
};
