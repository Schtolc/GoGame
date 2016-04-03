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
    LocalMultiPlayer();
public:

    LocalMultiPlayer(Board *board, int playerAmount);

    ~LocalMultiPlayer();

    //Проверяем можно ли поставить фишку игрока team на позицию X,Y

    bool isLocked();

    bool getXY(int X, int Y);

    void update();
};

#endif //MYGAME_LOCALMULTIPLAYER_H
