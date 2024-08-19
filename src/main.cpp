#include "../include/IGames.h"
#include "../include/IReversi.h"
#include "../include/Player.h"
#include "../include/PlayerManager.h"
#include "../include/Utilitiies.h"
#include "../include/TicTacToe.hpp"
#include "../include/Connect4.hpp"
#include <iostream>
#include <sstream>
enum GameType {REVERSI, CONNECT4, TICTAC, NONE};

void printCommandList() {
    std::cout << "Comandos disponíveis:" << std::endl;
    std::cout << "1. Cadastrar Jogador" << std::endl;
    std::cout << "   Comando: CJ <nickname> <name>" << std::endl;
    std::cout << "   Descrição: Cadastra um novo jogador com o apelido e nome fornecidos." << std::endl;
    std::cout << std::endl;

    std::cout << "2. Remover Jogador" << std::endl;
    std::cout << "   Comando: RJ <nickname>" << std::endl;
    std::cout << "   Descrição: Remove um jogador existente pelo apelido fornecido." << std::endl;
    std::cout << std::endl;

    std::cout << "3. Listar Jogadores" << std::endl;
    std::cout << "   Comando: LJ <sortBy>" << std::endl;
    std::cout << "   Descrição: Lista todos os jogadores ordenados pelo critério especificado." << std::endl;
    std::cout << "   Critérios: 'A' para ordem alfabética pelo apelido, 'N' para ordem alfabética pelo nome." << std::endl;
    std::cout << std::endl;

    std::cout << "4. Executar Partida" << std::endl;
    std::cout << "   Comando: EP <gameType> <nickname1> <nickname2>" << std::endl;
    std::cout << "   Descrição: Inicia uma partida do tipo especificado com os dois jogadores fornecidos." << std::endl;
    std::cout << "   Tipo de Jogo: 'R' para Reversi, 'C' para Connect4 (a ser implementado)." << std::endl;
    std::cout << std::endl;

    std::cout << "5. Atualizar Jogador" << std::endl;
    std::cout << "   Comando: UP <option> <nickname> <newValue>" << std::endl;
    std::cout << "   Descrição: Atualiza o apelido ou nome de um jogador existente." << std::endl;
    std::cout << "   Opções: 'A' para atualizar o apelido, 'N' para atualizar o nome." << std::endl;
    std::cout << std::endl;

    std::cout << "6. Finalizar Sistema" << std::endl;
    std::cout << "   Comando: FS" << std::endl;
    std::cout << "   Descrição: Finaliza o sistema." << std::endl;
}

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
        std::cout << "BEM VINDOS AO REVERSI!!";
        std::cout << "Digite o tamanho do tabuleiro que voces queirem jogar, lembrem que dever ser um numero par" << std::endl;
        int size = 0;
        std::cin >> size;
        if(size <= 0 || size %2 !=0){
            std::cout << "Erro : Tabuleiro deve ter tamanho positivo e numero par de casas" << std::endl;
            std::cin >> size;
        }
        Reversi game(size, size, nickname1, nickname2); 
        game.startGame();
        while (!game.checkWin()) {
            game.readMove();
        }
    }
    else if(gameType == CONNECT4){
        std::cout << "BEM VINDOS AO CONNECT 4!!" << std::endl;
        std::cout << "Digite o tamanho do tabuleiro que voces queirem jogar, lembrem que deve ser um numero maior ou igual a 4" << std::endl;
        int col = 0;
        int row = 0;
        std::cin >> col;
        std::cin >> row;
        if(col < 4 && row < 4 ){
            std::cout << "Erro : Tabuleiro deve ter tamanho maior ou igual a 4" << std::endl;
            std::cin >> col;
            std::cin >>row;
        }
        try{
            Ligue4 game(col, row, nickname1, nickname2);
        }catch(const std::exception& e){
            std::cerr << e.what() << std::endl;
        }
    }else if(gameType == TICTAC){
        std::cout << "BEM VINDOS AO TICTACTOE!!" << std::endl;
        Board board; 
        TicTacToe game(board);
        game.Start(nickname1, nickname2);
    }
    
}




int main() {
    std::cout << "BEM VINDO AO HUB DE JOGOS DE TABULEIRO!!!!" << std::endl; 
    std::cout << "Caso queira, escreva H para ajuda" << std::endl;
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
            } else if(gameTypeChar == 'C') {
                gameType = CONNECT4;
            } else if(gameTypeChar == 'T'){
                gameType = TICTAC;
            } 
            else {
                std::cout << "ERRO: dados incorretos" << std::endl;
                continue;
            }

            executeGame(pm, gameType, nickname1, nickname2);
        } else if(command == "FS") { // Finalizar Sistema
            break;
        }else if(command == "UP"){     //Update de jogadores
            char option;
            iss >> option;
            
            std::string nickname;
            iss >> nickname;

            Player existingPlayer = pm.returnPlayerByNickname(nickname);
            if(existingPlayer.getNickname().empty()){
                std::cout << "ERRO: jogador inexistente" << std::endl;
                continue;
            }
            std::string newValue;
            std::getline (iss, newValue);
            if(!newValue.empty()){
                newValue = newValue.substr(1);
            }
            if(newValue.empty()){
                std::cout << "ERRO: Dados Incorretos" << std::endl;
                continue;
            }
            if(option == 'A'){
                existingPlayer.updateNickName(newValue);
                pm.updatePlayer(nickname, existingPlayer);
                std::cout <<"Apelido do jogador " << nickname << " atualizado com sucesso" << std::endl;
            }else if(option == 'N'){
                existingPlayer.updateName(newValue);
                pm.updatePlayer(nickname, existingPlayer);
                std::cout << "Nome do jogador " << nickname << " atualizado com sucesso" << std::endl;
            }
            else{
                std::cout << "ERRO: Opção desconhecida" << std::endl;
            }

        } else if(command == "H"){
                printCommandList();
        }
            else {
                std::cout << "ERRO: comando desconhecido" << std::endl;
        }
    }

    return 0;
}