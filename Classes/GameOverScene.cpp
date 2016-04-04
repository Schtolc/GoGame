#include "GameOverScene.h"
#include "Defenitions.h"
#include "MenuScene.h"
#include "Player.h"

Scene *GameOver::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Background initialization
    auto backgroundSprite = Sprite::create("background.jpg");
    backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
    backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    auto title = Label::createWithTTF("Game Over", "fonts/go3v2.ttf", 64);
    title->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 10 * 9));
    this->addChild(title, 1);

    //Score displaying
    auto score = Label::createWithTTF(UserDefault::getInstance()->getStringForKey("PLAYER_SCORE"), "fonts/go3v2.ttf",
                                      32);
    score->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 10 * 5));
    this->addChild(score, 1);

    //Menu initialization
    auto menuItem = MenuItemLabel::create(createMenuLabel("Main Menu"), CC_CALLBACK_1(GameOver::GoToGameScene, this));
    menuItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 3));

    auto exitItem = MenuItemLabel::create(createMenuLabel("Exit"), CC_CALLBACK_1(GameOver::menuCloseCallback, this));
    exitItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 2));

    auto menu = Menu::create(menuItem, exitItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);

    return true;
}

Label *GameOver::createMenuLabel(std::string title) {
    auto menuLabel = Label::createWithTTF(title, "fonts/go3v2.ttf", 64);
    menuLabel->setColor(Color3B(61, 10, 10));
    return menuLabel;
}

void GameOver::GoToGameScene(cocos2d::Ref *sender) {
    auto scene = MenuScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOver::menuCloseCallback(Ref *pSender) {
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


