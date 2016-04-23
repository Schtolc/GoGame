//
// Created by pavelgolubev345 on 23.04.16.
//

#ifndef MYGAME_VIEWBILDER_H
#define MYGAME_VIEWBILDER_H

#include "cocos2d.h"
#include "Defenitions.h"

USING_NS_CC;


class ViewBuilder {
private:

    Label *createMenuLabel(std::string title);

protected:
    Layer *layer;
    int playerAmount;
    Size visibleSize;
    Vec2 origin;

    ViewBuilder() = default;

public:

    ViewBuilder(Layer *l, int amount);

    void buildBackGround();

    void buildBoard(Sprite *&boardSprite);

    void buildScores(Label **&scores);

    void buildUI();

};


#endif //MYGAME_VIEWBILDER_H
