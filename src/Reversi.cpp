#include "../include/IReversi.h"
#include "../include/Player.h"
#include "../include/PlayerManager.h"
#include "../include/Utilitiies.h"
#include <iostream>


Reversi::Reversi(int rows, int cols, const std::string& nickname1, const std::string& nickname2)
    : AbstractGames(rows, cols), currentPlayer(BLACK), board(rows, std::vector<int>(cols, 0)) {

    PlayerManager pm; 
    
    Player player1 = pm.returnPlayerByNickname(nickname1);
    Player player2 = pm.returnPlayerByNickname(nickname2);
    
    if (player1.getNickname().empty() || player2.getNickname().empty()) {
        throw std::invalid_argument("ERRO: Um ou ambos os jogadores não foram encontrados.");
    }

    // Inicializa os ponteiros para os jogadores ativos
    activePlayers[0] = new Player(player1);
    activePlayers[1] = new Player(player2);
}

Reversi::~Reversi(){
    delete activePlayers[0];
    delete activePlayers[1];
}

void Reversi::switchPlayer() {
    currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
}

void Reversi::printBoard() const {
    int index = 1;
    std::cout << "Tabuleiro atual:" << std::endl;
    for(size_t i = 0; i <= board.size(); i++)
        std::cout << i << " ";
    std::cout << std::endl;
    for (const auto& row : board) { 
        if(index < 10)
            std::cout << index << " ";
        else{
            std::cout << index;
        }
        index++;
        for (int cell : row) {
            if (cell == BLACK) {
                std::cout << "B "; // Preto
            } else if (cell == WHITE) {
                std::cout << "W "; // Branco
            } else {
                std::cout << ". "; // Vazio
            }
        }
        std::cout << std::endl;
    }
}

void Reversi::startGame() {
    resetBoard(); // Limpa o tabuleiro 
    currentPlayer = BLACK;

    size_t midBoard = board.size() / 2 - 1;
    board[midBoard][midBoard] = WHITE;
    board[midBoard + 1][midBoard + 1] = WHITE;
    board[midBoard][midBoard + 1] = BLACK;
    board[midBoard + 1][midBoard] = BLACK;
    
}

bool Reversi::possibleDirections(int row, int col, int x, int y, int player) {
    int rowDirection = row + x;
    int colDirection = col + y;
    bool foundEnemy = false;

    while (validPosition(rowDirection, colDirection)) {
        if (board[rowDirection][colDirection] == 0){
            return false;
        }

        if (board[rowDirection][colDirection] == player){
            return foundEnemy;
        }
        foundEnemy = true;
        rowDirection += x;
        colDirection += y;
    }
    return false;
}

bool Reversi::validPosition(int row, int col) {
    return row >= 0 && row < board.size() && col >= 0 && col < board.size();
}

bool Reversi::isValid(int row, int col, int currentPlayer){
    if (board[row][col] != 0)
        return false;

    bool hasValidMove = false;
    for (int x = -1; x <= 1; ++x){
        for(int y = -1; y <= 1; ++y){
            if(x == 0 && y == 0) continue;

            bool directionValid = possibleDirections(row, col, x, y, currentPlayer);
            if(directionValid){
                hasValidMove = true;
            }
        }
    }
    return hasValidMove;
}
void Reversi::readMove() {
    int row, col;
    bool moveValid = false;

    while (!moveValid) {
        try {
            std::cout << "Digite seu movimento (linha e coluna): " << std::endl;
            std::cin >> row >> col;

            if (row <= 0 || row > board.size() || col <= 0 || col > board.size()) {
                throw std::invalid_argument("ERRO: Entrada inválida. Tente novamente.");
            }

            int actualRow = row - 1;
            int actualCol = col - 1;

            if (validPosition(actualRow, actualCol) && isValid(actualRow, actualCol, currentPlayer)) {
                makeMove(actualRow, actualCol, currentPlayer);
                switchPlayer();
                moveValid = true;  // Saí do loop se o movimento for válido
            } else {
                throw std::invalid_argument("ERRO: Movimento inválido. Tente novamente.");
            }
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void Reversi::makeMove(int row, int col, int currentPlayer) {
    board[row][col] = currentPlayer;

    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (x == 0 && y == 0) continue;
            
            if (possibleDirections(row, col, x, y, currentPlayer)) {
                int rowDirection = row + x;
                int colDirection = col + y;
                
                while (validPosition(rowDirection, colDirection) && board[rowDirection][colDirection] != currentPlayer) {
                    board[rowDirection][colDirection] = currentPlayer;
                    rowDirection += x;
                    colDirection += y;
                }
            }
        }
    }
}

bool Reversi::checkWin() {
    bool blackHasMove = false;
    bool whiteHasMove = false;

    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board.size(); ++j) {
            if (isValid(i, j, BLACK))
                blackHasMove = true;
            if (isValid(i, j, WHITE))
                whiteHasMove = true;
        }
    }
    if (!blackHasMove && currentPlayer == BLACK && whiteHasMove){
        switchPlayer();
        return false;
    }
    if(!whiteHasMove && currentPlayer == WHITE && blackHasMove){
        switchPlayer();
        return false;
    }

    if (!blackHasMove && !whiteHasMove) {
        int blackCount = 0;
        int whiteCount = 0;

        for (const auto& row : board) {
            for (int cell : row) {
                if (cell == BLACK)
                    blackCount++;
                else if (cell == WHITE)
                    whiteCount++;
            }
        }

        std::cout << "Peças pretas: " << blackCount << ", Peças brancas: " << whiteCount << std::endl;
        Player& winner = blackCount > whiteCount ? *activePlayers[0] : *activePlayers[1];
        Player& loser = blackCount > whiteCount ? *activePlayers[1] : *activePlayers[0];
        if (blackCount > whiteCount)
            std::cout << "Preto Ganahou!!" << std::endl;    
        else if (whiteCount > blackCount)
            std::cout << "BRANCO GANHOU!!" << std::endl;
        else
            std::cout << "Empate" << std::endl;
        

        winner.updateReversiPlayerStats(winner.getNumOfVictoriesReversi() + 1, winner.getNumOfLossesReversi());
        loser.updateReversiPlayerStats(loser.getNumOfVictoriesReversi(), loser.getNumOfLossesReversi() + 1 );
        PlayerManager pm;
        pm.updatePlayer(winner);
        pm.updatePlayer(loser);
        return true; // END GAME
    }

    return false;
}






