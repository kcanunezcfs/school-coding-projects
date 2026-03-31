SOS Game (C++ – 8x8 Board)

This project is a console-based SOS game developed in C++, where two players compete to form the sequence “SOS” on an 8×8 grid. The game emphasizes strategic placement of letters and rewards players for successfully forming “SOS” patterns in multiple directions.

The implementation uses object-oriented programming with separate classes for the board, players, game logic, and input/output handling.

Features:
8×8 interactive game board displayed in the console
Two-player turn-based gameplay
Players can place either ‘S’ or ‘O’ on each turn
Automatic detection of “SOS” sequences:
Horizontal
Vertical
Diagonal
Score tracking system
Input validation for moves and letters
Game ends when the board is full

How It Works:
The game initializes an empty 8×8 board.
Players take turns entering:
Row (0–7)
Column (0–7)
Letter (S or O)
After each move:
The program checks if an “SOS” pattern is formed
If yes → player earns a point and plays again
If not → turn switches to the other player
The game continues until the board is completely filled
The player with the highest score wins

The main gameplay loop repeatedly displays the board, collects input, updates the state, and checks for scoring conditions.