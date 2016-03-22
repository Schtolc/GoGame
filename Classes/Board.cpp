//
// Created by pavelgolubev345 on 21.03.16.
//

#include "Board.h"

Board::Board() {
    memset(matrix, 0, sizeof(int) * BOARD_SIZE * BOARD_SIZE);
    boardSprite = Sprite::create("board.png");
    boardSprite->setScale(BOARD_SCALE);
}

Sprite* Board::getBoardSprite() const {
    return boardSprite;
}


bool Board::checkStep(int X, int Y, int team) {
    if (X < 0 || X > 18 || Y < 0 || Y > 18 || team < 0 || team > PLAYER_AMOUNT) {
        std::cout << "Error - Invalid args (" << X << ", " << Y << ", " << team << ") for checkChip()" << std::endl;
        return false;
    }
    //Добавить логику
    if (matrix[X][Y] != 0)
        return false;
    return true;
}

//Тут надо прикрутить error handling
int &Board::boardAt(int X, int Y){
    if (X < 0 || X > 18 || Y < 0 || Y > 18) {
        std::cout << "Invalid matrix position (" << X<<", "<<Y<<")"<< std::endl;
        return matrix[0][0];
    }
    return matrix[X][Y];
}
