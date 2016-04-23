//
// Created by pavelgolubev345 on 23.04.16.
//

#include "ViewBuilder.h"
#include "MainScene.h"

void ViewBuilder::buildBackGround() {
    auto backgroundSprite = Sprite::create("background.jpg");
    backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
    backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    layer->addChild(backgroundSprite, 0);
}

void ViewBuilder::buildBoard(Sprite *&boardSprite) {
    boardSprite = Sprite::create("board.png");
    boardSprite->setScale(BOARD_SCALE);
    boardSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    layer->addChild(boardSprite, 1);
}

void ViewBuilder::buildScores(Label **&scores) {
    scores = new Label *[playerAmount];
    for (int i = 0; i < playerAmount; i++) {
        scores[i] = Label::createWithTTF("p" + std::to_string(i + 1) + ": 0", "fonts/go3v2.ttf", 32);
        scores[i]->setPosition(Point(visibleSize.width / (playerAmount + 1) * (i + 1),
                                     visibleSize.height - scores[i]->getContentSize().height / 2));
        layer->addChild(scores[i], 1);
    }
}


void ViewBuilder::buildUI() {
    Menu *menu = Menu::create();
    menu->setPosition(Point::ZERO);
    layer->addChild(menu);

    auto Play = MenuItemLabel::create(createMenuLabel("Pass"),
                                      CC_CALLBACK_1(MainScene::passStep, dynamic_cast<MainScene *>(layer)));
    Play->setPosition(Point(origin.x + visibleSize.width / 3 * 1 - Play->getContentSize().width / 2,
                            origin.y + Play->getContentSize().height / 2));
    menu->addChild(Play);

    auto Exit = MenuItemLabel::create(createMenuLabel("Surrender"),
                                      CC_CALLBACK_1(MainScene::surrender, dynamic_cast<MainScene *>(layer)));
    Exit->setPosition(Point(origin.x + visibleSize.width / 3 * 2 - Exit->getContentSize().width / 2,
                            origin.y + Exit->getContentSize().height / 2));
    menu->addChild(Exit);

}

ViewBuilder::ViewBuilder(Layer *l, int amount) : layer(l), playerAmount(amount) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

Label *ViewBuilder::createMenuLabel(std::string title) {
    assert(title != "");
    auto menuLabel = Label::createWithTTF(title, "fonts/go3v2.ttf", 32);
    menuLabel->setColor(Color3B(61, 10, 10));
    return menuLabel;
}
