//
// Created by pavelgolubev345 on 21.04.16.
//

#include "GameModeFactory.h"

Board *GameFactory::makeBoard(Layer *layer, int gameMode) {
    switch (gameMode) {
        case SINGLE_PLAYER:
            return new Board(layer, 2);
        case ONLINE_MULTI_PLAYER:
            return new Board(layer, 4);
        case LOCAL_2_PLAYER:
            return new Board(layer, 2);
        case LOCAL_3_PLAYER:
            return new Board(layer, 3);
        case LOCAL_4_PLAYER:
            return new Board(layer, 4);
    }
    return NULL;
}

Game *GameFactory::makeGame(MainScene *layer, int gameMode) {
    switch (gameMode) {
        case SINGLE_PLAYER:
            return new SinglePlayer(layer);
        case ONLINE_MULTI_PLAYER:
            return new OnlineMultiPlayer(layer);
        case LOCAL_2_PLAYER:
            return new LocalMultiPlayer(layer, 2);
        case LOCAL_3_PLAYER:
            return new LocalMultiPlayer(layer, 3);
        case LOCAL_4_PLAYER:
            return new LocalMultiPlayer(layer, 4);
    }
    return NULL;
}

