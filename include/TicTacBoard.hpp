#ifndef TABULEIRO_H
#define TABULEIRO_H 
#include <iostream>
using namespace std;

#define SIZE 3
const char POSITIONS[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

class Board {
public:
    Board();
    ~Board();

    void startBoard();
    void printBoard();
    bool checkWin();
    bool updatePosition(int posicao);
private:
    char board_[SIZE][SIZE];
    char mark;
};

#endif