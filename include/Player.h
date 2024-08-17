#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
  std::string name;
  std::string nickame;
  int numOfVictoriesLig4;
  int numOfLossesLig4;
  int numOfVictoriesReversi;
  int numOfLossesReversi;

public:
  Player();
  Player(std::string name, std::string nickname);
  Player(std::string name, std::string nickname, int numOfVictoriesLig4,
         int numOfLossesLig4, int numOfVictoriesReversi, int numOfLossesReversi);
  std::string getName() const;
  std::string getNickname() const;
  int getNumOfVictoriesLig4() const;
  int getNumOfLossesLig4() const;
  int getNumOfVictoriesReversi() const;
  int getNumOfLossesReversi() const;
  void updateName(std::string newName);
  void updateNickName(std::string newNickname);
  void updateLig4PlayerStats(int numOfVictoriesLig4, int numOfLossesLig4);
  void updateReversiPlayerStats(int numOfVictoriesReversi,
                                int numOfLossesReversi);
  friend std::ostream &operator<<(std::ostream &os, const Player &player);
};

#endif
