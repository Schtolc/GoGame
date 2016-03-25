#include "PlayerMenuScene.h"
#include "MainScene.h"
#include "Defenitions.h"

USING_NS_CC;

Scene *PlayerMenu::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = PlayerMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayerMenu::init() {
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

    auto title = LabelTTF::create("GoGame", "fonts/go3v2.ttf", 128);
    title->setPosition(
            Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - title->getContentSize().height));

    this->addChild(title, 1);

    //Menu initialization
    cocos2d::Label *playerTtfs[PLAYER_AMOUNT] = {
            Label::createWithTTF("1 player", "fonts/go3v2.ttf", 64),
            Label::createWithTTF("2 player", "fonts/go3v2.ttf", 64),
            Label::createWithTTF("3 player", "fonts/go3v2.ttf", 64),
            Label::createWithTTF("4 player", "fonts/go3v2.ttf", 64),
    };
    for (int i = 0; i < PLAYER_AMOUNT; i++) {
        playerTtfs[i]->setColor(Color3B(61, 10, 10));
    }

    cocos2d::MenuItemLabel *playerLabels[PLAYER_AMOUNT] = {
            MenuItemLabel::create(playerTtfs[0], CC_CALLBACK_1(PlayerMenu::GoToGameScene, this, 1)),
            MenuItemLabel::create(playerTtfs[1], CC_CALLBACK_1(PlayerMenu::GoToGameScene, this, 2)),
            MenuItemLabel::create(playerTtfs[2], CC_CALLBACK_1(PlayerMenu::GoToGameScene, this, 3)),
            MenuItemLabel::create(playerTtfs[3], CC_CALLBACK_1(PlayerMenu::GoToGameScene, this, 4))
    };
    for (int i = 0; i < PLAYER_AMOUNT; i++) {
        playerLabels[i]->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 10 * (5 - i)));
    }

    auto menu = Menu::create(playerLabels[0], playerLabels[1], playerLabels[2], playerLabels[3], NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    return true;
}

void PlayerMenu::GoToGameScene(cocos2d::Ref *sender, const int amount) {
    assert(0 < amount && amount <= PLAYER_AMOUNT);
    UserDefault::getInstance()->setIntegerForKey("PLAYER_AMOUNT", amount);
    UserDefault::getInstance()->flush();
    auto scene = MainScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}



