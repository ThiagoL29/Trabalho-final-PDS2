#include "../include/IGames.h"
#include <iostream>


AbstractGames::AbstractGames(int rows, int cols)
: board(rows, std::vector<int>(cols, 0)){
}


void AbstractGames::resetBoard(){
    for(auto& row : board){
        std::fill(row.begin(), row.end(), 0);
    }
}
AbstractGames::~AbstractGames(){}
void AbstractGames::printBasicBoard() const{
    int index = 1;
        std::cout << "Tabuleiro atual:" << std::endl;
        for (size_t i = 0; i < board.size(); i++)
            std::cout << i + 1 << " ";
        std::cout << std::endl;
        for (const auto& row : board) {
            if (index < 10)
                std::cout << index << " ";
            else
                std::cout << index;
            index++;
            for (int cell : row) {
                std::cout << cell << " "; // Representação numérica básica
            }
            std::cout << std::endl;
        }
}





