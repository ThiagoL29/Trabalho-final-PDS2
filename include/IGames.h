#ifndef GAMES_H
#define GAMES_H

#include <string>
#include <vector>

class AbstractGames {
private:
    std::vector<std::vector<int>> board; // Representando o tabuleiro

public:
    AbstractGames(int rows, int cols) : board(rows, std::vector<int>(cols, 0)) {}              //Construtor
    
    void printBoard();                                   //Métodos Iniciais
    void readMove();
    bool isValid();
    bool checkWin();


    ~AbstractGames (){}    
};


#endif 
