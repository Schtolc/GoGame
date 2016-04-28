//
// Created by pavelgolubev345 on 31.03.16.
//

#ifndef MYGAME_SINGLEPLAYER_H
#define MYGAME_SINGLEPLAYER_H

#include "Game.h"


class SinglePlayer : public Game {
private:
    Player player;
    Player AI;

    SinglePlayer() = default;

    void AIstep();

    void Unlock();

public:

    SinglePlayer(MainScene *layer);

    ~SinglePlayer() = default;

    void update();

    bool isLocked();

    bool getXY(int X, int Y);

    void passStep();

    std::string getScore();
};


#endif //MYGAME_SINGLEPLAYER_H
