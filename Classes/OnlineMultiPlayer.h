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
    bool onAir;
    OnlineMultiPlayer() = default;
public:
    OnlineMultiPlayer(Board *board);

    ~OnlineMultiPlayer();

    bool getXY(int X, int Y);

    bool isLocked();

    void update();

    void passStep();

    void sync();
};


#endif //MYGAME_ONLINEMULTIPLAYER_H
