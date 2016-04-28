//
// Created by pavelgolubev345 on 31.03.16.
//

#ifndef MYGAME_GAME_H
#define MYGAME_GAME_H


class MainScene;
#include "Player.h"
#include <iostream>

USING_NS_CC;

class Game {
private:
    Game() = default;

protected:
    //Класс логики
    int matrix[19][19];
    MainScene* scene;
    bool Locked;
    int gameStatus;
public:
    Game(MainScene *s);

    virtual ~Game() = default;


    //Template method
    void surrender();
    virtual void doSurrender() { }

    virtual bool isLocked();

    //Инкапсулируем в логику
    bool checkStep(int X, int Y, int team);

    void update() { }

    //Получаем X и Y доски и совершаем ход
    virtual bool getXY(int X, int Y) = 0;

    //Пропуск хода
    virtual void passStep() = 0;

    //Отдаем счет игроков
    virtual std::string getScore() = 0;

    //Обработка событий мышки
    bool onTouchBegan(Touch *touch, Event *event);

};


#endif //MYGAME_GAME_H
