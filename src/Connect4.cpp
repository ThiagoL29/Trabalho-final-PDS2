#include "Connect4.hpp"

Ligue4::Ligue4(int col, int row) : board(col, row) {

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
            cout << "\nVocê ganhou!" << endl;
            break;
        }

        board.readMove(2, lastMoveX, lastMoveY);
        board.printBoard();
        if (board.checkWinner(lastMoveX, lastMoveY, 2)) {
            cout << "\nVocê ganhou!" << endl;
            break;
        }
    }
}