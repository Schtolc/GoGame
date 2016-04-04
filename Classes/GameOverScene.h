#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameOver : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene *createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);

private:
    void GoToGameScene(cocos2d::Ref *sender);

    void menuCloseCallback(cocos2d::Ref *pSender);

    Label *createMenuLabel(std::string title);
};

#endif // __GAMR_OVER_SCENE_H__
