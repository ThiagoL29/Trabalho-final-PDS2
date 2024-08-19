#ifndef CONNECT4_H
#define CONNECT4_H

#include "Connect4Board.hpp"

class Ligue4 {
private:
    Board4 board;
    int lastMoveX, lastMoveY;

public:
    Ligue4(int col, int row);
};

#endif