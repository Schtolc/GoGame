//
// Created by pavelgolubev345 on 01.04.16.
//

#ifndef MYGAME_ONLINEMULTIPLAYER_H
#define MYGAME_ONLINEMULTIPLAYER_H

#include "Game.h"
#include "GoGameServer.h"
#include <chrono>
#include <thread>


class OnlineMultiPlayer : public Game {
private:
    Player player;
    GoGameServer GoServer;
    int token;

    OnlineMultiPlayer() = default;

    void sync();

public:
    OnlineMultiPlayer(MainScene *s);

    ~OnlineMultiPlayer() = default;

    void update();

    bool isLocked();

    bool getXY(int X, int Y);

    void passStep();

    void performGameOver();

    std::string getScore();

};


#endif //MYGAME_ONLINEMULTIPLAYER_H
