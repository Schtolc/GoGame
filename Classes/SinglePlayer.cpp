//
// Created by pavelgolubev345 on 31.03.16.
//

#include "SinglePlayer.h"
#include <cstdlib>

SinglePlayer::SinglePlayer(Board *board) : Game(board), playerTeam(1)  { }

bool SinglePlayer::getXY(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    if (checkStep(X, Y, playerTeam)) {
        board->placeChip(X, Y, playerTeam);
        matrix[X][Y] = playerTeam;
        update();
        return true;
    } else {
        std::cout << "Warning cant place a chip (" << X << "," << Y <<  ")" << std::endl;
        return false;
    }
}

void SinglePlayer::update() {
    srand(time(NULL));
    int X = 0, Y = 0;
    do {
        X = rand()%18;
        Y = rand()%18;
    } while (!checkStep(X,Y,2));
    board->placeChip(X,Y,2);
}
