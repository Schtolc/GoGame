//
// Created by pavelgolubev345 on 21.03.16.
//

#ifndef MYGAME_BOARD_H
#define MYGAME_BOARD_H

#include <iostream>
#include <cstring>
#include "Defenitions.h"
#include "cocos2d.h"

USING_NS_CC;

class Board {
private:
    int matrix[19][19];
    Layer* boardLayer;
    Size visibleSize;
    Vec2 origin;
    Sprite* boardSprite;
    Board() = default;
public:
    Board(Layer* layer, Size size, Vec2 vector);

    //Ставим фишку игрока team на позицию X,Y
    void placeChip(int X, int Y, int team);

    //Убираем фишку с позиции X,Y
    void removeChip(int X, int Y);

    //Проверяем можно ли поставить фишку игрока team на позицию X,Y
    bool checkStep(int X, int Y, int team);

};


#endif //MYGAME_BOARD_H
