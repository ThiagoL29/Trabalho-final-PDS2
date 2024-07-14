#ifndef REVERSI_H
#define REVERSI_H

#include "IGames.h"

class Reversi : public AbstractGames{
    public:
        Reversi();

        void printBoard() const override;
        void readMove() override;
        bool isValid(int row, int col) const override;     // Conts pois nao modifica o Objeto
        bool checkWin() const override;
        void resetBoard() override;

    private:
    bool checkDirection(int row, int col, int drow, int dcol, char player) const;
    void makeMove(int row, int col, char player);
    
};

#endif 