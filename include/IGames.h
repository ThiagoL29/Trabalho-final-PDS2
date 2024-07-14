#ifndef GAMES_H
#define GAMES_H

#include <string>
#include <vector>

class AbstractGames {
private:
    std::vector<std::vector<int>> board; // Representando o tabuleiro

public:
    AbstractGames(int rows, int cols) : board(rows, std::vector<int>(cols, 0)) {}              //Construtor
    
    virtual void printBoard() const;                                   //Métodos Iniciais
    virtual void readMove();
    virtual bool isValid(int row, int col) const;
    virtual bool checkWin() const;
    virtual void resetBoard();

    virtual ~AbstractGames (){}              //Destrutor
};


#endif 
