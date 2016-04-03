#include "MainScene.h"
#include "string"

USING_NS_CC;


Scene *MainScene::createScene() {

    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool MainScene::init() {

    if (!Layer::init()) {
        return false;
    }

    board.init(this);
//    game = new LocalMultiPlayer(&board, 4);
//    game = new SinglePlayer(&board);
    game = new OnlineMultiPlayer(&board);


//    auto f = CC_CALLBACK_0(MainScene::sync,this);
//    this->schedule(schedule_selector(MainScene::sync), 2);
    //Adding mouse events
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    return true;

}

bool MainScene::onTouchBegan(Touch *touch, Event *event) {
    Vec2 mousePosition = touch->getLocation();
    std::pair<int, int> XY = board.mousePositionToXY(mousePosition);
    if (0 > XY.first || XY.first > 18 || 0 > XY.second || XY.second > 18) {
        return true;
    } else if (game->isLocked()) {
        std::cout << "Locked" << std::endl;
        return true;
    }
    else {
        game->getXY(XY.first, XY.second);
        return true;
    }
}

void MainScene::GoToGameOver(cocos2d::Ref *sender) {
    /*std::string str = "";
    for (int i = 0; i < playerAmount; i++) {
        str += "Player " + std::to_string(i + 1) + " score: " + std::to_string(players[i].getScore()) + "\n";
    }
    UserDefault::getInstance()->setStringForKey("PLAYER_SCORE", str);
    UserDefault::getInstance()->flush();
    auto scene = GameOver::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));*/
}

