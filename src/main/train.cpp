#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "matchbox.h"
#include "board.h"
using namespace std;

int main() {
    srand(time(NULL));

    ifstream testO("data/tttdb_O.txt");
    if (!testO.good()) initMatchboxFile("data/tttdb_O.txt");
    testO.close();

    ifstream testX("data/tttdb_X.txt");
    if (!testX.good()) initMatchboxFile("data/tttdb_X.txt");
    testX.close();

    vector<Matchbox> memoryO;
    vector<Matchbox> memoryX;
    loadFromFile(memoryO, "data/tttdb_O.txt");
    loadFromFile(memoryX, "data/tttdb_X.txt");

    const int totalGames = 100000;
    int computerOWins = 0, computerXWins = 0, draws = 0;

    for (int g = 0; g < totalGames; ++g) {
        Board board;
        vector<vector<char>> boardsO, boardsX;
        vector<int> movesO, movesX;
        int move;
        int turn = 0;
        int winIndex = 0;

        while (true) {
            if (turn == 0) {
                boardsO.push_back(board.getBoard());
                move = getComputerMove(memoryO, board.getBoard());
                if (move == -1) break;
                board.computerMove('O', move);
                movesO.push_back(move);
                if (board.checkState()) {
                    winIndex = 1;
                    computerOWins++;
                    break;
                }
            } else {
                boardsX.push_back(board.getBoard());
                move = getComputerMove(memoryX, board.getBoard());
                if (move == -1) break;
                board.computerMove('X', move);
                movesX.push_back(move);
                if (board.checkState()) {
                    winIndex = -1;
                    computerXWins++;
                    break;
                }
            }

            bool full = true;
            for (char c : board.getBoard())
                if (c == ' ') full = false;
            if (full) {
                draws++;
                winIndex = 0;
                break;
            }

            turn = 1 - turn;
        }

        if (winIndex == 1) {
            updateLearning(memoryO, boardsO, movesO, 1);
            updateLearning(memoryX, boardsX, movesX, -1);
        } else if (winIndex == -1) {
            updateLearning(memoryO, boardsO, movesO, -1);
            updateLearning(memoryX, boardsX, movesX, 1);
        } else {
            updateLearning(memoryO, boardsO, movesO, 0);
            updateLearning(memoryX, boardsX, movesX, 0);
        }

        if ((g + 1) % 1000 == 0) {
            cout << "Game " << (g + 1)
                 << " / Wins by O: " << computerOWins
                 << " / Wins by X: " << computerXWins
                 << " / Draws: " << draws << endl;
        }
    }

    saveToFile(memoryO, "data/tttdb_O.txt");
    saveToFile(memoryX, "data/tttdb_X.txt");

    cout << "\n=== Training complete. ===\n";
    cout << "O wins: " << computerOWins
         << ", X wins: " << computerXWins
         << ", Draws: " << draws << endl;
}