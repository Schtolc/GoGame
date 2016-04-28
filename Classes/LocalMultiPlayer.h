//
// Created by pavelgolubev345 on 31.03.16.
//

#ifndef MYGAME_LOCALMULTIPLAYER_H
#define MYGAME_LOCALMULTIPLAYER_H

#include "Game.h"


class LocalMultiPlayer : public Game {
private:
    int playerAmount;
    Player *currentPlayer;
    Player *players;
    LocalMultiPlayer() = default;

    void nextPlayer();
public:

    LocalMultiPlayer(MainScene *s, int playerAmount);

    ~LocalMultiPlayer();

    void update();

    bool getXY(int X, int Y);

    void passStep();

    std::string getScore();


};

#endif //MYGAME_LOCALMULTIPLAYER_H
