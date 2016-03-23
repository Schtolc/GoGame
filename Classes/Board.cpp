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
    if (X < 0 || X > 18 || Y < 0 || Y > 18 || currentPlayer < 0 || currentPlayer >= PLAYER_AMOUNT) {
        std::cout << "Error - Invalid args (" << X << ", " << Y << ", " << currentPlayer << ") for checkChip()" <<
        std::endl;
        return false;
    }

    //Добавить логику проверяющую можно ли поставить фишку
    //т.е не занято ли поле или допустим ли ход

    if (matrix[X][Y] != -1)
        return false;
    return true;
}

int &Board::boardAt(int X, int Y) {
    if (X < 0 || X > 18 || Y < 0 || Y > 18) {
        std::cout << "Invalid matrix position (" << X << ", " << Y << ")" << std::endl;
        return matrix[0][0];
    }
    return matrix[X][Y];
}
