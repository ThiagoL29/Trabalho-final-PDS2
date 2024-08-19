#include "Connect4.hpp"

Ligue4::Ligue4(int col, int row, const string& nickname1, const string& nickname2) : board(col, row) {

    PlayerManager pm; 
    
    Player player1 = pm.returnPlayerByNickname(nickname1);
    Player player2 = pm.returnPlayerByNickname(nickname2);
    
    if (player1.getNickname().empty() || player2.getNickname().empty()) {
        throw std::invalid_argument("ERRO: Um ou ambos os jogadores não foram encontrados.");
    }

    // Inicializa os ponteiros para os jogadores ativos
    activePlayers[0] = new Player(player1);
    activePlayers[1] = new Player(player2);

    cout << "Por favor, selecione um número de 1 a " << row << endl;
    for (int i = 1; i <= row; ++i) {
        cout << "| " << i;
    }
    cout << "\n" << string(row * 3, '-') << endl;
    board.printBoard();

    for (int i = 0; i < (col * row) / 2; i++) {
        board.readMove(1, lastMoveX, lastMoveY);
        board.printBoard();
        if (board.checkWinner(lastMoveX, lastMoveY, 1)) {

            Player& winner = *activePlayers[0];
            Player& loser = *activePlayers[1];

            cout << "\n" << winner.getNickname() <<"Ganhou!" << endl;
            break;
        }

        board.readMove(2, lastMoveX, lastMoveY);
        board.printBoard();
        if (board.checkWinner(lastMoveX, lastMoveY, 2)) {
            Player& loser = *activePlayers[0];
            Player& winner = *activePlayers[1];
            cout << "\n" << winner.getNickname() <<"Ganhou!" << endl;
            winner.updateLig4PlayerStats(winner.getNumOfVictoriesLig4() + 1, winner.getNumOfLossesLig4());
            loser.updateLig4PlayerStats(loser.getNumOfVictoriesLig4(), loser.getNumOfLossesLig4() + 1 );
            PlayerManager pm;
            pm.updatePlayer(winner.getNickname() , winner);
            pm.updatePlayer(loser.getNickname(), loser);
            break;
        }
    }
}