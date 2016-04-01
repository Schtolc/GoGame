//
// Created by pavelgolubev345 on 23.03.16.
//

#include "Player.h"


Player::Player() : score(0), playerTeam(0) {
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int score) {
    assert(score >= 0);
    Player::score = score;
}

int Player::team() const {
    return playerTeam;
}

void Player::setTeam(int num) {
    assert(0 <= num && num < PLAYER_AMOUNT);
    playerTeam = num;
}

std::string Player::getChipPath() const {
    return chipPath;
}

