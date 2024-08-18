#include "Tabuleiro.hpp"


void Board::startBoard() {

    int posicao= 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board_[i][j] = POSITIONS[posicao++];
        }
    }
}

void Board::printBoard() {
    cout << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << "| " << board_[i][j] << " ";
        }
        cout << "| \n";
    }
}

bool Board::checkWin() {
    int i = 0;
    int j = 0;

    //checar linhas
    for(int i = 0; i < 3; i++){
        if (board_[i][j] == board_[i][j++] && board_[i][j] == board_[i][j++]) {
            return true;
        }
        j = 0;
    }

    //checar colunas
    for(int j = 0; j < 3; j++){
        if (board_[i][j] == board_[++i][j] && board_[i][j]== board_[++i][j]) {
            return true;    
        }
        i = 0;
    }

    //checar diagonais
    if (board_[i][j] == board_[++i][++j] && board_[i][j] == board_[++i][++j]) {
        return true; 
    }

    i = 0;
    j = SIZE - 1;
    return board_[i][j] == board_[++i][--j] && board_[i][j] == board_[++i][--j];
}

bool Board::updatePosition(int posicao) {
    bool atualizacao = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board_[i][j] == POSITIONS[posicao]) {
                board_[i][j] = mark;
                atualizacao = true;
            }
        }
    }
    if (mark == 'X') {
        mark = 'O';
    }else {
        mark = 'X';    
    }

    return atualizacao;
}