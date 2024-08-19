#ifndef GAMES_H
#define GAMES_H

#include <string>
#include <vector>

class AbstractGames {
protected:
   void printBasicBoard() const;

public:
    std::vector<std::vector<int>> board; // Representando o tabuleiro
    AbstractGames(int rows, int cols);          //Construtor

    
    virtual void printBoard() const = 0;                                   //Métodos Iniciais
    virtual void readMove() = 0;
    virtual bool isValid(int row, int col, int currentPlayer) = 0;
    virtual bool checkWin() = 0;
    virtual void resetBoard();

    virtual ~AbstractGames() = 0;           //Destrutor
};


#endif 
