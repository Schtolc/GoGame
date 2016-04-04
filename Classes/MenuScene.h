//
// Created by pavelgolubev345 on 04.04.16.
//

#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "cocos2d.h"
#include "MainScene.h"
#include "Defenitions.h"

USING_NS_CC;

class MenuScene : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene *createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);

    cocos2d::Menu* MainMenu;
    Size visibleSize;
    Vec2 origin;

private:

    Label *createMenuLabel(std::string title);

    void showPlayMenu(cocos2d::Ref *sender);

    void showPlayersAmountMenu(cocos2d::Ref *sender);

    void showGameModesMenu(cocos2d::Ref *sender);

    void menuClose(cocos2d::Ref *sender);

    void GoToGameScene(cocos2d::Ref *sender, const int gameMode);

};


#endif //MENU_SCENE_H
