#include "PlayerManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>


const std::string path("players_information.txt");

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

    if (playerData.size() == 6) {
        Player auxPlayer(playerData[0], playerData[1], std::stoi(playerData[2]),
                         std::stoi(playerData[3]), std::stoi(playerData[4]),
                         std::stoi(playerData[5]));
      std::cout << auxPlayer.getName() << std::endl;
      checkIfPlayerExistsInFile(player, auxPlayer);
       
    }
    
  }
  file.close();
}

void PlayerManager::addPlayerToFile(Player &player, std::ofstream &file) {
  file << player;
  file.close();
}

void PlayerManager::addPlayer(Player &player) {
  try {
    std::ifstream in(path, std::fstream::in);
    checkIfInputFileExists(in);
    readFileRowsAndCheckIfPlayerExists(player, in);
    in.close();

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
                                                 std::ifstream &file, std::string nickname) {
  std::string line;
  while (getline(file, line)) {
    std::vector<std::string> playerData;
    std::stringstream info(line);
    std::string aux;
    while (getline(info, aux, ';')) {
      playerData.push_back(aux);
    }

    if (playerData.size() == 6) {
    Player auxPlayer(playerData[0], playerData[1], std::stoi(playerData[2]),
                     std::stoi(playerData[3]), std::stoi(playerData[4]),
                     std::stoi(playerData[5]));

    if (auxPlayer.getNickname() != nickname) {
      players.push_back(auxPlayer);
    }
    }
    file.close();
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

  delete players;
    } catch (std::ios_base::failure &e) {
      std::cout << e.what() << std::endl;
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
    }
}

void PlayerManager::readFileRowsAndUpdatePlayer(std::vector<Player> &players, Player &player,
                                                 std::ifstream &file) {
  std::string line;
  while (getline(file, line)) {
    std::vector<std::string> playerData;
    std::stringstream info(line);
    Player cmpPlayer;
    std::string aux;
    while (getline(info, aux, ';')) {
      playerData.push_back(aux);
    }

    if (playerData.size() == 6) {
    Player auxPlayer(playerData[0], playerData[1], std::stoi(playerData[2]),
                     std::stoi(playerData[3]), std::stoi(playerData[4]),
                     std::stoi(playerData[5]));

    if (auxPlayer.getNickname() != player.getNickname()) {
      players.push_back(auxPlayer);
      continue;
    }

    auxPlayer = player;
    cmpPlayer = auxPlayer;
    players.push_back(auxPlayer);
    }

    if(cmpPlayer.getNickname() != player.getNickname()) {
      throw std::invalid_argument("Jogador não existe. Tente novamente com outro nickname.");
    }
  }
  file.close();
}

void PlayerManager::updatePlayer(Player &player) {
  try {
    std::ifstream in(path, std::fstream::in);
    checkIfInputFileExists(in);

    std::vector<Player> *players = new std::vector<Player>;
    readFileRowsAndUpdatePlayer(*players, player, in);

    std::ofstream out(path, std::fstream::out);
    for (auto iter = players->begin(); iter != players->end(); iter++) {
      addPlayerToFile(*iter, out);
    }
    
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

      if (playerData.size() == 6) {
          Player auxPlayer(playerData[0], playerData[1], std::stoi(playerData[2]),
                           std::stoi(playerData[3]), std::stoi(playerData[4]),
                           std::stoi(playerData[5]));

        if(auxPlayer.getNickname() == nickname) {
          return auxPlayer;
        }
      }

    }
      in.close();
    
  } catch (std::ios_base::failure &e) {
    std::cout << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return Player();
}

void PlayerManager::readFileRows(std::vector<Player> &players, std::ifstream &file) {
  std::string line;
  
  while (getline(file, line)) {
    std::vector<std::string> playerData;
    std::stringstream info(line);
    std::string aux;
    while (getline(info, aux, ';')) {
      playerData.push_back(aux);
    }

    if (playerData.size() == 6) {
    Player auxPlayer(playerData[0], playerData[1], std::stoi(playerData[2]),
                     std::stoi(playerData[3]), std::stoi(playerData[4]),
                     std::stoi(playerData[5]));

      players.push_back(auxPlayer);
    }
    
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

    if(lowerOrderBy != 'n' && lowerOrderBy != 'a') {
      throw std::invalid_argument("Ordenação inválida. Tente novamente.");
    }

    if (lowerOrderBy == 'n') {
      std::sort(players->begin(), players->end(), [](const Player& lhs, const Player& rhs) {
            return lhs.getName() < rhs.getName();
         });
    }

    if(lowerOrderBy == 'a') {
      std::sort(players->begin(), players->end(), [](const Player& lhs, const Player& rhs) {
          return lhs.getNickname() < rhs.getNickname();
       });
    }

    for(auto it = players->begin(); it != players->end(); it++) {
        std::cout << *it << std::endl;
     }
    
    delete players;
  } catch (std::ios_base::failure &e) {
      std::cout << e.what() << std::endl;
  } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
  }
}