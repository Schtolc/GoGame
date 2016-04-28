#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

#include "Game.h"
#include "Board.h"
#include "GameOverScene.h"
#include "GameModeFactory.h"


USING_NS_CC;



class MainScene : public cocos2d::Layer {
private:
    Game *game;
    Board *board;
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    CREATE_FUNC(MainScene);

    void placeChip(int X, int Y, int team);

    std::pair<int, int> mousePositionToXY(Vec2 coordinates);

    void removeChip(int X, int Y);

    void displayAlert(int status);

    void removeAlert();

    void surrender(Ref *sender);

    void passStep(Ref *sender);

    void GoToGameOver(Ref *sender);

};

#endif // __MAIN_SCENE_H__
