#ifndef SPRITE_H
#define SPRITE_H
#include <QPixmap>

/**
 * @brief Sprite for player's moving
 */
class Sprite {
public:

    /**
     * @brief       Sprite constructor
     */
    Sprite();

    /**
     * @brief       Sprite destructor
     */
    ~Sprite();

    /**
     * @brief       Return next picture from sprite sheet
     */
    QPixmap nextSprite();

    /**
     * @brief       Set sprite sheet on begin
     */
    QPixmap startingSprite();

    /**
     * @brief               Add new sprite
     * @param spriteName    Name of current sprite
     */
    void addSprite(const QString & spriteName);

private:
    QVector<QPixmap> _spritesheet; //!< Sprite sheet of player's moving
    int _current = 0; //!< Current picture from sprite sheet
};

#endif // SPRITE_H
