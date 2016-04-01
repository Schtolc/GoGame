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
    bool Locked;
public:

    Game();

    Game(Board *board);

    virtual ~Game() = default;

    bool isLocked() const;

    void setLocked(bool l) {
        Locked = l;
    }
    //Проверяем можно ли поставить фишку игрока team на позицию X,Y
    bool checkStep(int X, int Y, int team);

    virtual bool getXY(int X, int Y) = 0;

    void update() {}
};


#endif //MYGAME_GAME_H
