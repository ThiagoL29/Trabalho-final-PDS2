#include "TicTacToe.hpp"
#include "Player.h"
#include "PlayerManager.h"
#include "Utilitiies.h"  

TicTacToe::TicTacToe(const Board& board) : board_(board){}

TicTacToe::~TicTacToe() {
    delete activePlayers[0];
    delete activePlayers[1];
}

void TicTacToe::Start(const string& nickname1, const string& nickname2) {
    PlayerManager pm; 
    
    Player player1 = pm.returnPlayerByNickname(nickname1);
    Player player2 = pm.returnPlayerByNickname(nickname2);
    
    if (player1.getNickname().empty() || player2.getNickname().empty()) {
        throw std::invalid_argument("ERRO: Um ou ambos os jogadores não foram encontrados.");
    }

    // Inicializa os ponteiros para os jogadores ativos
    activePlayers[0] = new Player(player1);
    activePlayers[1] = new Player(player2);

    board_.startBoard();

    int moves = 0;
    while (moves < 9) {
        cout << "JOGO DA VELHA" << endl;
        board_.printBoard();
        cout << "Turno do jogador " << (moves % 2 ? nickname1 : nickname2) << endl;
        int position = 0;
        cin >> position;
        while (position > 9 || position < 1) {
            cout << "Posicao inválida. Selecione um número de 1 a 9.";
            cin >> position;
        };

        while (!board_.updatePosition(position)) {
            cout << "Posição inválida. Tente novamente com uma posição válida.";
        }
       
        if (moves > 3) {
            if(board_.checkWin()) {
                board_.checkWin();
                cout << "Jogador " << (moves % 2 ? nickname1 : nickname2) << " ganhou!" << endl;

                Player& winner = moves % 2 ? *activePlayers[0] : *activePlayers[1];
                Player& loser = moves % 2 ? *activePlayers[1] : *activePlayers[0];
                winner.updateTicTacToePlayerStats(winner.getNumOfVictoriesTicTacToe() + 1, winner.getNumOfLossesTicTacToe());
                loser.updateTicTacToePlayerStats(loser.getNumOfVictoriesTicTacToe(), loser.getNumOfLossesTicTacToe() + 1 );
                PlayerManager pm;
                pm.updatePlayer(winner.getNickname(), winner);
                pm.updatePlayer(loser.getNickname(), loser);

                break;
            } else if (moves == 8) {
                cout << "EMPATE!" << endl;
            }
       }
       moves++;
    };
}