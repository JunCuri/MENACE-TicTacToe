#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
    private:
    std::vector<char> board;

    public:
    Board() {
        for (int i = 0; i < 9; i++) {
            board.push_back(' ');
        }
    }
    std::vector<char> getBoard() const;
    bool checkState() const;
    void computerMove(char symbol, int move);
    void playerMove(char symbol);
    void printBoard() const;
};

#endif