//
// Created by pavelgolubev345 on 01.04.16.
//

#ifndef MYGAME_ONLINEMULTIPLAYER_H
#define MYGAME_ONLINEMULTIPLAYER_H

#include "Game.h"

class OnlineMultiPlayer :public Layer, public Game {
private:
    Player player;
    OnlineMultiPlayer() = default;
public:
    OnlineMultiPlayer(Board *board);

    ~OnlineMultiPlayer() = default;

    bool getXY(int X, int Y);

    void update();

    void sync(float dt);
};


#endif //MYGAME_ONLINEMULTIPLAYER_H
