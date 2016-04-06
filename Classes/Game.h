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
    int gameStatus;
public:

    Game();

    int gamestatus() const {
        return gameStatus;
    }
    Game(Board *board);

    virtual ~Game() = default;

    virtual bool isLocked() = 0;

    //Проверяем можно ли поставить фишку игрока team на позицию X,Y
    bool checkStep(int X, int Y, int team);

    virtual bool getXY(int X, int Y) = 0;

    virtual void passStep() = 0 ;

    virtual std::string getScore() = 0;

    void update() {}
};


#endif //MYGAME_GAME_H
