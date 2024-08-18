#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "Tabuleiro.hpp"

class TicTacToe {
public:
    TicTacToe(const Board& board_);
    ~TicTacToe();

    void Start();
private:
    Board board_;
};

#endif