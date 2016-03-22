//
// Created by pavelgolubev345 on 22.03.16.
//

#include "Round.h"

Round::Round(Board *roundBoard) : AScore(0), BScore(0), CScore(0), turn(1), board(roundBoard), gameOver(false) {

}

void Round::startGame() {

}

void Round::update() {
    //добавить сюда логику
    //Должна изменять gameOver
}

void Round::endGame() {
    //Должна вызывать GameOverScene
}