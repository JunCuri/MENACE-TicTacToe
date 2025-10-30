#include <iostream>
#include <vector>
#include <cstdlib>
#include "matchbox.h"
#include "board.h"
using namespace std;

vector<char> Board::getBoard() const {
    return board;
}

bool Board::checkState() const {
    int index = 4;
    vector<char> cur_board = getBoard();
    if(cur_board.at(index) != ' ')
        for (int i = 1; i < 5; i++)
            if(cur_board.at(index - i) == cur_board.at(index) && cur_board.at(index + i) == cur_board.at(index)) return true;
    
    for (int i = 0; i < 9; i += 6)
        if(cur_board.at(i) != ' ')
            if(cur_board.at(i + 1) == cur_board.at(i) && cur_board.at(i + 2) == cur_board.at(i)) return true;
    
    for (int i = 0; i < 3; i += 2)
        if(cur_board.at(i) != ' ')
            if(cur_board.at(i + 3) == cur_board.at(i) && cur_board.at(i + 6) == cur_board.at(i)) return true;

    return false;
}

void Board::computerMove(char symbol, int move) {
    board.at(move) = symbol;
    return;
}

void Board::playerMove(char symbol) {
    int tile;
    while(true) {
        cout << "Select your tile (1 - 9): ";
        cin >> tile;
        if(tile < 1 || tile > 9) {
            cout << "Invalid value, please enter a number between 1 and 9.\n\n";
            continue;
        }
    
        if(board.at(tile - 1) == ' ') {
            board.at(tile - 1) = symbol;
            return;
        }

        cout << "This tile is already in use, please select another tile.\n\n";
    }
}

void Board::printBoard() const {
    for (int i = 0; i < 9; i++) {
        cout << board.at(i) << "  ";
        if((i == 2) || (i == 5) || (i == 8)) cout << "\n";
    }
}