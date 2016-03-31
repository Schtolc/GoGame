//
// Created by pavelgolubev345 on 31.03.16.
//

#ifndef MYGAME_GAME_H
#define MYGAME_GAME_H

#include "Board.h"
#include "Player.h"

USING_NS_CC;

class Game {
protected:
    int matrix[19][19];
    Board *board;
public:

    Game();

    Game(Board *board);

    virtual ~Game() = default;

    //Проверяем можно ли поставить фишку игрока team на позицию X,Y
    bool checkStep(int X, int Y, int team);

    virtual bool getXY(int X, int Y) = 0;

    virtual void update() = 0;
};


#endif //MYGAME_GAME_H
