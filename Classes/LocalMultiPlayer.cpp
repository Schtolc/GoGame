//
// Created by pavelgolubev345 on 31.03.16.
//

#include "LocalMultiPlayer.h"

LocalMultiPlayer::LocalMultiPlayer() : playerAmount(0), players(NULL), currentPlayer(NULL) { }

LocalMultiPlayer::LocalMultiPlayer(Board *board, int playerAmount) : Game(board) {
    assert(0 < playerAmount && playerAmount <= 4);
    LocalMultiPlayer::playerAmount = playerAmount;
    players = new Player[playerAmount]();
    for (int i = 0; i < playerAmount; i++) {
        players[i].setTeam(i);
    }
    currentPlayer = players;
}

LocalMultiPlayer::~LocalMultiPlayer() {
    delete[] players;
}

bool LocalMultiPlayer::getXY(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    if (checkStep(X, Y, currentPlayer->team())) {
        board->placeChip(X, Y, currentPlayer->team());
        matrix[X][Y] = currentPlayer->team();
        update();
        return true;
    } else {
        std::cout << "Warning cant place a chip (" << X << "," << Y << "," << currentPlayer->team() << ")" << std::endl;
        return false;
    }
}

void LocalMultiPlayer::update() {
    //Добавить логику




    if (currentPlayer->team() == playerAmount - 1) {
        currentPlayer = players;
    } else {
        currentPlayer++;
    }
}

bool LocalMultiPlayer::isLocked() {
    return false;
}

void LocalMultiPlayer::passStep() {
    update();
}

std::string LocalMultiPlayer::getScore() {
    std::string score = "";
    for (int i = 0; i < playerAmount; i++) {
        score += std::string("p") + std::to_string(i) + std::string(": ") + std::to_string(players[i].getScore()) + std::string("\n");
    }
    return score;
}
