#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("GoGame", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    auto sprite = Sprite::create("/home/pavelgolubev345/Downloads/board.png");

    sprite->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2));
    sprite->setScale(0.4);
    this->addChild(sprite);

    auto chip = Sprite::create("/home/pavelgolubev345/Downloads/chip.png");
    chip->setScale(0.1);
    chip->setPosition(Vec2(sprite->getPositionX()  - (sprite->getBoundingBox().size.width- 100*0.4)/18*4, sprite->getPositionY() +
            (sprite->getBoundingBox().size.height-  100*0.4)/18*4));

    this->addChild(chip,2);

    auto bchip = Sprite::create("/home/pavelgolubev345/Downloads/chip.png");
    bchip->setScale(0.1);
    bchip->setPosition(Vec2(sprite->getPositionX()  + (sprite->getBoundingBox().size.width- 100*0.4)/18*7,
                            sprite->getPositionY() - (sprite->getBoundingBox().size.height-  100*0.4)/18*2));


    bchip->setColor(Color3B(0,0,0));
    this->addChild(bchip,2);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
