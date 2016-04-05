//
// Created by pavelgolubev345 on 31.03.16.
//

#include "SinglePlayer.h"

SinglePlayer::SinglePlayer(Board *board) : Game(board) {
    std::srand(time(NULL));
    player.setTeam(0);
    AI.setTeam(1);
}

bool SinglePlayer::getXY(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    if (checkStep(X, Y, player.team())) {
        board->placeChip(X, Y, player.team());
        Locked = true;
        matrix[X][Y] = player.team();
        update();
        AIstep();
        return true;
    } else {
        std::cout << "Warning cant place a chip (" << X << "," << Y << ")" << std::endl;
        return false;
    }
}

void SinglePlayer::update() {
    player.setScore(player.getScore()+1);
    board->displayScore(player.getScore(),player.team());
    AI.setScore(player.getScore()+2);
    board->displayScore(player.getScore(),AI.team());
}

void SinglePlayer::AIstep() {
    int X = 0, Y = 0;
    do {
        X = std::rand() % 18;
        Y = std::rand() % 18;
    } while (!checkStep(X, Y, AI.team()));
    CallFunc* callAIstep = CallFunc::create(CC_CALLBACK_0(Board::placeChip, board, X, Y, AI.team()));
    CallFunc* callUnlock = CallFunc::create(CC_CALLBACK_0(SinglePlayer::setLocked, this, false));

    board->getLayel()->runAction(Sequence::create(DelayTime::create(0.5), callAIstep, callUnlock, NULL));

    matrix[X][Y] = AI.team();
    update();
}

bool SinglePlayer::isLocked() {
    return Locked;
}

void SinglePlayer::passStep() {
    Locked = true;
    AIstep();
}
