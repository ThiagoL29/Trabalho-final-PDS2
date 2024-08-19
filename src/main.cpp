#include "../include/IGames.h"
#include "../include/IReversi.h"
#include "../include/Player.h"
#include "../include/PlayerManager.h"
#include "../include/Utilitiies.h"
#include "TicTacBoard.hpp"
#include "TicTacToe.hpp"
#include "Connect4Board.hpp"
#include "Connect4.hpp"
#include <iostream>
#include <sstream>
enum GameType {REVERSI, LIG4, TICTACTOE};

void printPlayerList(PlayerManager& pm, char sortBy) {
    pm.printPlayers(sortBy);
}

void executeGame(PlayerManager& pm, GameType gameType, const std::string& nickname1, const std::string& nickname2) {
    Player player1 = pm.returnPlayerByNickname(nickname1);
    Player player2 = pm.returnPlayerByNickname(nickname2);

    if (player1.getNickname().empty() || player2.getNickname().empty()) {
        std::cout << "ERRO: jogador inexistente" << std::endl;
        return;
    }

    if (gameType == REVERSI) {
        int size = 0;
        std::cin >> size;
        if(size <= 0 || size %2 !=0){
            std::cout << "Erro : Tabuleiro deve ter tamanho positivo e numero par de casas" << std::endl;
            std::cin >> size;
        }
        Reversi game(size, size, nickname1, nickname2); // Assume tamanho padrão 8x8 para Reversi
        game.startGame();
        while (!game.checkWin()) {
            game.printBoard();
            game.readMove();
        }
    }

    if (gameType == LIG4) {
        cout << "Digite o tamanho de linhas e colunas que você deseja no tabuleiro, respectivamente: " << endl;
        int row, col;
        cin >> row >> col;
        Ligue4 lig4(row, col);
    }

    if (gameType == TICTACTOE) {
        Board board;
        TicTacToe game(board);
        game.Start();
    }

}




int main() {
    PlayerManager pm;
    std::string line;

    while (true) { 
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "CJ") { // Cadastrar Jogador
            std::string nickname, name;
            iss >> nickname;
            std::getline(iss, name);
            name = name.substr(1); // Remove espaço extra no início

            if (nickname.empty() || name.empty()) {
                std::cout << "ERRO: dados incorretos" << std::endl;
                continue;
            }

            Player newPlayer(name, nickname);
            pm.addPlayer(newPlayer);
            Player existingPlayer = pm.returnPlayerByNickname(nickname);
            bool playerAddedSuccessfully = !existingPlayer.getNickname().empty();
            if (playerAddedSuccessfully) {
                std::cout << "Jogador " << nickname << " cadastrado com sucesso" << std::endl;
            } else {
                std::cout << "ERRO: jogador repetido" << std::endl;
            }
        }else if(command == "RJ") { // Remover Jogador
                std::string nickname;
                iss >> nickname;

                Player existingPlayer = pm.returnPlayerByNickname(nickname);
                bool playerExists = !existingPlayer.getNickname().empty();
                bool removalSuccessful = false;

                if (playerExists) {
                    std::cout << nickname << std::endl;
                    pm.removePlayer(nickname);
                    Player checkPlayer = pm.returnPlayerByNickname(nickname);
                    removalSuccessful = checkPlayer.getNickname().empty();
                }

                if (!playerExists) {
                    std::cout << "ERRO: jogador inexistente" << std::endl;
                }else if(removalSuccessful) {
                    std::cout << "Jogador " << nickname << " removido com sucesso" << std::endl;
                }else{
                    std::cout << "ERRO: jogador inexistente" << std::endl;
                }
        
        } else if (command == "LJ") { // Listar Jogadores
            char sortBy;
            iss >> sortBy;
            if (sortBy == 'A' || sortBy == 'N') {
                printPlayerList(pm, sortBy);
            } else {
                std::cout << "ERRO: dados incorretos" << std::endl;
            }
        } else if (command == "EP") { // Executar Partida
            char gameTypeChar;
            std::string nickname1, nickname2;
            iss >> gameTypeChar >> nickname1 >> nickname2;

            GameType gameType = NONE;
            if (gameTypeChar == 'R') {
                gameType = REVERSI;
            } else if (gameTypeChar == 'L') {
                gameType = LIG4;
            } else if (gameTypeChar == 'T') {
                gameType = TICTACTOE;
            }else{
                std::cout << "ERRO: dados incorretos" << std::endl;
                continue;
            }

            executeGame(pm, gameType, nickname1, nickname2);
        } else if(command == "FS") { // Finalizar Sistema
            break;
        }else if(command == "UP"){     //UPDATE DE JOGADORES
            std::string nickname;
            iss >> nickname;
            Player existingPlayer = pm.returnPlayerByNickname(nickname);
            if(existingPlayer.getNickname().empty()){
                std::cout << "ERRO: jogador inexistente" << std::endl;
                continue;
            }
            std::string newName;
            std::getline (iss, newName);
            if(!newName.empty()){
                newName = newName.substr(1);
            }
            if(newName.empty()){
                std::cout << "ERRO: Dados Incorretos" << std::endl;
                continue;
            }
            Player updatePlayer(newName, nickname);
            pm.updatePlayer(updatePlayer);
            std::cout << "Jogador " << nickname << " atualizado com sucesso " << std::endl;
        } 
            else {
            std::cout << "ERRO: comando desconhecido" << std::endl;
        }
    }

    return 0;
}