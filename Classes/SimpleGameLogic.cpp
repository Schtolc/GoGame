//
// Created by pavelgolubev345 on 08.05.16.
//

#include <string.h>
#include <assert.h>
#include "SimpleGameLogic.h"
#include "Defenitions.h"

SimpleGameLogic::SimpleGameLogic() {
    memset(matrix, EMPTY_CELL, sizeof(int) * 19 * 19);
}

bool SimpleGameLogic::checkStep(int X, int Y, int team) const {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18 && team >= FIRST_PLAYER);
    return matrix[X][Y] == EMPTY_CELL;
}

bool SimpleGameLogic::setChip(int X, int Y, int team) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18 && team >= FIRST_PLAYER);
    if (checkStep(X,Y,team)) {
        matrix[X][Y] = team;
        return true;
    }
    else {
        return false;
    }
}

int SimpleGameLogic::getCell(int X, int Y) const {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    return matrix[X][Y];
}
