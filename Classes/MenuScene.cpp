//
// Created by pavelgolubev345 on 04.04.16.
//

#include "MenuScene.h"

Scene *MenuScene::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    //Background initialization
    auto backgroundSprite = Sprite::create("background.jpg");
    backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
    backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    //GoGameLogic title initialization
    auto title = Label::createWithTTF("GoGameLogic", "fonts/go3v2.ttf", 128);
    title->setPosition(
            Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - title->getContentSize().height));
    this->addChild(title, 1);

    //Menu initialization
    menu = Menu::create();
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    //Calling main menu
    showMainMenu(NULL);

    return true;
}

void MenuScene::showMainMenu(cocos2d::Ref *sender) {
    menu->removeAllChildren();

    auto play = MenuItemLabel::create(createMenuLabel("Play"),
                                              CC_CALLBACK_1(MenuScene::showGameModesMenu, this));
    auto exitGame = MenuItemLabel::create(createMenuLabel("Exit"), CC_CALLBACK_1(MenuScene::gameExit, this));

    placeMenuLabel(play, 4);
    placeMenuLabel(exitGame, 3);
}

void MenuScene::showGameModesMenu(cocos2d::Ref *sender) {
    menu->removeAllChildren();

    auto single = MenuItemLabel::create(createMenuLabel("Single player"),
                                        CC_CALLBACK_1(MenuScene::GoToGameScene, this, SINGLE_PLAYER));
    auto local = MenuItemLabel::create(createMenuLabel("Local Multiplayer"),
                                       CC_CALLBACK_1(MenuScene::showLocalMultiplayerMenu, this));
    auto online = MenuItemLabel::create(createMenuLabel("Online Multiplayer"),
                                        CC_CALLBACK_1(MenuScene::GoToGameScene, this, ONLINE_MULTI_PLAYER));
    auto back = MenuItemLabel::create(createMenuLabel("back"),
                                      CC_CALLBACK_1(MenuScene::showMainMenu, this));

    placeMenuLabel(single, 4);
    placeMenuLabel(local, 3);
    placeMenuLabel(online, 2);
    placeMenuLabel(back, 1);
}

void MenuScene::showLocalMultiplayerMenu(cocos2d::Ref *sender) {
    menu->removeAllChildren();

    auto player2 = MenuItemLabel::create(createMenuLabel("2 players"),
                                         CC_CALLBACK_1(MenuScene::GoToGameScene, this, LOCAL_2_PLAYER));
    auto player3 = MenuItemLabel::create(createMenuLabel("3 players"),
                                         CC_CALLBACK_1(MenuScene::GoToGameScene, this, LOCAL_3_PLAYER));
    auto player4 = MenuItemLabel::create(createMenuLabel("4 players"),
                                         CC_CALLBACK_1(MenuScene::GoToGameScene, this, LOCAL_4_PLAYER));
    auto back = MenuItemLabel::create(createMenuLabel("back"),
                                      CC_CALLBACK_1(MenuScene::showGameModesMenu, this));
    placeMenuLabel(player2, 4);
    placeMenuLabel(player3, 3);
    placeMenuLabel(player4, 2);
    placeMenuLabel(back, 1);

}

void MenuScene::GoToGameScene(cocos2d::Ref *sender, const int gameMode) {

    UserDefault::getInstance()->setIntegerForKey("GAME_MODE", gameMode);

    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MenuScene::gameExit(cocos2d::Ref *sender) const {
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

Label *MenuScene::createMenuLabel(std::string title) {
    assert(title != "");
    auto menuLabel = Label::createWithTTF(title, "fonts/go3v2.ttf", 64);
    menuLabel->setColor(Color3B(61, 10, 10));
    return menuLabel;
}


void MenuScene::placeMenuLabel(MenuItemLabel *menuLabel, const int Y) {
    assert(0 <= Y && Y <= 10);
    menuLabel->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 10 * Y));
    menu->addChild(menuLabel);
}
