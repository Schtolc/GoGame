//
// Created by pavelgolubev345 on 01.04.16.
//

#include "OnlineMultiPlayer.h"

OnlineMultiPlayer::OnlineMultiPlayer(Board *board) : Game(board) {
    std::srand(time(NULL));
    token = std::rand() % 2000;
    player.setTeam(GoServer.ServerGetPlayerTeam(token));
    std::thread t = std::thread(&OnlineMultiPlayer::sync, this);
    t.detach();
}

bool OnlineMultiPlayer::getXY(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    if (checkStep(X, Y, player.team())) {
        board->placeChip(X, Y, player.team());
        GoServer.ServerMakeStep(X, Y, player.team(), token);
        matrix[X][Y] = player.team();
        update();
        return true;
    } else {
        std::cout << "Warning cant place a chip (" << X << "," << Y << ")" << std::endl;
        return false;
    }
}

bool OnlineMultiPlayer::isLocked() {
    return GoServer.ServerIsPlayerLocked(token);
}

void OnlineMultiPlayer::update() {

}

void OnlineMultiPlayer::sync() {

    while (true) {
        std::cout << token << std::endl;
        step newStep = GoServer.ServerGetLastStep(token);
        if (newStep.x != -1) {
            Director::getInstance()->getScheduler()->performFunctionInCocosThread(CC_CALLBACK_0(Board::placeChip, board, newStep.x, newStep.y, newStep.team));
            matrix[newStep.x][newStep.y] = newStep.team;
            update();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}
