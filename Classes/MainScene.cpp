#include "MainScene.h"

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

    //Resolving game mode
    int gameMode = UserDefault::getInstance()->getIntegerForKey("GAME_MODE");
    assert(SINGLE_PLAYER <= gameMode && gameMode <= LOCAL_4_PLAYER);
    switch (gameMode) {
        case SINGLE_PLAYER:
            board = new Board(this, 2);
            game = new SinglePlayer(board);
            break;
        case ONLINE_MULTI_PLAYER:
            board = new Board(this, 4);
            game = new OnlineMultiPlayer(board);
            break;
        case LOCAL_2_PLAYER:
            board = new Board(this, 2);
            game = new LocalMultiPlayer(board, 2);
            break;
        case LOCAL_3_PLAYER:
            board = new Board(this, 3);
            game = new LocalMultiPlayer(board, 3);
            break;
        case LOCAL_4_PLAYER:
            board = new Board(this, 4);
            game = new LocalMultiPlayer(board, 4);
            break;
    }

    //Adding mouse events
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    //Adding menu
    auto Play = MenuItemLabel::create(board->createMenuLabel("Pass"), CC_CALLBACK_1(MainScene::passStep, this));
    auto Exit = MenuItemLabel::create(board->createMenuLabel("Surrender"),
                                      CC_CALLBACK_1(MainScene::GoToGameOver, this));
    board->placeMenuLabel(Play, 1);
    board->placeMenuLabel(Exit, 2);

    return true;

}

bool MainScene::onTouchBegan(Touch *touch, Event *event) {
        //Идет подключение к серверу - касания не работают
    if (game->gamestatus() == PLAYER_CONNECTING) {
        return true;
    }
        //Конец игры
    else if (game->gamestatus() != GAME_GOING) {
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

void MainScene::GoToGameOver(cocos2d::Ref *sender) {
    std::string str = game->getScore();
    UserDefault::getInstance()->setStringForKey("PLAYER_SCORE", str);

    auto scene = GameOver::createScene();
    delete game;
    delete board;
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainScene::passStep(Ref *sender) {
    game->passStep();
}
