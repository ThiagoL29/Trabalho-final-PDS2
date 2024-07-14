#include "IGames.h"


AbstractGames::AbstractGames(int rows, int cols)
: board(rows, std::vector<int>(cols, 0)){
}

void AbstractGames::resetBoard(){
    for(auto& row : board){
        std::fill(row.begin(), row.end(), 0);
    }
}

AbstractGames::~AbstractGames(){
    
}




