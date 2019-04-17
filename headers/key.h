#ifndef KEY_H
#define KEY_H

#include <QGraphicsPixmapItem>

/**
 * @brief Class for making universal key and level keys with ids and pictures
 */
class Key : public QGraphicsPixmapItem
{
public:

    /**
     * @brief       Key constructor
     * @param id    Id of key
     * @param bg    Picture of the key
     */
    Key(qint16 id, const QPixmap& bg);

    /**
     * @brief       Key destructor
     */
    ~Key() = default;

    /**
     * @brief       Function that return true if player solved level puzzle
     */
    bool shouldGetKey();

    /**
     * @brief       Setter for key
     * @param k     k equals true when player solve level puzzle
     */
    void setKeyAvailability(bool k);

private:
    qint16 _id; //!< Key's id
    bool _getKey = false; //!< Boolean value that tell us if user solved level puzzle
};

#endif // KEY_H
