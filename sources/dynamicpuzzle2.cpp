#include "headers/dynamicpuzzle2.h"

DynamicPuzzle2::DynamicPuzzle2(QGraphicsView *parent, QGraphicsScene *scene, qint16 cl)
    : Puzzle(parent, scene, cl)
{
    setSceneRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    setBackgroundBrush(QImage(":/resources/puzzles/fifteen_puzzle/frame1.png"));
    initializePuzzle();
    _closeBtn = new QGraphicsPixmapItem(QPixmap(":/resources/buttons/close_btn.png"));
    _closeBtn->moveBy(1075,0);
    _closeBtn->setFlag(QGraphicsItem::ItemIsFocusable);
    this->addItem(_closeBtn);

}
void DynamicPuzzle2::initializePuzzle(){
    // Initializing tiles. Setting their pictures and values.
    QString base(":/resources/puzzles/fifteen_puzzle/");
    for(qint16 j = 0; j < NUM_OF_ROWS; j++){
        for(qint16 i = 0; i < NUM_OF_COLS; i++) {
            auto s1 = base + QString::number(j*NUM_OF_COLS + i) + ".png";
            QGraphicsPixmapItem* tilePixmap = new QGraphicsPixmapItem(QPixmap(QString(s1)));
            QPair<QGraphicsPixmapItem*, qint16> item(tilePixmap, j*NUM_OF_COLS + i);
            _tiles.push_back(item);
            _tiles.at(j*NUM_OF_COLS + i).first->setPos(QPoint(STARTING_X+MOVE_VAL*i, STARTING_Y+MOVE_VAL*j));
        }
    }
    // Adding tiles to the scene.
    for(qint16 i = 0; i < NUM_OF_ROWS; i++) {
        for(qint16 j = 0; j < NUM_OF_COLS; j++) {
            this->addItem(_tiles.at(NUM_OF_COLS*i + j).first);
        }
    }
    int i = 0;
    int position = _tiles.size() - 1;
    int nextPosition = 0;
    // Swaping "empty" tile with "non-empty" tiles for NUM_OF_ITERS times. This way, we know that we have a solution for sure.
    while(i < NUM_OF_ITERS){
        nextPosition = std::rand();
        // We're checking every possible situation and using probability randomizing tiles.
        switch(position) {
            case 0: {
                if ( nextPosition % 2 == 0) {
                    nextPosition = position + 1;
                }
                else {
                    nextPosition = position + 4;
                }
                break;
            }
            case 1:
            case 2: {
                if ( nextPosition % 3 == 0) {
                    nextPosition = position - 1;
                }
                else if ( nextPosition % 3 == 1){
                    nextPosition = position + 1;
                }
                else {
                    nextPosition = position + 4;
                }
                break;
            }
            case 3: {
                if ( nextPosition % 2 == 0){
                    nextPosition = position - 1;
                }
                else {
                    nextPosition = position + 4;
                }
                break;
            }
            case 4:
            case 8: {
                if ( nextPosition % 3 == 0){
                    nextPosition = position + 1;
                }
                else if ( nextPosition % 3 == 1) {
                    nextPosition = position + 4;
                }
                else {
                    nextPosition = position - 4;
                }
                break;
            }
            case 5:
            case 6:
            case 9:
            case 10: {
                if ( nextPosition % 4 == 0){
                    nextPosition = position + 1;
                }
                else if (nextPosition % 4 == 1){
                    nextPosition = position - 1;
                }
                else if (nextPosition % 4 == 2){
                    nextPosition = position + 4;
                }
                else {
                    nextPosition = position - 4;
                }
                break;
            }
            case 7:
            case 11: {
                if ( nextPosition % 3 == 0 ){
                    nextPosition = position - 1;
                }
                else if ( nextPosition % 3 == 1 ) {
                    nextPosition = position + 4;
                }
                else {
                    nextPosition = position - 4;
                }
                break;
            }
            case 12: {
                if ( nextPosition % 2 == 0){
                    nextPosition = position + 1;
                }
                else {
                    nextPosition = position - 4;
                }
                break;
            }
            case 13:
            case 14: {
                if ( nextPosition % 3 == 0){
                    nextPosition = position + 1;
                }
                else if ( nextPosition % 3 == 1){
                    nextPosition = position - 1;
                }
                else {
                    nextPosition = position - 4;
                }
                break;
            }
            case 15: {
                if ( nextPosition % 2 == 0){
                    nextPosition = position - 4;
                }
                else {
                    nextPosition = position - 1;
                }
            }
        }
        swapTiles(position, nextPosition);
        i++;
    }

}

