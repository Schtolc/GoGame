//
// Created by pavelgolubev345 on 01.04.16.
//

#include "OnlineMultiPlayer.h"

OnlineMultiPlayer::OnlineMultiPlayer(Board *board) : Game(board), onAir(true) {
    gameStatus = PLAYER_CONNECTING;
    std::srand(time(NULL));
    token = std::rand() % 2000;
    int team = GoServer.ServerGetPlayerTeam(token);
    if (team == -1) {
        gameStatus = SERVER_FULL;
        this->Game::board->displayAlert(SERVER_FULL);
    } else {
        this->Game::board->displayAlert(PLAYER_CONNECTING);
        player.setTeam(team);
        std::thread t = std::thread(&OnlineMultiPlayer::sync, this);
        t.detach();
    }
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
    //Добавить логику. изменить счет, вывести алерт, изменить статус игры

}

void OnlineMultiPlayer::sync() {

    while (true) {
        if (GoServer.ServerIsReady()) {
            gameStatus = GAME_GOING;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    board->removeAlert();

    while (onAir) {
        std::cout << token << std::endl;
        step newStep = GoServer.ServerGetLastStep(token);
        if (newStep.x != -1) {
            Director::getInstance()->getScheduler()->performFunctionInCocosThread(
                    CC_CALLBACK_0(Board::placeChip, board, newStep.x, newStep.y, newStep.team));
            matrix[newStep.x][newStep.y] = newStep.team;
            update();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

OnlineMultiPlayer::~OnlineMultiPlayer() {
    onAir = false;
}

void OnlineMultiPlayer::passStep() {
    GoServer.ServerPassStep(token);
}

std::string OnlineMultiPlayer::getScore() {
    return "p" + std::to_string(player.team()) + ": " + std::to_string(player.getScore());
}
