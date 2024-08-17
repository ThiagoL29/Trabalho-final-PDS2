#include "Player.h"
#include "Utilities.h"
#include <iostream>

Player::Player()
    : name(""), nickame("") {
  numOfVictoriesLig4 = numOfLossesLig4 = numOfVictoriesReversi =
      numOfLossesReversi = 0;
}

Player::Player(std::string name, std::string nickname)
    : name(toLower(name)), nickame(toLower(nickname)) {
  numOfVictoriesLig4 = numOfLossesLig4 = numOfVictoriesReversi =
      numOfLossesReversi = 0;
}

Player::Player(std::string name, std::string nickname, int numOfVictoriesLig4,
               int numOfLossesLig4, int numOfVictoriesReversi,
               int numOfLossesReversi)
    : name(toLower(name)), nickame(toLower(nickname)),
      numOfVictoriesLig4(numOfVictoriesLig4), numOfLossesLig4(numOfLossesLig4),
      numOfVictoriesReversi(numOfVictoriesReversi),
      numOfLossesReversi(numOfLossesReversi) {}

std::string Player::getName() const { return this->name; }

std::string Player::getNickname() const { return this->nickame; }

int Player::getNumOfVictoriesLig4() const { return this->numOfVictoriesLig4; }
int Player::getNumOfLossesLig4() const { return this->numOfLossesLig4; }
int Player::getNumOfVictoriesReversi() const {
  return this->numOfVictoriesReversi;
}
int Player::getNumOfLossesReversi() const { return this->numOfLossesReversi; }

void Player::updateName(std::string newName) { this->name = newName; }

void Player::updateNickName(std::string newNickname) {
  this->nickame = newNickname;
}

void Player::updateLig4PlayerStats(int numOfVictoriesLig4,
                                   int numOfLossesLig4) {
    if(numOfVictoriesLig4 < 0 || numOfLossesLig4 < 0) {
        throw std::out_of_range("Número de vitórias e derrotas devem ser positivos.");
    }
  this->numOfVictoriesLig4 = numOfVictoriesLig4;
  this->numOfLossesLig4 = numOfLossesLig4;
}

void Player::updateReversiPlayerStats(int numOfVictoriesReversi,
                                      int numOfLossesReversi) {

    if(numOfVictoriesReversi < 0 || numOfLossesReversi < 0) {
        throw std::out_of_range("Número de vitórias e derrotas devem ser positivos.");
    }
  this->numOfVictoriesReversi = numOfVictoriesReversi;
  this->numOfLossesReversi = numOfLossesReversi;
}

std::ostream &operator<<(std::ostream &os, const Player &player) {

  os << player.getName() << ";";
  os << player.getNickname() << ";";
  os << player.getNumOfVictoriesLig4() << ";";
  os << player.getNumOfLossesLig4() << ";";
  os << player.getNumOfVictoriesReversi() << ";";
  os << player.getNumOfLossesReversi() << std::endl;
  return os;
}
