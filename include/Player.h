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
        bool isDeleted;

    public:
        Player(std::string name, std::string nickname);
        std::string getName() const;
        std::string getNickname() const;
        bool getUserStatus() const;
        void removePlayer();
        void updateName(std::string newName);
        void updateNickName(std::string newNickname);
        void updateLig4PlayerStats(int numOfVictoriesLig4, int numOfLossesLig4);
        void updateReversiPlayerStats(int numOfVictoriesReversi, int numOfLossesReversi);
};

#endif
