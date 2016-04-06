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
    Sprite *boardSprite;
    Layer *layer;
    Label **scores;
    Menu *menu;
    Size visibleSize;
    Vec2 origin;


    Board() = default;

public:
    Board(Layer *layer, int playerAmount);

    Layer *getLayel() const;

    void displayScore(int score, int team);

    void displayAlert(int status);

    void removeAlert();

    void placeChip(int X, int Y, int team);

    void removeChip(int X, int Y);

    Label *createMenuLabel(std::string title);

    void placeMenuLabel(MenuItemLabel *menuLabel, const int X);

    std::pair<int, int> mousePositionToXY(Vec2 coordinates);
};


#endif //MYGAME_BOARD_H
