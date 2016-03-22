#include "HelloWorldScene.h"

USING_NS_CC;

Scene *HelloWorld::createScene() {
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
bool HelloWorld::init() {

    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    board.getBoardSprite()->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(board.getBoardSprite());

    auto listener1 = EventListenerTouchOneByOne::create();

    listener1->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);


    return true;
}


bool HelloWorld::placeChip(int X, int Y, int team) {
    if (X < 0 || X > 18 || Y < 0 || Y > 18 || team < 0 || team > PLAYER_AMOUNT) {
        std::cout << "Error - Invalid args (" << X << ", " << Y << ", " << team << ") for placeChip()" << std::endl;
        return false;
    }

    if (board.checkStep(X, Y, team)) {
        auto chip = Sprite::create("chip.png");
        chip->setScale(CHIP_SCALE);

        //Здесь надо просчитать координаты фишки которая должна поставиться на доску с координатой (X,Y)
        chip->setPosition(
                Vec2(board.getBoardSprite()->getPositionX() +
                     (board.getBoardSprite()->getBoundingBox().size.width - 100 * BOARD_SCALE) / 18 * (X - 9),
                     board.getBoardSprite()->getPositionY() +
                     (board.getBoardSprite()->getBoundingBox().size.height - 100 * BOARD_SCALE) / 18 * (9 - Y)));
        //

        chip->setTag(X * 10 + Y);
        switch (team) {
            case 2:
                chip->setColor(Color3B::BLACK);
                break;
            case 3:
                chip->setColor(Color3B::GRAY);
                break;
        }
        this->addChild(chip);
        board.boardAt(X, Y) = team;
        return true;
    } else {
        std::cout << "Error - Cannot place (" << X << ", " << Y << ", " << team <<
        ") on the board. Chip already exit" << std::endl;
        return false;
    }
}

void HelloWorld::removeChip(int X, int Y) {
    if (X < 0 || X > 18 || Y < 0 || Y > 18) {
        std::cout << "Error - Invalid args (" << X << ", " << Y << ") for removeChip()" << std::endl;
        return;
    }
    if (this->getChildByTag(X * 10 + Y)) {
        this->removeChildByTag(X * 10 + Y);
    } else {
        std::cout << "Warning - removing a chip (" << X << ", " << Y << ") what do not exist" << std::endl;
    }
}


bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {
    int X = rand()%19, Y = rand()%19, team = 1 + rand()%3;

    Vec2 vector = touch->getLocation();
    //Здесь очередная магия с координатами - нужно зная координату касания (vector) вычислить позицию на доске
    // (X,Y) ближайшую к ней
    placeChip(X,Y,team);
    return true;
}
