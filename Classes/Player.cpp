//
// Created by pavelgolubev345 on 23.03.16.
//

#include "Player.h"

int Player::playerAmount = 0;

Player::Player() : score(0) {
    playerNumber = playerAmount;
    switch (playerNumber) {
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

std::string Player::getChipPath() const {
    return chipPath;
}

void Player::setPlayerAmount(int amount){
    playerAmount = amount;
}
