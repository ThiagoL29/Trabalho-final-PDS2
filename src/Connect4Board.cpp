#include "Connect4Board.hpp"

void Board4::printBoard() const {
    cout << endl;
        for (int y = 0; y < col; y++) {
            for (int x = 0; x < row + 1; x++) {
                cout << "| ";
                if (boardInfo[y][x] == 0) cout << " ";
                else if (boardInfo[y][x] == 1) cout << "X";
                else if (boardInfo[y][x] == 2) cout << "O";
            }
            cout << "\n" << string(row * 3, '-') << endl;
        }
}

void Board4::readMove(int player, int& lastMoveX, int& lastMoveY) {
    int choice;
        cout << "\nJogador " << player << ", por favor selecione um número de 1 a " << row << ": ";
        cin >> choice;

        while (choice > row || choice <= 0 || cin.fail()) {
            cout << "Seleção inválida. Por favor, selecione novamente: ";
            cin >> choice;
        }

        int number = 0;
        while (boardInfo[col - 1 - number][choice - 1] != 0) {
            number++;
            if (number >= col) {
                cout << "Por favor, selecione novamente: ";
                cin >> choice;
                number = 0;
            }
        }
}

bool Board4::checkWinner(int x, int y, int player) const {
        return checkLeftD(x, y, player) ||
               checkRightD(x, y, player) ||
               checkCol(x, y, player) ||
               checkRow(x, y, player);
}

bool Board4::checkLeftD(int x, int y, int player) const {
    int score = 1;
        int count = 1;

        while ((y - count >= 0) && (x + count < row)) {
            if (boardInfo[y - count][x + count] == player) {
                score++;
                count++;
            } else {
                break;  
            }
        }

        count = 1;
        while ((y + count < col) && (x - count >= 0)) {
            if (boardInfo[y + count][x - count] == player) {
                score++;
                count++;
            } else {
                break;
            }
        }

        return score >= 4;
}

bool Board4::checkRightD(int x, int y, int player) const {
    int score = 1;
        int count = 1;

        while ((y + count < col) && (x + count < row)) {
            if (boardInfo[y + count][x + count] == player) {
                score++;
                count++;
            } else {
                break;
            }
        }

        count = 1;
        while ((y - count >= 0) && (x - count >= 0)) {
            if (boardInfo[y - count][x - count] == player) {
                score++;
                count++;
            } else {
                break;
            }
        }

        return score >= 4;
}

bool Board4::checkCol(int x, int y, int player) const {
    int score = 1;
        int count = 1;

        while (y + count < col) {
            if (boardInfo[y + count][x] == player) {
                score++;
                count++;
            } else {
                break;
            }
        }

        return score >= 4;
}

bool Board4::checkRow(int x, int y, int player) const {
    int score = 1;
        int count = 1;

        while ((x + count < row)) {
            if (boardInfo[y][x + count] == player) {
                score++;
                count++;
            } else {
                break;
            }
        }

        count = 1;
        while ((x - count >= 0)) {
            if (boardInfo[y][x - count] == player) {
                score++;
                count++;
            } else {
                break;
            }
        }

        return score >= 4;
}