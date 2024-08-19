#ifndef REVERSI_H
#define REVERSI_H
#include "Player.h"
#include "PlayerManager.h"
#include "IGames.h"
#include <vector>

class Reversi : public AbstractGames{
public:
    Reversi(int rows, int cols, const std::string& nickname1, const std::string& nickname2);
    ~Reversi();
   
    void readMove() override;
    bool checkWin() override;
    void startGame();
    void switchPlayer();
    enum Colors {NONE = 0, BLACK  = -1, WHITE = 1};
    std::vector<std::vector<int>> board;

private:
    int currentPlayer;
    std::vector<Player> players;
    Player* activePlayers[2];
    bool isValid(int row, int col, int currentPlayer) override; 
    bool possibleDirections(int row, int col, int x, int y, int currentPlayer);
    bool validPosition(size_t row, size_t col);
    void makeMove(int row, int col, int currentPlayer); 
    void printBoard() const;

};

#endif // REVERSI_H