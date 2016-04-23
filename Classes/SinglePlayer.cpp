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
    //Добавить логику. изменить счет, вывести алерт, изменить статус игры

}

void SinglePlayer::AIstep() {
    //Совершаем рандомный ход
    int X = 0, Y = 0;
    do {
        X = std::rand() % 18;
        Y = std::rand() % 18;
    } while (!checkStep(X, Y, AI.team()));

    //Бот ходит с задержкой
    CallFunc *callAIstep = CallFunc::create(CC_CALLBACK_0(Board::placeChip, board, X, Y, AI.team()));
    CallFunc *callUnlock = CallFunc::create(CC_CALLBACK_0(SinglePlayer::Unlock, this));
    board->getLayer()->runAction(Sequence::create(DelayTime::create(0.5), callAIstep, callUnlock, NULL));

    matrix[X][Y] = AI.team();
    update();
}

bool SinglePlayer::isLocked() {
    return Locked;
}

void SinglePlayer::passStep() {
    if (isLocked()) {
        std::cout << "Locked" << std::endl;
        return;
    } else {
        Locked = true;
        AIstep();
    }
}

std::string SinglePlayer::getScore() {
    return "p1: " + std::to_string(player.getScore()) + "\np2: " + std::to_string(AI.getScore());
}

void SinglePlayer::Unlock() {
    Locked = false;
}
