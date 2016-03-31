#include "MainMenuScene.h"
#include "PlayerMenuScene.h"
#include "Defenitions.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Background initialization
    auto backgroundSprite = Sprite::create( "background.jpg" );
    backgroundSprite->setScaleX(visibleSize.width/backgroundSprite->getContentSize().width);
    backgroundSprite->setScaleY(visibleSize.height/backgroundSprite->getContentSize().height);
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    this->addChild( backgroundSprite );
    
    auto title = Label::createWithTTF("GoGame", "fonts/go3v2.ttf", 128);
    title->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - title->getContentSize().height));
    this->addChild(title,1);

    //Menu initialization
    auto newGameLabel = Label::createWithTTF("NewGame", "fonts/go3v2.ttf", 64);
    newGameLabel->setColor(Color3B(61,10,10));
    auto newGameItem = MenuItemLabel::create(newGameLabel, CC_CALLBACK_1( MainMenu::GoToGameScene, this ) );
    newGameItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 10 * 3 ) );

    auto exitLabel = Label::createWithTTF("Exit", "fonts/go3v2.ttf", 64);
    exitLabel->setColor(Color3B(61,10,10));
    auto exitItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1( MainMenu::menuCloseCallback, this ) );
    exitItem->setPosition( Point( visibleSize.width / 2 + origin.x,  visibleSize.height / 10 * 2) );

    auto menu = Menu::create( newGameItem, exitItem, NULL );
    menu->setPosition( Point::ZERO );
    
    this->addChild( menu );
    
    return true;
}

void MainMenu::GoToGameScene( cocos2d::Ref *sender )
{
    auto scene = PlayerMenu::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


