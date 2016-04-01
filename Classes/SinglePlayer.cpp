//
// Created by pavelgolubev345 on 31.03.16.
//

#include "SinglePlayer.h"

SinglePlayer::SinglePlayer(Board *board) : Game(board), playerTeam(1) {
    std::srand(time(NULL));
}

bool SinglePlayer::getXY(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    if (checkStep(X, Y, playerTeam)) {
        board->placeChip(X, Y, playerTeam);
        Locked = true;
        matrix[X][Y] = playerTeam;
        update();
        AIstep();
        return true;
    } else {
        std::cout << "Warning cant place a chip (" << X << "," << Y << ")" << std::endl;
        return false;
    }
}

void SinglePlayer::update() {

}

void SinglePlayer::AIstep() {
    int X = 0, Y = 0;
    do {
        X = std::rand() % 18;
        Y = std::rand() % 18;
    } while (!checkStep(X, Y, 2));
    CallFunc* callbk = CallFunc::create(CC_CALLBACK_0(Board::placeChip, board, X, Y, 2));
    CallFunc* callLocked = CallFunc::create(CC_CALLBACK_0(Game::setLocked, this, false));

    board->getLayel()->runAction(Sequence::create(DelayTime::create(2), callbk, NULL));
    board->getLayel()->runAction(Sequence::create(DelayTime::create(2), callLocked, NULL));

    matrix[X][Y] = 2;
    update();
}
