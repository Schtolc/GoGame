#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Board.h"
#include "Player.h"
#include "GameOverScene.h"

USING_NS_CC;

class MainScene : public cocos2d::Layer {
private:
    Board board;
    int playerAmount;
    Player *currentPlayer;
    Player *players;
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

    //Ставим фишку игрока team на позицию X,Y
    bool placeChip(int X, int Y);

    //Убираем фишку с позиции X,Y
    bool removeChip(int X, int Y);

    //Обработка событий ошибок
    bool onTouchBegan(Touch *touch, Event *event);

    //Логика игры (взаимодействие с доской)
    void update();

    void GoToGameOver( cocos2d::Ref *sender );

};

#endif // __MAIN_SCENE_H__
