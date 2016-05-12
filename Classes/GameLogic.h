//
// Created by pavelgolubev345 on 08.05.16.
//

#ifndef MYGAME_GAMELOGIC_H
#define MYGAME_GAMELOGIC_H

class GameLogic {
public:
    GameLogic() = default;

    //True если на ячейку [X,Y] можно поставить фишку игрока team, False если нельзя
    // 0 <= X <= 18 &&  0 <= Y <= 18 && team = {1,2}
//    virtual bool checkStep(int X, int Y, int team) const = 0;

    //Ставит на ячейку [X,Y] фишку игрока team - должна выполнятся всегда, т.к. перед ней вызывается функция checkStep
    // 0 <= X <= 18 &&  0 <= Y <= 18 && team = {1,2}
    virtual bool setChip(int X, int Y, int team) = 0;

    //Возвращает team игрока который поставил фишку на ячейку [X,Y]
    // 0 <= X <= 18 &&  0 <= Y <= 18
    virtual int getCell(int X, int Y) const = 0;

    virtual ~GameLogic() = default;
};

#endif //MYGAME_GAMELOGIC_H
