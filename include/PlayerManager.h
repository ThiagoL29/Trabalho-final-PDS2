#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "Player.h"
#include <vector>

class PlayerManager {
private:
  void checkIfInputFileExists(std::ifstream &file) const;
  void checkIfOutputFileExists(std::ofstream &file) const;
  void checkIfPlayerExistsInFile(Player &player, Player &auxPlayer) const;
  void readFileRowsAndCheckIfPlayerExists(Player &player,
                                           std::ifstream &file) const;
  void checkIfPlayerObjectIsDeleted(Player &player) const;
  void addPlayerToFile(Player &player, std::ofstream &file);
  void readFileRowsAndRemovePlayer(std::vector<Player> &players,
 std::ifstream &file, std::string nickname);
void readFileRowsAndUpdatePlayer(std::vector<Player> &players, Player &player,
 std::ifstream &file);
void readFileRows(std::vector<Player> &players, std::ifstream &file);

public:
  PlayerManager();
  void addPlayer(Player &player);
  void removePlayer(std::string nickname);
  void updatePlayer(Player &player);
  Player returnPlayerByNickname(std::string nickname);
  void printPlayers(char orderBy);
};

#endif
