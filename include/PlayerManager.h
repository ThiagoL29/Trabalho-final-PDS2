#ifndef PLAYERMANAGER_H 
#define PLAYERMANAGER_H

#include "Player.h"

class PlayerManager {
    public:
        void addPlayer(Player &player);
        void removePlayer(Player player);
        void updatePlayer(Player player);
        void printPlayers(char orderBy);
};

#endif