void DynamicPuzzle2::swapTiles(int &position, int nextPosition){
    auto tmp = _tiles.begin() + nextPosition;
    QPair<qreal, qreal> current(_tiles.at(position).first->x(),_tiles.at(position).first->y());
    QPair<qreal, qreal> next(tmp->first->x(),tmp->first->y());
    // Setting the position of the current tile to the nextPosition.
    _tiles.at(position).first->setPos(next.first, next.second);
    // Setting the position of the next tile to the position.
    _tiles.at(nextPosition).first->setPos(current.first, current.second);
    // Swaping tiles.
    std::iter_swap(_tiles.begin() + position, _tiles.begin() + nextPosition);
    // Setting the next position as the current position.
    position = nextPosition;
}
void DynamicPuzzle2::mousePressEvent(QGraphicsSceneMouseEvent *){
    if(_closeBtn->isUnderMouse()){
        puzzleOver();
    }
    // Handling mouse press event for every single tile.
    for(int i = 0; i < NUM_OF_COLS*NUM_OF_ROWS; i++){
        if (_tiles.at(i).first->isUnderMouse()){
            switch(i) {
                case 0: {
                    if(_tiles.at(i+1).second == EMPTY_TILE){
                        swapTiles(i, i+1);
                    }
                    else if(_tiles.at(i+4).second == EMPTY_TILE){
                        swapTiles(i, i+4);
                    }
                    break;
                }
                case 1:
                case 2: {
                    if(_tiles.at(i+1).second == EMPTY_TILE){
                        swapTiles(i, i+1);
                    }
                    else if(_tiles.at(i-1).second == EMPTY_TILE) {
                        swapTiles(i, i-1);
                    }
                    else if(_tiles.at(i+4).second == EMPTY_TILE) {
                        swapTiles(i, i+4);
                    }
                    break;

                }
                case 3: {
                    if (_tiles.at(i-1).second == EMPTY_TILE){
                        swapTiles(i, i-1);
                    }
                    else if (_tiles.at(i+4).second == EMPTY_TILE){
                        swapTiles(i, i+4);
                    }
                    break;
                }
                case 4:
                case 8: {
                    if (_tiles.at(i+1).second == EMPTY_TILE){
                        swapTiles(i,i+1);
                    }
                    else if(_tiles.at(i+4).second == EMPTY_TILE){
                        swapTiles(i, i+4);
                    }
                    else if(_tiles.at(i-4).second == EMPTY_TILE) {
                        swapTiles(i, i-4);
                    }
                    break;
                }
                case 5:
                case 6:
                case 9:
                case 10: {
                    if(_tiles.at(i-1).second == EMPTY_TILE){
                        swapTiles(i, i-1);
                    }
                    else if(_tiles.at(i+1).second == EMPTY_TILE){
                        swapTiles(i, i+1);
                    }
                    else if(_tiles.at(i+4).second == EMPTY_TILE){
                        swapTiles(i, i+4);
                    }
                    else if(_tiles.at(i-4).second == EMPTY_TILE){
                        swapTiles(i, i-4);
                    }
                    break;
                }
                case 7:
                case 11:{
                    if(_tiles.at(i-1).second == EMPTY_TILE){
                        swapTiles(i, i-1);
                    }
                    else if(_tiles.at(i+4).second == EMPTY_TILE){
                        swapTiles(i, i+4);
                    }
                    else if(_tiles.at(i-4).second == EMPTY_TILE){
                        swapTiles(i, i-4);
                    }
                    break;
                }
                case 12: {
                    if(_tiles.at(i-4).second == EMPTY_TILE){
                        swapTiles(i, i-4);
                    }
                    else if(_tiles.at(i+1).second == EMPTY_TILE){
                        swapTiles(i, i+1);
                    }
                    break;
                }
                case 13:
                case 14:{
                    if(_tiles.at(i-1).second == EMPTY_TILE){
                        swapTiles(i, i-1);
                    }
                    else if(_tiles.at(i+1).second == EMPTY_TILE){
                        swapTiles(i, i+1);
                    }
                    else if(_tiles.at(i-4).second == EMPTY_TILE){
                        swapTiles(i, i-4);
                    }
                    break;
                }
                case 15: {

                    if(_tiles.at(i-1).second == 15){
                        swapTiles(i, i-1);
                    }
                    else if(_tiles.at(i-4).second == 15){
                        swapTiles(i, i-4);
                    }
                    break;
               }
           }
        }
    }
    checkResult();
}


void DynamicPuzzle2::puzzleOver(){
    this->deleteLater();
    getView()->setScene(getScene());
}

void DynamicPuzzle2::checkResult(){
    QVector<int> val;
    for(auto tile : _tiles){
        val.push_back(tile.second);
    }
    if(std::is_sorted(val.begin(), val.end())){
        getLK()->setKeyAvailability(true);
        getLog()->setText("Chest unlocked, click to get key");
        puzzleOver();
    }
}
