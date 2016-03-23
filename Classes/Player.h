//
// Created by pavelgolubev345 on 23.03.16.
//

#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

#include "Defenitions.h"
#include "cocos2d.h"

USING_NS_CC;

class Player {
private:
    static int playerAmount;
    int playerNumber;
    int score;
    Color3B chipColor;
public:
    Player();

    int getScore() const;

    void setScore(int score);

    int getPlayerNumber() const;

    void setPlayerNumber(int num);

    Color3B getChipColor() const;
};


#endif //MYGAME_PLAYER_H
