//
// Created by pavelgolubev345 on 21.03.16.
//

#include "Board.h"

Board::Board(Layer *layer, Size size, Vec2 vector) : boardLayer(layer), visibleSize(size), origin(vector) {
    if (layer == NULL) {
        std::cout << "Error - Board layer is uninitialized" << std::endl;
    }

    memset(matrix, EMPTY_CELL, sizeof(int) * BOARD_SIZE * BOARD_SIZE);
    boardSprite = Sprite::create("board.png");
    boardSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    boardSprite->setScale(0.4);
    layer->addChild(boardSprite);
}

void Board::placeChip(int X, int Y, int team) {
    if (X < 0 || X > 18 || Y < 0 || Y > 18 || team < 0 || team > 3) {
        std::cout << "Error - Invalid args (" << X << ", " << Y << ", " << team << ") for placeChip()" << std::endl;
        return;
    }

    if (checkStep(X, Y, team)) {
        auto chip = Sprite::create("chip.png");
        chip->setScale(CHIP_SCALE);
        chip->setPosition(
                Vec2(boardSprite->getPositionX() +
                     (boardSprite->getBoundingBox().size.width - 100 * BOARD_SCALE) / 18 * (X-9),
                     boardSprite->getPositionY() +
                     (boardSprite->getBoundingBox().size.height - 100 * BOARD_SCALE) / 18 * (9-Y)));
        chip->setTag(X * 10 + Y);
        switch (team) {
            case B_CELL:
                chip->setColor(Color3B::BLACK);
                break;
            case C_CELL:
                chip->setColor(Color3B::GRAY);
                break;
        }
        boardLayer->addChild(chip);
    } else {
        std::cout << "Error - Cannot place (" << X << ", " << Y << ", " << team << ") on the board" << std::endl;
    }
}

bool Board::checkStep(int X, int Y, int team) {

    //Добавить логику
    if(matrix[X][Y] != 0)
        return false;
    return true;
}

void Board::removeChip(int X, int Y) {
    if (X < 0 || X > 18 || Y < 0 || Y > 18) {
        std::cout << "Error - Invalid args (" << X << ", " << Y << ") for removeChip()" << std::endl;
        return;
    }
    if (boardLayer->getChildByTag(X * 10 + Y)) {
        boardLayer->removeChildByTag(X * 10 + Y);
    } else {
        std::cout << "Warning - removing a chip (" << X << ", " << Y << ") what do not exist" << std::endl;
    }
}
