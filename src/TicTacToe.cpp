#include "TicTacToe.hpp"

TicTacToe::TicTacToe(const Board& board) : board_(board) {}

TicTacToe::~TicTacToe() {
    delete activePlayers[0];
    delete activePlayers[1];
}

void TicTacToe::Start(const string& nickname1, const string& nickname2) {
    board_.startBoard();

    int moves = 0;
    while (moves < 9) {
        cout << "JOGO DA VELHA" << endl;
        board_.printBoard();
        cout << "Turno do jogador " << (moves % 2 ? "1" : "2") << endl;
        int position = 0;
        cin >> position;
        while (position > 9 || position < 1) {
            cout << "Posicao inválida. Selecione um número de 1 a 9.";
            cin >> position;
        };

        while (!board_.updatePosition(position))
       
       if (moves > 3) {
            if(board_.checkWin()) {
                board_.checkWin();
                cout << "Jogador " << (moves % 2 ? "1" : "2") << " ganhou!" << endl;
                break;
            } else if (moves == 8) {
                cout << "EMPATE!" << endl;
            }
       }
       moves++;
    };
}