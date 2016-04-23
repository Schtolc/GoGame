//
// Created by pavelgolubev345 on 04.04.16.
//

#ifndef MENU_SCENE_H
#define MENU_SCENE_H


#include "cocos2d.h"
#include "MainScene.h"
#include "Board.h"
#include "Defenitions.h"
#include <functional>

USING_NS_CC;

class MenuScene : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene *createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);

private:
    Menu *menu;
    Size visibleSize;
    Vec2 origin;

    void showMainMenu(Ref *sender);

    void showLocalMultiplayerMenu(Ref *sender);

    void showGameModesMenu(Ref *sender);

    void gameExit(Ref *sender) const;

    void GoToGameScene(Ref *sender, const int gameMode);

    Label *createMenuLabel(std::string title);

    void placeMenuLabel(MenuItemLabel* menuLabel, const int Y);
};


#endif //MENU_SCENE_H
