#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Board.h"
#include "Player.h"
#include <thread>
#include <chrono>

USING_NS_CC;

class HelloWorld : public cocos2d::Layer {
private:
    Board board;
    Player *currentPlayer;
    Player players[PLAYER_AMOUNT];
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    //Ставим фишку игрока team на позицию X,Y
    bool placeChip(int X, int Y);

    //Убираем фишку с позиции X,Y
    void removeChip(int X, int Y);

    //Обработка событий ошибок
    bool onTouchBegan(Touch *touch, Event *event);

    //Логика игры (взаимодействие с доской)
    void update();

};

#endif // __HELLOWORLD_SCENE_H__
