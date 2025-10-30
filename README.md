# MENACE — Tic-Tac-Toe Reinforcement Learning (C++)

A modern C++ implementation of **MENACE** (*Matchbox Educable Noughts and Crosses Engine*) —  
one of the earliest examples of **reinforcement learning**, originally created by **Donald Michie (1961)**.

---

## Overview

MENACE learns to play Tic-Tac-Toe through **trial and error**.  
Each unique board state is stored as a *matchbox* that contains a set of *beads*,  
representing the number of times each move was successful.

After each game:
- **Win** → MENACE adds beads to the chosen moves (reward)  
- **Loss** → MENACE removes beads (punishment)  
- **Draw** → Minor or no change  

Over many games, even when playing against itself, MENACE converges toward a **perfect Tic-Tac-Toe strategy**, ending almost all games in a draw.

---

## How It Works

| Concept | Description |
|----------|--------------|
| **Matchbox** | Represents a specific board configuration |
| **Beads** | Integers that weight each possible move |
| **Reinforcement** | Bead counts are adjusted based on win/loss outcomes |
| **Learning** | The system improves with each game, requiring no hard-coded strategy |

> This project demonstrates the foundations of **reinforcement learning**; learning optimal behavior via rewards and penalties, without any neural networks.

---

## Building & Running

### Prerequisites
- **C++17 or later**
- **make** and **g++**
- Works on Windows (MinGW), Linux, or macOS

### Build
```bash
make all
```

### Play against MENACE
```bash
make play
./play
```

### Train MENACE (self-play)
```bash
make train
./train
```

### Learning Behavior
MENACE starts with all moves equally likely.
As it plays more games:

- It reinforces moves that lead to wins.

- It avoids losing sequences.

- It eventually plays flawlessly, always drawing against another perfect player.

You can visualize progress by inspecting the data/tttdb_O.txt (or data/tttdb_X.txt) file as the agent trains.

### Key Functions
- getComputerMove() => Chooses a move based on current bead weights (stochastic)
- getComputerMoveDeterminist() => Chooses the best move deterministically.
- updateLearning() => Adjusts beads after each game based on outcome.
- loadFromFile() & saveToFile() => Handles persistent memory of all matchboxes.

## Author
### Jun Curi
Second-year Computer Science student exploring reinforcement learning through C++
- Project started: 2025
- Inspired by Donald Michie’s MENACE (1961)

### Future Improvements
- Visual interface for the board

- Statistical tracking of learning progress

- Smarter training heuristics

- Export/import learned models

### License
This project is open-source and free to use for educational and research purposes.