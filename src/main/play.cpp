#include <iostream>
#include "matchbox.h"
#include "board.h"
#include <ctime>
#include <fstream>
#include <cstdlib>
using namespace std;

int main() {

    vector<Matchbox> memory;

    int games_count = 0;
    char continuePlay;

    do {
        vector<vector<char>> gameBoards;
        vector<int> gameMoves;
        loadFromFile(memory, "data/tttdb_O.txt");
        int count = 0, move, winIndex = 0;
        srand(time(NULL));
        Board board = Board();
        do {
            gameBoards.push_back(board.getBoard());
            move = getComputerMoveDeterminist(memory, board.getBoard());
            board.computerMove('O', move);
            gameMoves.push_back(move);
            board.printBoard();
            if(board.checkState()) {
                std::cout << "Computer wins!";
                winIndex = 1;
                break;
            }
            count++;
            if(!(count < 9)) {
                std::cout << "\n\nDraw!\n\n";
                break;
            }
            std::cout << "------------------------------------\n\n";
            board.playerMove('X');
            board.printBoard();
            if(board.checkState()) {
                std::cout << "You win!\n";
                winIndex = -1;
                break;
            }
            count++;
            std::cout << "------------------------------------\n\n";
    }while(count < 9);

    updateLearning(memory, gameBoards, gameMoves, winIndex);
    games_count++;
    std::cout << "Play again? y/n: ";
    cin >> continuePlay;

    }while(games_count < 200 && continuePlay != 'n');
}



