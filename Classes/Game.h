//
// Created by pavelgolubev345 on 31.03.16.
//

#ifndef MYGAME_GAME_H
#define MYGAME_GAME_H

#include "Board.h"
#include "Player.h"

USING_NS_CC;

class Game {
private:
    Game() = default;

protected:
    int matrix[19][19];
    Board *board;
    bool Locked;
    int gameStatus;
public:
    Game(Board *board);

    virtual ~Game() = default;

    int gamestatus() const;

    virtual void performGameOver() {}

    //Проверяем можно ли поставить фишку игрока team на позицию X,Y
    bool checkStep(int X, int Y, int team);

    void update() { }

    //Проверяем может ли игрок ходить
    virtual bool isLocked() = 0;

    //Получаем X и Y доски и совершаем ход
    virtual bool getXY(int X, int Y) = 0;

    //Пропуск хода
    virtual void passStep() = 0;

    //Отдаем счет игроков
    virtual std::string getScore() = 0;

};


#endif //MYGAME_GAME_H
