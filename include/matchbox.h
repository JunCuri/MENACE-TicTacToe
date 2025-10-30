#ifndef MATCHBOX_H
#define MATCHBOX_H

#include <vector>
#include "board.h"

struct Matchbox {
    std::vector<char> board;
    std::vector<int> beads;
};

void initMatchboxFile(const std::string& filename);
void loadFromFile(std::vector<Matchbox>& memory, const std::string& filename);
void saveToFile(std::vector<Matchbox>& memory, const std::string& filename);
int getComputerMove(const std::vector<Matchbox>& memory, const std::vector<char>& currBoard);
int getComputerMoveDeterminist(const std::vector<Matchbox>& memory, const std::vector<char>& currBoard);
void updateLearning(std::vector<Matchbox>& memory, const std::vector<std::vector<char>>& gameBoards, const std::vector<int>& moves, int result);

#endif