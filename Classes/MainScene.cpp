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
    listener1->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, game);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    return true;

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

void MainScene::surrender(Ref *sender) {
    game->surrender();
}

void MainScene::passStep(Ref *sender) {
    game->passStep();
}

std::pair<int, int> MainScene::mousePositionToXY(Vec2 coordinates) {
    return board->mousePositionToXY(coordinates);
}

void MainScene::GoToGameOver(cocos2d::Ref *sender) {

    UserDefault::getInstance()->setStringForKey("PLAYER_SCORE",game->getScore());

    auto scene = GameOver::createScene();
    removeAlert();

    delete game;
    delete board;
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

