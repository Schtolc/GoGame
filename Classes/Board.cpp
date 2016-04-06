//
// Created by pavelgolubev345 on 21.03.16.
//

#include "Board.h"

Board::Board(Layer *layer, int playerAmount) {
    assert(layer != NULL && 2<=playerAmount && playerAmount<=4);
    Board::layer = layer;

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    //Adding board sprite
    boardSprite = Sprite::create("board.png");
    boardSprite->setScale(BOARD_SCALE);
    boardSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    layer->addChild(boardSprite, 1);

    //Adding background
    auto backgroundSprite = Sprite::create("background.jpg");
    backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
    backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    layer->addChild(backgroundSprite, 0);

    //Adding scores
    scores = new Label*[playerAmount];
    for (int i =0 ; i < playerAmount; i++) {
        scores[i] = Label::createWithTTF("p" + std::to_string(i+1) + ": 0", "fonts/go3v2.ttf", 32);
        scores[i]->setPosition(Point(visibleSize.width / (playerAmount+1) * (i + 1),
                                     visibleSize.height - scores[i]->getContentSize().height / 2));
        layer->addChild(scores[i], 1);
    }

    //Adding menu
    menu = Menu::create();
    menu->setPosition(Point::ZERO);
    layer->addChild(menu);

}


void Board::placeChip(int X, int Y, int team) {

    //Проверяем ошибки входных данных
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    assert (team >= 0 && team <= 4);

    //Добавляем спрайт фишки. Здесь можно поизменять CHIP_SCALE чтобы нормальный размер доски был
    std::string chipPath;
    switch (team) {
        case 0:
            chipPath = "white_chip.png";
            break;
        case 1:
            chipPath = "black_chip.png";
            break;
        case 2:
            chipPath = "gray_chip.png";
            break;
        case 3:
            chipPath = "yellow_chip.png";
            break;
        default:
            std::cout << "Chip path failed" << std::endl;
    }

    auto chip = Sprite::create(chipPath);

    //Здесь надо просчитать координаты фишки которая должна поставиться на доску с координатой (X,Y)
    Vec2 pos(Vec2(boardSprite->getContentSize().width / 32 +
                  ((boardSprite->getContentSize().width -
                    boardSprite->getContentSize().width / 16) / 18 * (X)),
                  boardSprite->getContentSize().height / 32 +
                  ((boardSprite->getContentSize().height -
                    boardSprite->getContentSize().height / 16) / 18 * (Y))));


    //Параметры фишки
    chip->setPosition(pos);
    chip->setTag(X * 10 + Y);
    boardSprite->addChild(chip);
}

void Board::removeChip(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    layer->removeChildByTag(X * 10 + Y);
}

std::pair<int, int> Board::mousePositionToXY(Vec2 coordinates) {

    int X = (coordinates.x +
             (boardSprite->getContentSize().width - boardSprite->getContentSize().width / 16) / 36 *
             BOARD_SCALE - boardSprite->getPositionX() +
             boardSprite->getContentSize().width / 2 * BOARD_SCALE -
             boardSprite->getContentSize().width / 32 * BOARD_SCALE) * 18 /
            (boardSprite->getContentSize().width * BOARD_SCALE -
             boardSprite->getContentSize().width / 16 * BOARD_SCALE);


    int Y = (coordinates.y +
             (boardSprite->getContentSize().height - boardSprite->getContentSize().height / 16) / 36 *
             BOARD_SCALE - boardSprite->getPositionY() +
             boardSprite->getContentSize().height / 2 * BOARD_SCALE -
             boardSprite->getContentSize().height / 32 * BOARD_SCALE) * 18 /
            (boardSprite->getContentSize().height * BOARD_SCALE -
             boardSprite->getContentSize().height / 16 * BOARD_SCALE);

    return std::pair<int, int>(X, Y);
}

Layer *Board::getLayel() const {
    return layer;
}

void Board::displayScore(int score, int team) {
    assert(0<=team && team <=3);
    scores[team]->setString("p" + std::to_string(team+1) + ": " + std::to_string(score));
}

void Board::displayAlert(int status) {
    assert(GAME_OVER <= status && status <=PLAYER_CONNECTING);
    std::string alert;
    switch (status) {
        case SERVER_FULL:
            alert = "Server is full\n";
            break;
        case GAME_OVER:
            alert = "Game over\n";
            break;
        case PLAYER_SURRENDERED:
            alert = "Player surrendered\n";
            break;
        case PLAYER_CONNECTING:
            alert = "Waiting for other players";
            break;
    }

    if (status!=PLAYER_CONNECTING)
        alert+=std::string("touch to continue");

    auto alertLabel = Label::createWithTTF(alert , "fonts/go3v2.ttf", 72);
    alertLabel->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    alertLabel->setTag(ALERT_MESSAGE);
    layer->addChild(alertLabel,1);
}

void Board::removeAlert() {
    layer->removeChildByTag(ALERT_MESSAGE);
}

Label *Board::createMenuLabel(std::string title) {
    assert(title != "");
    auto menuLabel = Label::createWithTTF(title, "fonts/go3v2.ttf", 32);
    menuLabel->setColor(Color3B(61, 10, 10));
    return menuLabel;
}


void Board::placeMenuLabel(MenuItemLabel *menuLabel, const int X) {
    assert(1 <= X && X <= 2 && menuLabel!= nullptr);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    menuLabel->setPosition(Point(origin.x + visibleSize.width / 3 * X - menuLabel->getContentSize().width / 2,
                            origin.y + menuLabel->getContentSize().height / 2));
    menu->addChild(menuLabel);
}
