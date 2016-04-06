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
    int playerTeam;
    int score;
    std::string chipPath;
public:
    Player();

    int getScore() const;

    void setScore(int score);

    int team() const;

    void setTeam(int num);

    std::string getChipPath() const;
};


#endif //MYGAME_PLAYER_H
