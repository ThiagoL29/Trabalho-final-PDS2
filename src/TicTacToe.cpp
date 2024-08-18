#include "TicTacToe.hpp"

TicTacToe::TicTacToe(const Board& tabuleiro) : board_(tabuleiro) {}

void TicTacToe::Start() {
    board_.startBoard();

    int movimentos = 0;
    while (movimentos < 9) {
        cout << "JOGO DA VELHA" << endl;
        board_.printBoard();
        cout << "Turno do jogador " << (movimentos % 2 ? "1" : "2") << endl;
        int posicao = 0;
        cin >> posicao;
        while (posicao > 9 || posicao < 1) {
            cout << "Posicao inválida. Selecione um número de 1 a 9.";
            cin >> posicao;
        };

        while (!board_.updatePosition(posicao))
       
       if (movimentos > 3) {
            if(board_.checkWin()) {
                board_.checkWin();
                cout << "Jogador " << (movimentos % 2 ? "1" : "2") << " ganhou!" << endl;
                break;
            } else if (movimentos == 8) {
                cout << "EMPATE!" << endl;
            }
       }
       movimentos++;
    };
}