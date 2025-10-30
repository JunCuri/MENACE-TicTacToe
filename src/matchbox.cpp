#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <random>
#include "board.h"
#include "matchbox.h"
using namespace std;

vector<Matchbox> memory;

void loadFromFile(std::vector<Matchbox>& memory, const std::string& filename) {
    ifstream file(filename);

    if(!file) {
        cerr << "Error: could not open file " << filename << "\n";
        return;
    }

    string line;
    memory.clear();

    while(getline(file, line)) {
        if(line.empty()) continue;

        size_t separator = line.find('|');
        if(separator == string::npos) continue;

        string boardStatus = line.substr(0, separator);
        string beadsStatus = line.substr(separator + 1);

        if(boardStatus.size() != 9) continue;

        Matchbox m;
        m.board.assign(boardStatus.begin(), boardStatus.begin() + 9);

        istringstream iss(beadsStatus);
        int val;
        while(iss >> val) m.beads.push_back(val);

        if(m.beads.size() == 9)
            memory.push_back(m);
    }
}

string toString(const vector<char>& currBoard) {
    string fullBoard;
    for (char c : currBoard) fullBoard.push_back(c);
    return fullBoard;
}

void saveToFile(vector<Matchbox>& memory, const string& filename) {
    ofstream file(filename);

    if(!file) {
        cerr << "Error: could not open file " << filename << "\n";
        return;
    }

    for (const auto& m : memory) {
        string fullBoard = toString(m.board);
        file << fullBoard << "|";
        for (size_t i = 0; i < m.beads.size(); ++i) {
            file << m.beads[i];
            if(i + 1 < m.beads.size()) file << ' ';
        }
        
        file << '\n';
    }

    file.close();
}

void initMatchboxFile(const string& filename) {
    ofstream file(filename);

    if(!file) {
        cerr << "Error: could not create " << filename << "\n";
        return;
    }

    const vector<char> symbols = {' ', 'X', 'O'};

    long long total = pow(3, 9);

    for (long long n = 0; n < total; ++n) {
        vector<char> board(9);
        long long temp = n;

        for (int i = 0; i < 9; i++) {
            board[i] = symbols[temp % 3];
            temp /= 3;
        }

        vector<int> beads(9);
        for (int i = 0; i < 9; ++i)
            beads[i] = 1;
        
        for (char c : board) file << c;
        file << "|";
        for (int i = 0; i < 9; i++) {
            file << beads[i];
            if(i < 8) file << ' ';
        }
            
        file << '\n';
    }

    file.close();
    cout << "Initialized " << total << " matchboxes in " << filename << "\n";
}

int getComputerMove(const std::vector<Matchbox>& memory, const std::vector<char>& currBoard) {
    for (const auto& m : memory) {
        if(m.board == currBoard) {
            vector<int> validMoves;
            vector<int> weights;

            for (int i = 0; i < 9; ++i) {
                if(m.board[i] == ' ') {
                    validMoves.push_back(i);
                    weights.push_back(max(1, m.beads[i]));
                }
            }

            random_device rd;
            mt19937 gen(rd());
            discrete_distribution<> dist(weights.begin(), weights.end());
            int chosenIndex = dist(gen);
            return validMoves[chosenIndex];
        }
    }

    return -1;
}

int getComputerMoveDeterminist(const std::vector<Matchbox>& memory, const std::vector<char>& currBoard) {
    for (const auto& m : memory) {
        if (m.board == currBoard) {
            vector<int> validMoves;
            vector<int> weights;

            for (int i = 0; i < 9; ++i) {
                if (m.board[i] == ' ') {
                    validMoves.push_back(i);
                    weights.push_back(max(1, m.beads[i]));
                }
            }
            int chosenIndex = 0, maxWeight = 0;
            for (size_t i = 0; i < weights.size(); i++) {
                if (weights.at(i) > maxWeight) {
                    maxWeight = weights.at(i);
                    chosenIndex = i;
                }
            }

            return validMoves[chosenIndex];
        }
    }

    return -1;
}

void updateLearning(std::vector<Matchbox>& memory, const std::vector<std::vector<char>>& gameBoards, const std::vector<int>& moves, int result) {
    int reward = 0;
    if(result == 1) reward = 2;
    else if(result == 0) reward = 1;
    else reward = -1;

    for (size_t t = 0; t < gameBoards.size(); ++t) {
        for (auto& m : memory) {
            if (m.board == gameBoards[t]) {
                int move = moves[t];
                m.beads[move] = max(0, m.beads[move] + reward);
                break;
            }
        }
    }
}