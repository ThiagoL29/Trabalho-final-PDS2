#include "Player.h"
#include "Utilitiies.h"
#include <iostream>

Player::Player() : name(""), nickame("") {
  numOfVictoriesLig4 = numOfLossesLig4 = numOfVictoriesReversi =
      numOfLossesReversi = numOfVictoriesTicTacToe = numOfLossesTicTacToe = 0;
}

Player::Player(std::string name, std::string nickname)
    : name(toLower(name)), nickame(toLower(nickname)) {
  numOfVictoriesLig4 = numOfLossesLig4 = numOfVictoriesReversi =
      numOfLossesReversi = numOfVictoriesTicTacToe = numOfLossesTicTacToe = 0;
}

Player::Player(std::string name, std::string nickname, int numOfVictoriesLig4,
               int numOfLossesLig4, int numOfVictoriesReversi,
               int numOfLossesReversi, int numOfVictoriesTicTacToe,
               int numOfLossesTicTacToe)
    : name(toLower(name)), nickame(toLower(nickname)),
      numOfVictoriesLig4(numOfVictoriesLig4), numOfLossesLig4(numOfLossesLig4),
      numOfVictoriesReversi(numOfVictoriesReversi),
      numOfLossesReversi(numOfLossesReversi),
      numOfVictoriesTicTacToe(numOfVictoriesTicTacToe),
      numOfLossesTicTacToe(numOfLossesTicTacToe) {}

std::string Player::getName() const { return this->name; }

std::string Player::getNickname() const { return this->nickame; }

int Player::getNumOfVictoriesLig4() const { return this->numOfVictoriesLig4; }

int Player::getNumOfLossesLig4() const { return this->numOfLossesLig4; }

int Player::getNumOfVictoriesReversi() const {
  return this->numOfVictoriesReversi;
}

int Player::getNumOfLossesReversi() const { return this->numOfLossesReversi; }

int Player::getNumOfVictoriesTicTacToe() const {
  return this->numOfVictoriesTicTacToe;
}

int Player::getNumOfLossesTicTacToe() const {
  return this->numOfLossesTicTacToe;
}

void Player::updateName(std::string newName) { this->name = newName; }

void Player::updateNickName(std::string newNickname) {
  this->nickame = newNickname;
}

void Player::checkStats(int numOfVictories, int numOfLosses) {
  if (numOfVictories < 0 || numOfLosses < 0) {
    throw std::out_of_range(
        "Número de vitórias e derrotas devem ser positivos.");
  }
}

void Player::updateLig4PlayerStats(int numOfVictoriesLig4,
                                   int numOfLossesLig4) {
  try {
    checkStats(numOfVictoriesLig4, numOfLossesLig4);
    this->numOfVictoriesLig4 = numOfVictoriesLig4;
    this->numOfLossesLig4 = numOfLossesLig4;
  } catch (std::out_of_range &e) {
    std::cout << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void Player::updateReversiPlayerStats(int numOfVictoriesReversi,
                                      int numOfLossesReversi) {

  try {
    checkStats(numOfVictoriesReversi, numOfLossesReversi);
    this->numOfVictoriesReversi = numOfVictoriesReversi;
    this->numOfLossesReversi = numOfLossesReversi;
  } catch (std::out_of_range &e) {
    std::cout << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void Player::updateTicTacToePlayerStats(int numOfVictoriesTicTacToe,
                                        int numOfLossesTicTacToe) {
  try {
    checkStats(numOfVictoriesTicTacToe, numOfLossesTicTacToe);
    this->numOfVictoriesTicTacToe = numOfVictoriesTicTacToe;
    this->numOfLossesTicTacToe = numOfLossesTicTacToe;
  } catch (std::out_of_range &e) {
    std::cout << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void Player::print() {
  std::cout << this->getNickname() << " " << this->getName() << std::endl;
  std::cout << "CONNECT4 - V: <" << this->getNumOfVictoriesLig4() << "> D: <"
            << this->getNumOfLossesLig4() << ">" << std::endl;
  std::cout << "REVERSI - V: <" << this->getNumOfVictoriesReversi() << "> D: <"
            << this->getNumOfLossesReversi() << ">" << std::endl;
  std::cout << "TICTACTOE - V: <" << this->getNumOfVictoriesTicTacToe()
            << "> D: <" << this->getNumOfLossesTicTacToe() << ">" << std::endl;

  std::cout << "-------------------------------------------" << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Player &player) {

  os << player.getName() << ";";
  os << player.getNickname() << ";";
  os << player.getNumOfVictoriesLig4() << ";";
  os << player.getNumOfLossesLig4() << ";";
  os << player.getNumOfVictoriesReversi() << ";";
  os << player.getNumOfLossesReversi() << ";";
  os << player.getNumOfVictoriesTicTacToe() << ";";
  os << player.getNumOfLossesTicTacToe() << std::endl;
  return os;
}
