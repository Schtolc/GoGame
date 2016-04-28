//
// Created by pavelgolubev345 on 01.04.16.
//

#include "OnlineMultiPlayer.h"
#include "MainScene.h"

OnlineMultiPlayer::OnlineMultiPlayer(MainScene *s) : Game(s), GoServer(
        boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8090)) {

    gameStatus = PLAYER_CONNECTING;
    std::srand(time(NULL));
    token = std::rand() % 1000;

    std::pair<int,int> TeamLobby = GoServer.ServerGetPlayerTeam(token);
    int team = TeamLobby.first;
    GoServer.setLobbyId(TeamLobby.second);
    assert(-1 <= team && team <= PLAYER_AMOUNT - 1);

    if (team == -1) {
        gameStatus = SERVER_FULL;
        scene->displayAlert(SERVER_FULL);
    } else {
        scene->displayAlert(PLAYER_CONNECTING);
        player.setTeam(team);
        std::thread t = std::thread(&OnlineMultiPlayer::sync, this);
        t.detach();
    }
}

bool OnlineMultiPlayer::getXY(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    if (checkStep(X, Y, player.team())) {
        scene->placeChip(X, Y, player.team());
        assert(GoServer.ServerMakeStep(X, Y, player.team(), token));
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

    while (GoServer.ServerState() == PLAYER_CONNECTING) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    gameStatus = GAME_GOING;
    scene->removeAlert();

    while (GoServer.ServerState() != GAME_OVER) {
        std::cout << token << std::endl;
        Step newStep = GoServer.ServerGetLastStep(token);
        if (newStep.x != -1) {
            Director::getInstance()->getScheduler()->performFunctionInCocosThread(
                    CC_CALLBACK_0(MainScene::placeChip, scene, newStep.x, newStep.y, newStep.team));
            matrix[newStep.x][newStep.y] = newStep.team;
            update();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout<< "im here" << std::endl;

    if (gameStatus!=PLAYER_SURRENDERED) {
        gameStatus = PLAYER_SURRENDERED;
        Director::getInstance()->getScheduler()->performFunctionInCocosThread(
                CC_CALLBACK_0(MainScene::displayAlert, scene, PLAYER_SURRENDERED));
    }

}

void OnlineMultiPlayer::doSurrender() {
    gameStatus = PLAYER_SURRENDERED;
    assert(GoServer.ServerPassGameOver());
}

void OnlineMultiPlayer::passStep() {
    assert(GoServer.ServerPassStep(token));
}

std::string OnlineMultiPlayer::getScore() {
    return "p" + std::to_string(player.team()) + ": " + std::to_string(player.getScore());
}
