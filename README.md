# MENACE Tic Tac Toe

A self-learning Tic Tac Toe AI inspired by Donald Michie’s **MENACE** (Matchbox Educable Noughts And Crosses Engine).  
This program learns optimal play through reinforcement based on wins, losses, and draws.

## How it works
Each possible Tic Tac Toe board state is stored as a “matchbox” with beads representing possible moves.
- Winning moves gain beads (reinforcement)
- Losing moves lose beads (punishment)
- Drawing slightly rewards moves

After enough self-play, the AI converges to **perfect play (always draws or wins)**.

## How to run

### Build
Make sure you have a C++ compiler (g++) and `make`.

```bash
make train
make play
