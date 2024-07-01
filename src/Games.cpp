#include "IGames.h"


AbstractGames::AbstractGames(int rows, int cols)
: board(rows, std::vector<int>(cols, 0)){
}




