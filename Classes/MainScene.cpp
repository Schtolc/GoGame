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


    //Scene initialization
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    playerAmount = UserDefault::getInstance()->getIntegerForKey("PLAYER_AMOUNT");
    players = new Player[playerAmount]();
    currentPlayer = &players[0];

    //Adding background
    auto backgroundSprite = Sprite::create("background.jpg");
    backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
    backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    //Adding board sprite
    board.getBoardSprite()->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(board.getBoardSprite());

    //Adding mouse events
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);


    return true;
}


bool MainScene::placeChip(int X, int Y) {

    //Проверяем ошибки входных данных
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);

    //Проверяем возможность поставить фишку на доску
    if (board.checkStep(X, Y, currentPlayer->getPlayerNumber())) {

        //Добавляем спрайт фишки. Здесь можно поизменять CHIP_SCALE чтобы нормальный размер доски был
        auto chip = Sprite::create("chip.png");
        chip->setScale(CHIP_SCALE);

        //Здесь надо просчитать координаты фишки которая должна поставиться на доску с координатой (X,Y)
        Vec2 pos(Vec2(board.getBoardSprite()->getPositionX() +
                      (board.getBoardSprite()->getBoundingBox().size.width - 100 * BOARD_SCALE) / 18 * (X - 9),
                      board.getBoardSprite()->getPositionY() +
                      (board.getBoardSprite()->getBoundingBox().size.height - 100 * BOARD_SCALE) / 18 * (9 - Y)));

        //Параметры фишки
        chip->setPosition(pos);
        chip->setTag(X * 10 + Y);
        chip->setColor(currentPlayer->getChipColor());
        this->addChild(chip);

        //Взаимодействуем с матрицей доски
        board.boardAt(X, Y) = currentPlayer->getPlayerNumber();
        update();
        return true;
    }
    else {

        //Предупреждение если попытка поставить в недопустимое место
        std::cout << "Warning - Cannot place (" << X << ", " << Y << ", " << currentPlayer->getPlayerNumber() <<
        ") on the board." << std::endl;
        return false;
    }
}

void MainScene::removeChip(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);

    if (this->getChildByTag(X * 10 + Y)) {
        this->removeChildByTag(X * 10 + Y);
    } else {
        std::cout << "removing a Chip that do not exist" << std::endl;
    }
}


bool MainScene::onTouchBegan(Touch *touch, Event *event) {
    int X = 0, Y = 0;
    Vec2 vector = touch->getLocation();

    //Здесь очередная магия с координатами - нужно зная координату касания (vector) вычислить позицию на доске
    // (X,Y) ближайшую к ней
    X = (vector.x - board.getBoardSprite()->getPositionX() -
         (board.getBoardSprite()->getBoundingBox().size.width - 100 * BOARD_SCALE) / 18 * 0.5) * 18 /
        (board.getBoardSprite()->getBoundingBox().size.width - 100 * BOARD_SCALE) + 10;
    Y = (vector.y - board.getBoardSprite()->getPositionY() -
         (board.getBoardSprite()->getBoundingBox().size.height - 100 * BOARD_SCALE) / 18 * 0.5) * 18 /
        (board.getBoardSprite()->getBoundingBox().size.height - 100 * BOARD_SCALE) - 9;
    Y = -Y;
    placeChip(X, Y);
    return true;
}

void MainScene::update() {

    //Здесь надо изменять счет игррока в зависимости от поля и удалять фишки (removeChip)
    //с доски если их съели. Также эта функция меняют сцену на чцену конца игры если игра окончена
    //Так же необходимо менять текущего игрока - это я реализовал ниже
    currentPlayer->setScore(100);
    if (currentPlayer->getPlayerNumber() == playerAmount - 1) {
        currentPlayer = &players[0];
    } else
        currentPlayer++;
    //GoToGameOver(this);

}

void MainScene::GoToGameOver(cocos2d::Ref *sender) {
    std::string str = "";
    for (int i = 0; i < playerAmount; i++) {
        str += "Player " + std::to_string(i+1)+ " score: " + std::to_string(players[i].getScore()) + "\n";
    }
    UserDefault::getInstance()->setStringForKey("PLAYER_SCORE", str);
    UserDefault::getInstance()->flush();
    auto scene = GameOver::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}