#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Board.h"
#include "LocalMultiPlayer.h"
#include "GameOverScene.h"

USING_NS_CC;

class MainScene : public cocos2d::Layer {
private:
    Game *game;
    Board board;
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

    //Обработка событий мышки
    bool onTouchBegan(Touch *touch, Event *event);

    void GoToGameOver(cocos2d::Ref *sender);

};

#endif // __MAIN_SCENE_H__
