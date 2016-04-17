//
// Created by pavelgolubev345 on 31.03.16.
//

#include "Game.h"

Game::Game(Board *board) : Locked(false), gameStatus(GAME_GOING) {
    assert(board != NULL);
    memset(matrix, -1, sizeof(int) * BOARD_SIZE * BOARD_SIZE);
    Game::board = board;
}

int Game::gamestatus() const {
    return gameStatus;
}


bool Game::checkStep(int X, int Y, int team) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18 && team >= 0);

    //Добавить логику проверяющую можно ли поставить фишку
    //т.е не занято ли поле или допустим ли ход

    if (matrix[X][Y] != -1)
        return false;
    return true;
}
