//
// Created by pavelgolubev345 on 31.03.16.
//

#include "LocalMultiPlayer.h"
#include "MainScene.h"

LocalMultiPlayer::LocalMultiPlayer(MainScene *s, int playerAmount) : Game(s) {
    assert(0 < playerAmount && playerAmount <= 4);
    LocalMultiPlayer::playerAmount = playerAmount;
    players = new Player[playerAmount]();
    for (int i = 0; i < playerAmount; i++) {
        players[i].setTeam(i+FIRST_PLAYER);
    }
    currentPlayer = players;
}

LocalMultiPlayer::~LocalMultiPlayer() {
    delete[] players;
}

bool LocalMultiPlayer::getXY(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    if (logic->setChip(X, Y, currentPlayer->team())) {
        scene->placeChip(X, Y, currentPlayer->team());
        update();
        nextPlayer();
        return true;
    } else {
        std::cout << "Warning cant place a chip (" << X << "," << Y << "," << currentPlayer->team() << ")" << std::endl;
        return false;
    }
}

void LocalMultiPlayer::update() {
    //Добавить логику. изменить счет, вывести алерт, изменить статус игры
//    for (int i = 0; i < 19; i++) {
//        for (int j =0 ; j < 19; j++) {
////            if (logic->getCell(i,j)==EMPTY_CELL) {
////                if (scene->chipExist(i,j)) {
//                    scene->removeChip(i,j);
////                }
////            }
//        }
//    }
}

void LocalMultiPlayer::passStep() {
    nextPlayer();
}

std::string LocalMultiPlayer::getScore() {
    std::string score = "";
    for (int i = 0; i < playerAmount; i++) {
        score += "p" + std::to_string(i) + ": " + std::to_string(players[i].getScore()) + "\n";
    }
    return score;
}

void LocalMultiPlayer::nextPlayer() {
    if (currentPlayer->team() == FIRST_PLAYER + playerAmount - 1) {
        currentPlayer = players;
    } else {
        currentPlayer++;
    }
}
