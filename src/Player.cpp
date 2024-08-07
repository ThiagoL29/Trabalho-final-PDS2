#include "Player.h"

#include <iostream>

Player::Player(std::string name, std::string nickname): name(name), nickame(nickname) {
    numOfVictoriesLig4 = numOfLossesLig4 = numOfVictoriesReversi = numOfLossesReversi = 0;
    isDeleted = false;
}

std::string Player::getName() const {
    return this->name;
}

std::string Player::getNickname() const {
    return this->nickame;
}

bool Player::getUserStatus() const {
    return this->isDeleted;
}

void Player::removePlayer() {
    this->isDeleted = true;
}

void Player::updateName(std::string newName) {
    this->name = newName;
}

void Player::updateNickName(std::string newNickname) {
    this->nickame = newNickname;
}

void Player::updateLig4PlayerStats(int numOfVictoriesLig4, int numOfLossesLig4) {
    this->numOfVictoriesLig4 = numOfVictoriesLig4;
    this->numOfLossesLig4 = numOfLossesLig4;
}

void Player::updateReversiPlayerStats(int numOfVictoriesReversi, int numOfLossesReversi) {
    this->numOfVictoriesReversi = numOfVictoriesReversi;
    this->numOfLossesReversi = numOfLossesReversi;
}
