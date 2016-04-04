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

public:

    SinglePlayer(Board *board);

    ~SinglePlayer() = default;

    bool getXY(int X, int Y);

    bool isLocked();

    void setLocked(bool l) {
        Locked = l;
    }

    void passStep();

    void AIstep();

    void update();
};


#endif //MYGAME_SINGLEPLAYER_H
