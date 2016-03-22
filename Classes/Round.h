//
// Created by pavelgolubev345 on 22.03.16.
//

#ifndef MYGAME_ROUND_H
#define MYGAME_ROUND_H

#include "Board.h"

USING_NS_CC;

class Round {
private:
    int AScore;
    int BScore;
    int CScore;
    char turn;
    bool gameOver;
    Board* board;
    Round() = default;
public:
    Round(Board*);
    void startGame();
    void update();
    void endGame();    
};


#endif //MYGAME_ROUND_H
