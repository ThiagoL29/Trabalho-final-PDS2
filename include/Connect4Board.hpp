#ifndef BOARD4_H
#define BOARD4_H

#include <iostream>
#include <vector>

using namespace std;

class Board4 {
private:
    vector<vector<int>> boardInfo;
    int col, row;

public:
    Board4(int col, int row) : col(col), row(row), boardInfo(col, vector<int>(row, 0)) {}

    void printBoard() const;
    void readMove(int player, int& lastMoveX, int& lastMoveY);
    bool checkWinner(int x, int y, int player) const;
    bool checkLeftD(int x, int y, int player) const;
    bool checkRightD(int x, int y, int player) const;
    bool checkCol(int x, int y, int player) const;
    bool checkRow(int x, int y, int player) const;

};

#endif