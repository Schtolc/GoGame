//
// Created by pavelgolubev345 on 08.05.16.
//

#ifndef MYGAME_SIMPLEGAMELOGIC_H
#define MYGAME_SIMPLEGAMELOGIC_H


#include "GameLogic.h"

class SimpleGameLogic : public GameLogic {
public:
    SimpleGameLogic();

    bool setChip(int X, int Y, int team);

    int getCell(int X, int Y) const;

    ~SimpleGameLogic() = default;

private:
    int matrix[19][19];
    bool checkStep(int X, int Y, int team) const;
};


#endif //MYGAME_SIMPLEGAMELOGIC_H
