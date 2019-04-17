#ifndef STATICPUZZLE_H
#define STATICPUZZLE_H

#include <QGraphicsRectItem>
#include <QTextEdit>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "headers/puzzle.h"
#include <QSound>

/**
 * @brief Class for setting static puzzle's
 */
class StaticPuzzle : public Puzzle {
public:

    /**
     * @brief           StaticPuzzle constuctor
     * @param parent    Main view
     * @param scene     Current scene
     * @param cl        Current level
     */
    StaticPuzzle(QGraphicsView *parent, QGraphicsScene *scene, qint16 cl);

    /**
     * @brief           Mouse press event inside puzzle
     * @param event     Represent event that trigered this function
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsPixmapItem *_accBtn; //!< Accept button
    QVector<QTextEdit*> _answers; //!< Vector of TextEdit fields where user should eneter his/her answers
    qint32 _ansNum{}; //!< Number of answers
    QVector<QString*> _rightAnswers; //!< Vector of correct answers
    QVector<QString*> _answerPositionsX; //!< Vector of position on x axis for answers TextEdit fields
    QVector<QString*> _answerPositionsY; //!< Vector of position on y axis for answers TextEdit fields
    /**
     * @brief       Function for loading data from json file
     */
    void loadPuzzle();
};

#endif // PUZZLE_1_H
