//
// Created by pavelgolubev345 on 21.03.16.
//

#ifndef MYGAME_BOARD_H
#define MYGAME_BOARD_H

#include <cstring>
#include <iostream>
#include "Defenitions.h"
#include "cocos2d.h"

USING_NS_CC;

class Board {
private:
    int matrix[19][19];
    Sprite *boardSprite;
public:

    Board();

    Sprite *getBoardSprite() const;

    //Геттер для матрицы
    int &boardAt(int X, int Y);

    //Проверяем можно ли поставить фишку игрока team на позицию X,Y
    bool checkStep(int X, int Y, int team);
};


#endif //MYGAME_BOARD_H
