//
// Created by pavelgolubev345 on 31.03.16.
//

#include "Game.h"
#include "MainScene.h"
#include "SimpleGameLogic.h"

Game::Game(MainScene *s) : Locked(false), gameStatus(GAME_GOING) {
    assert(s != NULL);
   //!!!!
    logic = new SimpleGameLogic();
    scene = s;
}

bool Game::onTouchBegan(Touch *touch, Event *event) {
    //Идет подключение к серверу - касания не работают
    if (gameStatus == PLAYER_CONNECTING) {
        return true;
    }
        //Конец игры
    else if (gameStatus == GAME_OVER || gameStatus == PLAYER_SURRENDERED) {
        scene->GoToGameOver(scene);
        return true;
    }
        //Игрок не может ходить
    else if (isLocked()) {
        std::cout << "Locked" << std::endl;
        return true;
    }

    //Вычисляем по координатам касания X и Y доски
    std::pair<int, int> XY = scene->mousePositionToXY(touch->getLocation());

    //Игрок нажал не на поле
    if (0 > XY.first || XY.first > 18 || 0 > XY.second || XY.second > 18) {
        return true;
    }
        //Передаем координаты модели игры
    else {
        getXY(XY.first, XY.second);
        return true;
    }
}

void Game::surrender() {
    gameStatus = GAME_OVER;
    this->doSurrender();
    scene->displayAlert(GAME_OVER);
}


bool Game::isLocked() {
    return Locked;
}
