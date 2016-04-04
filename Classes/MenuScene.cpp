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

    auto title = Label::createWithTTF("GoGame", "fonts/go3v2.ttf", 128);
    title->setPosition(
            Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - title->getContentSize().height));
    this->addChild(title, 1);

    MainMenu = Menu::create(NULL);
    MainMenu->setPosition(Point::ZERO);
    this->addChild(MainMenu);
    showPlayMenu(NULL);
    return true;
}

Label *MenuScene::createMenuLabel(std::string title) {
    auto menuLabel = Label::createWithTTF(title, "fonts/go3v2.ttf", 64);
    menuLabel->setColor(Color3B(61, 10, 10));
    return menuLabel;
}


void MenuScene::showPlayMenu(cocos2d::Ref *sender) {
    MainMenu->removeAllChildren();

    auto Play = MenuItemLabel::create(createMenuLabel("Play"), CC_CALLBACK_1(MenuScene::showGameModesMenu, this));
    Play->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 4));

    auto Exit = MenuItemLabel::create(createMenuLabel("Exit"), CC_CALLBACK_1(MenuScene::menuClose, this));
    Exit->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 3));

    MainMenu->addChild(Play);
    MainMenu->addChild(Exit);
}


void MenuScene::showGameModesMenu(cocos2d::Ref *sender) {
    MainMenu->removeAllChildren();

    auto single = MenuItemLabel::create(createMenuLabel("Single player"),
                                        CC_CALLBACK_1(MenuScene::GoToGameScene, this, SINGLE_PLAYER));
    single->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 4));

    auto local = MenuItemLabel::create(createMenuLabel("Local Multiplayer"),
                                       CC_CALLBACK_1(MenuScene::showPlayersAmountMenu, this));
    local->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 3));

    auto online = MenuItemLabel::create(createMenuLabel("Online Multiplayer"),
                                        CC_CALLBACK_1(MenuScene::GoToGameScene, this, ONLINE_MULTI_PLAYER));
    online->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 2));

    auto back = MenuItemLabel::create(createMenuLabel("back"),
                                        CC_CALLBACK_1(MenuScene::showPlayMenu, this));
    back->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 1));

    MainMenu->addChild(single);
    MainMenu->addChild(local);
    MainMenu->addChild(online);
    MainMenu->addChild(back);
}

void MenuScene::showPlayersAmountMenu(cocos2d::Ref *sender) {
    MainMenu->removeAllChildren();

    auto player2 = MenuItemLabel::create(createMenuLabel("2 players"),
                                         CC_CALLBACK_1(MenuScene::GoToGameScene, this, LOCAL_2_PLAYER));
    player2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 4));

    auto player3 = MenuItemLabel::create(createMenuLabel("3 players"),
                                         CC_CALLBACK_1(MenuScene::GoToGameScene, this, LOCAL_3_PLAYER));
    player3->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 3));

    auto player4 = MenuItemLabel::create(createMenuLabel("4 players"),
                                         CC_CALLBACK_1(MenuScene::GoToGameScene, this, LOCAL_4_PLAYER));
    player4->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 2));

    auto back = MenuItemLabel::create(createMenuLabel("back"),
                                      CC_CALLBACK_1(MenuScene::showGameModesMenu, this));
    back->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 1));

    MainMenu->addChild(player2);
    MainMenu->addChild(player3);
    MainMenu->addChild(player4);
    MainMenu->addChild(back);
}

void MenuScene::GoToGameScene(cocos2d::Ref *sender, const int gameMode) {
    assert(SINGLE_PLAYER <= gameMode && gameMode <= LOCAL_4_PLAYER);
    UserDefault::getInstance()->setIntegerForKey("GAME_MODE", gameMode);
//    UserDefault::getInstance()->flush();
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MenuScene::menuClose(cocos2d::Ref *sender) {
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

