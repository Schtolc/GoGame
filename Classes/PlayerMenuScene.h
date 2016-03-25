#ifndef __PLAYER_MENU_SCENE_H__
#define __PLAYER_MENU_SCENE_H__

#include "cocos2d.h"

class PlayerMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayerMenu);
    
private:
    void GoToGameScene( cocos2d::Ref *sender, const int amount);
    
};

#endif // __PLAYER_MENU_SCENE_H__
