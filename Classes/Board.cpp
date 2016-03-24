//
// Created by pavelgolubev345 on 21.03.16.
//

#include "Board.h"

Board::Board() {
    memset(matrix, -1, sizeof(int) * BOARD_SIZE * BOARD_SIZE);
    boardSprite = Sprite::create("board.png");
    boardSprite->setScale(BOARD_SCALE);
}

Sprite *Board::getBoardSprite() const {
    return boardSprite;
}


bool Board::checkStep(int X, int Y, int currentPlayer) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18 && 0 <= currentPlayer && currentPlayer < PLAYER_AMOUNT);

    //Добавить логику проверяющую можно ли поставить фишку
    //т.е не занято ли поле или допустим ли ход

    if (matrix[X][Y] != -1)
        return false;
    return true;
}

int &Board::boardAt(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    return matrix[X][Y];
}
