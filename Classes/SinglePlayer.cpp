//
// Created by pavelgolubev345 on 31.03.16.
//

#include "SinglePlayer.h"
#include "MainScene.h"

SinglePlayer::SinglePlayer(MainScene *layer) : Game(layer) {
    std::srand(time(NULL));
    player.setTeam(FIRST_PLAYER);
    AI.setTeam(FIRST_PLAYER+1);
}

bool SinglePlayer::getXY(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    if (logic->checkStep(X, Y, player.team())) {
        scene->placeChip(X, Y, player.team());
        Locked = true;
        logic->setChip(X,Y,player.team());
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
    } while (!logic->checkStep(X, Y, AI.team()));

    //Бот ходит с задержкой
    CallFunc *callAIstep = CallFunc::create(CC_CALLBACK_0(MainScene::placeChip, scene, X, Y, AI.team()));
    CallFunc *callUnlock = CallFunc::create(CC_CALLBACK_0(SinglePlayer::Unlock, this));
    scene->runAction(Sequence::create(DelayTime::create(0.5), callAIstep, callUnlock, NULL));

    logic->setChip(X,Y,AI.team());
    update();
}


void SinglePlayer::passStep( ) {
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
