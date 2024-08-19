#ifndef CONNECT4_H
#define CONNECT4_H

#include "Connect4Board.hpp"
#include "Player.h"
#include "PlayerManager.h"

class Ligue4 {
private:
    Board4 board;
    int lastMoveX, lastMoveY;
    Player* activePlayers[2];

public:
    Ligue4(int col, int row, const string& nickname1, const string& nickname2);
};

#endif