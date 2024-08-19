#include "PlayerManager.h"
#include "Utilitiies.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>

const std::string path("./database/players_informations.txt");

PlayerManager::PlayerManager() {}

void PlayerManager::checkIfInputFileExists(std::ifstream &file) const {
  if (!file.is_open()) {
    throw std::ios_base::failure("Houve um erro ao abrir o arquivo");
  }
}

void PlayerManager::checkIfOutputFileExists(std::ofstream &file) const {
  if (!file.is_open()) {
    throw std::ios_base::failure("Houve um erro ao abrir o arquivo");
  }
}

void PlayerManager::checkIfPlayerExistsInFile(Player &player,
                                              Player &auxPlayer) const {
  if (player.getNickname() == auxPlayer.getNickname()) {
    throw std::invalid_argument(
        "Jogador já existe. Tente novamente com outro nickname.");
  }
}

void PlayerManager::checkSizeOfPlayerDataVectorAndCreateAuxPlayer(
    std::vector<std::string> &playerData, Player *&player) const {
  try {
    if (playerData.size() != 8) {
      throw std::out_of_range("ERRO: O arquivo está com dados inválidos.");
    }

    player = new Player(playerData[0], playerData[1], std::stoi(playerData[2]),
                        std::stoi(playerData[3]), std::stoi(playerData[4]),
                        std::stoi(playerData[5]), std::stoi(playerData[6]),
                        std::stoi(playerData[7]));

  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void PlayerManager::readFileRowsAndCheckIfPlayerExists(
    Player &player, std::ifstream &file) const {

  std::string line;
  while (getline(file, line)) {
    std::stringstream info(line);
    std::vector<std::string> playerData;
    std::string aux;
    while (getline(info, aux, ';')) {
      playerData.push_back(aux);
    }

    Player *auxPlayer = nullptr;
    checkSizeOfPlayerDataVectorAndCreateAuxPlayer(playerData, auxPlayer);
    checkIfPlayerExistsInFile(player, *auxPlayer);
    delete auxPlayer;
  }
  file.close();
}

void PlayerManager::addPlayerToFile(Player &player, std::ofstream &file) {
  file << player;
}

void PlayerManager::addPlayer(Player &player) {
  try {
    std::ifstream in(path, std::fstream::in);
    checkIfInputFileExists(in);
    readFileRowsAndCheckIfPlayerExists(player, in);

    std::ofstream out(path, std::ios_base::app);
    checkIfOutputFileExists(out);
    addPlayerToFile(player, out);
    out.close();

  } catch (std::ios_base::failure &e) {
    std::cout << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void PlayerManager::readFileRowsAndRemovePlayer(std::vector<Player> &players,
                                                std::ifstream &file,
                                                std::string nickname) {
  std::string line;
  bool playerFound = false;
  while (getline(file, line)) {
    std::vector<std::string> playerData;
    std::stringstream info(line);
    std::string aux;
    while (getline(info, aux, ';')) {
      playerData.push_back(aux);
    }

    Player *auxPlayer = nullptr;
    checkSizeOfPlayerDataVectorAndCreateAuxPlayer(playerData, auxPlayer);

    if (auxPlayer->getNickname() == nickname) {
      playerFound = true;
    } else {
      players.push_back(*auxPlayer);
    }

    delete auxPlayer;
  }

  file.close();

  if (!playerFound) {
    throw std::invalid_argument("Jogador já está excluído.");
  }
}

void PlayerManager::removePlayer(std::string nickname) {
  try {
    std::ifstream in(path, std::fstream::in);
    checkIfInputFileExists(in);

    std::vector<Player> *players = new std::vector<Player>;
    readFileRowsAndRemovePlayer(*players, in, nickname);

    std::ofstream out(path, std::fstream::out);
    for (auto iter = players->begin(); iter != players->end(); iter++) {
      addPlayerToFile(*iter, out);
    }

    out.close();

    delete players;
  } catch (std::ios_base::failure &e) {
    std::cout << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void PlayerManager::checkNewNickname(Player *auxPlayer, Player &player,
                                     std::string nickname) const {

  if (auxPlayer->getNickname() == player.getNickname() &&
      nickname != player.getNickname()) {
    delete auxPlayer;
    throw std::invalid_argument(
        "Jogador já existe. Tente novamente com outro nickname.");
  }
}

void PlayerManager::readFileRowsAndUpdatePlayer(std::vector<Player> &players,
                                                std::string nickname,
                                                Player &player,
                                                std::ifstream &file) {
  std::string line;
  bool playerFound = false;

  while (getline(file, line)) {
    std::vector<std::string> playerData;
    std::stringstream info(line);
    Player cmpPlayer;
    std::string aux;
    while (getline(info, aux, ';')) {
      playerData.push_back(aux);
    }

    Player *auxPlayer = nullptr;
    checkSizeOfPlayerDataVectorAndCreateAuxPlayer(playerData, auxPlayer);
    checkNewNickname(auxPlayer, player, nickname);

    if (auxPlayer->getNickname() == nickname) {
      *auxPlayer = player;
      playerFound = true;
    }

    players.push_back(*auxPlayer);
    delete auxPlayer;
  }

  file.close();

  if (!playerFound) {
    throw std::invalid_argument(
        "Jogador não existe. Tente novamente com outro nickname.");
  }
}

void PlayerManager::updatePlayer(std::string nickname, Player &player) {
  try {
    std::ifstream in(path, std::fstream::in);
    checkIfInputFileExists(in);

    std::vector<Player> *players = new std::vector<Player>;
    readFileRowsAndUpdatePlayer(*players, nickname, player, in);

    std::ofstream out(path, std::fstream::out);
    for (auto iter = players->begin(); iter != players->end(); iter++) {
      addPlayerToFile(*iter, out);
    }

    out.close();

    delete players;
  } catch (std::ios_base::failure &e) {
    std::cout << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

Player PlayerManager::returnPlayerByNickname(std::string nickname) {
  try {
    std::ifstream in(path, std::fstream::in);
    checkIfInputFileExists(in);
    std::string line;
    while (getline(in, line)) {
      std::stringstream info(line);
      std::vector<std::string> playerData;
      std::string aux;
      while (getline(info, aux, ';')) {
        playerData.push_back(aux);
      }

      Player *auxPlayer = nullptr;
      checkSizeOfPlayerDataVectorAndCreateAuxPlayer(playerData, auxPlayer);

      if (auxPlayer->getNickname() == nickname) {
        return *auxPlayer;
      }

      delete auxPlayer;
    }

    in.close();

  } catch (std::ios_base::failure &e) {
    std::cout << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return Player();
}

void PlayerManager::readFileRows(std::vector<Player> &players,
                                 std::ifstream &file) {
  std::string line;

  while (getline(file, line)) {
    std::vector<std::string> playerData;
    std::stringstream info(line);
    std::string aux;
    while (getline(info, aux, ';')) {
      playerData.push_back(aux);
    }

    Player *auxPlayer = nullptr;
    checkSizeOfPlayerDataVectorAndCreateAuxPlayer(playerData, auxPlayer);
    players.push_back(*auxPlayer);
    delete auxPlayer;
  }
  file.close();
}

void PlayerManager::printPlayers(char orderBy) {
  try {
    std::ifstream in(path, std::fstream::in);
    checkIfInputFileExists(in);

    std::vector<Player> *players = new std::vector<Player>;
    readFileRows(*players, in);

    char lowerOrderBy = std::tolower(orderBy);

    if (lowerOrderBy != 'n' && lowerOrderBy != 'a') {
      throw std::invalid_argument("Ordenação inválida. Tente novamente.");
    }

    if (lowerOrderBy == 'n') {
      std::sort(players->begin(), players->end(),
                [](const Player &lhs, const Player &rhs) {
                  return lhs.getName() < rhs.getName();
                });
    }

    if (lowerOrderBy == 'a') {
      std::sort(players->begin(), players->end(),
                [](const Player &lhs, const Player &rhs) {
                  return lhs.getNickname() < rhs.getNickname();
                });
    }

    for (auto it = players->begin(); it != players->end(); it++) {
      it->print();
    }

    delete players;
  } catch (std::ios_base::failure &e) {
    std::cout << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}