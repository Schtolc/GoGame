//
// Created by pavelgolubev345 on 21.04.16.
//

#ifndef MYGAME_GAMEMODEFACTORY_H
#define MYGAME_GAMEMODEFACTORY_H


#include "Game.h"
#include "LocalMultiPlayer.h"
#include "OnlineMultiPlayer.h"
#include "SinglePlayer.h"
#include "Board.h"

class GameFactory {
public:
    static Board* makeBoard(Layer* layer, int gameMode);
    static Game* makeGame(MainScene* layer, int gameMode);
};


#endif //MYGAME_GAMEMODEFACTORY_H
