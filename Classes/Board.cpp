//
// Created by pavelgolubev345 on 21.03.16.
//

#include "Board.h"

Board::Board() { }

void Board::init(Layer *layer) {
    assert(layer != NULL);
    Board::layer = layer;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

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
    chip->setScale(CHIP_SCALE);

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
