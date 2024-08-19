#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "TicTacBoard.hpp"
#include "Player.h"
#include "PlayerManager.h"

class TicTacToe {
public:
    TicTacToe(const Board& board_);
    ~TicTacToe();

    void Start(const string& nickname1, const string& nickname2);
private:
    Board board_;
    Player* activePlayers[2];
};

#endif