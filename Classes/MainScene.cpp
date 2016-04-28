#include "MainScene.h"


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

    //Resolving game mode
    int gameMode = UserDefault::getInstance()->getIntegerForKey("GAME_MODE");
    assert(SINGLE_PLAYER <= gameMode && gameMode <= LOCAL_4_PLAYER);

    board = GameFactory::makeBoard(this, gameMode);
    game = GameFactory::makeGame(this, gameMode);

    //Adding mouse events
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    return true;

}

bool MainScene::onTouchBegan(Touch *touch, Event *event) {
    //Идет подключение к серверу - касания не работают
    if (game->gamestatus() == PLAYER_CONNECTING) {
        return true;
    }
        //Конец игры
    else if (game->gamestatus() == GAME_OVER || game->gamestatus() == PLAYER_SURRENDERED) {
        GoToGameOver(this);
        return true;
    }
        //Игрок не может ходить
    else if (game->isLocked()) {
        std::cout << "Locked" << std::endl;
        return true;
    }

    //Вычисляем по координатам касания X и Y доски
    std::pair<int, int> XY = board->mousePositionToXY(touch->getLocation());

    //Игрок нажал не на поле
    if (0 > XY.first || XY.first > 18 || 0 > XY.second || XY.second > 18) {
        return true;
    }
        //Передаем координаты модели игры
    else {
        game->getXY(XY.first, XY.second);
        return true;
    }
}

void MainScene::surrender(Ref *sender) {
    game->performGameOver();
    board->displayAlert(GAME_OVER);
}


void MainScene::GoToGameOver(cocos2d::Ref *sender) {

    std::string str = game->getScore();
    UserDefault::getInstance()->setStringForKey("PLAYER_SCORE", str);

    auto scene = GameOver::createScene();
    board->removeAlert();
    delete game;
    delete board;
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainScene::passStep(Ref *sender) {
    game->passStep();
}

void MainScene::placeChip(int X, int Y, int team) {
    board->placeChip(X, Y, team);
}

void MainScene::removeChip(int X, int Y) {
    board->removeChip(X, Y);

}

void MainScene::displayAlert(int status) {
    board->displayAlert(status);
}

void MainScene::removeAlert() {
    board->removeAlert();
}
