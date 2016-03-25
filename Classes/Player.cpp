//
// Created by pavelgolubev345 on 23.03.16.
//

#include "Player.h"

int Player::playerAmount = 0;

Player::Player() : score(0) {
    playerNumber = playerAmount;
    switch (playerNumber) {
        case 0:
            chipColor = Color3B::WHITE;
            break;
        case 1:
            chipColor = Color3B::BLACK;
            break;
        case 2:
            chipColor = Color3B::GRAY;
            break;
        case 3:
            chipColor = Color3B::BLUE;
            break;
    }
    playerAmount++;
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int score) {
    assert(score >= 0);
    Player::score = score;
}

int Player::getPlayerNumber() const {
    return playerNumber;
}

void Player::setPlayerNumber(int num) {
    assert(0 <= num && num < PLAYER_AMOUNT);
    playerNumber = num;
}

Color3B Player::getChipColor() const {
    return chipColor;
}