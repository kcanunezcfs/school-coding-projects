#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <limits>

class Board {
private:
    char board[8][8];

public:
    Board() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                board[i][j] = ' ';
            }
        }
    }

    void display() {
        std::cout << "   ";
        for (int i = 0; i < 8; ++i) {
            std::cout << " " << i << "  ";
        }
        std::cout << "\n";

        for (int i = 0; i < 8; ++i) {
            std::cout << "  +";
            for (int j = 0; j < 8; ++j) {
                std::cout << "---+";
            }
            std::cout << "\n";

            std::cout << i << " ";
            for (int j = 0; j < 8; ++j) {
                std::cout << "| " << board[i][j] << " ";
            }
            std::cout << "|\n";
        }

        std::cout << "  +";
        for (int j = 0; j < 8; ++j) {
            std::cout << "---+";
        }
        std::cout << "\n";
    }

    bool isValidMove(int row, int col) {
        return (row >= 0 && row < 8 && col >= 0 && col < 8 && board[row][col] == ' ');
    }

    void placeLetter(int row, int col, char letter) {
        if (isValidMove(row, col)) {
            board[row][col] = toupper(letter);
        }
    }

    char getLetter(int row, int col) {
        return board[row][col];
    }

    bool isFull() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};

class Player {
public:
    std::string name;
    int score;

    Player(std::string playerName) : name(playerName), score(0) {}

    void incrementScore() {
        ++score;
    }
};

class GameLogic {
public:
    static bool checkForSOS(Board &board, int row, int col, char letter) {
        bool foundSOS = false;
        if (letter == 'O') {
            if ((row >= 1 && row < 7 && board.getLetter(row - 1, col) == 'S' && board.getLetter(row + 1, col) == 'S') || // vertical
                (col >= 1 && col < 7 && board.getLetter(row, col - 1) == 'S' && board.getLetter(row, col + 1) == 'S') || // horizontal
                (row >= 1 && row < 7 && col >= 1 && col < 7 && board.getLetter(row - 1, col - 1) == 'S' && board.getLetter(row + 1, col + 1) == 'S') || // diagonal \ //
                (row >= 1 && row < 7 && col >= 1 && col < 7 && board.getLetter(row - 1, col + 1) == 'S' && board.getLetter(row + 1, col - 1) == 'S')) { // diagonal / //
                foundSOS = true;
            }
        } else if (letter == 'S'); {
            if ((row >= 0 && row < 6 && board.getLetter(row + 1, col) == 'O' && board.getLetter(row + 2, col) == 'S') || // vertical down
                (row >= 2 && row < 8 && board.getLetter(row - 1, col) == 'O' && board.getLetter(row - 2, col) == 'S') || // vertical up
                (col >= 0 && col < 6 && board.getLetter(row, col + 1) == 'O' && board.getLetter(row, col + 2) == 'S') || // horizontal right
                (col >= 2 && col < 8 && board.getLetter(row, col - 1) == 'O' && board.getLetter(row, col - 2) == 'S') || // horizontal left
                (row >= 0 && row < 6 && col >= 0 && col < 6 && board.getLetter(row + 1, col + 1) == 'O' && board.getLetter(row + 2, col + 2) == 'S') || // diagonal down-right
                (row >= 2 && row < 8 && col >= 2 && col < 8 && board.getLetter(row - 1, col - 1) == 'O' && board.getLetter(row - 2, col - 2) == 'S') || // diagonal up-left
                (row >= 0 && row < 6 && col >= 2 && col < 8 && board.getLetter(row + 1, col - 1) == 'O' && board.getLetter(row + 2, col - 2) == 'S') || // diagonal down-left
                (row >= 2 && row < 8 && col >= 0 && col < 6 && board.getLetter(row - 1, col + 1) == 'O' && board.getLetter(row - 2, col + 2) == 'S')) { // diagonal up-right
                foundSOS = true;
            }
        }
        return foundSOS;
    }
};

class IOHandler {
public:
    static void getMove(int &row, int &col, char &letter) {
        while (true) {
            std::cout << "Enter ROW (0-7): ";
            std::cin >> row;
            if (std::cin.fail() || row < 0 || row > 7) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid row. Please enter a number between 0 and 7.\n";
                continue;
            }

            std::cout << "Enter COLUMN (0-7): ";
            std::cin >> col;
            if (std::cin.fail() || col < 0 || col > 7) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid column. Please enter a number between 0 and 7.\n";
                continue;
            }

            std::cout << "Enter LETTER (S or O): ";
            std::cin >> letter;
            letter = toupper(letter);
            if (letter != 'S' && letter != 'O') {
                std::cout << "Invalid letter. Please enter 'S' or 'O'.\n";
                continue;
            }
            break;
        }
    }

    static void displayWinner(Player &player1, Player &player2) {
        std::cout << player1.name << " score: " << player1.score << "\n";
        std::cout << player2.name << " score: " << player2.score << "\n";
        if (player1.score > player2.score) {
            std::cout << player1.name << " wins!\n";
        } else if (player2.score > player1.score) {
            std::cout << player2.name << " wins!\n";
        } else {
            std::cout << "It's a draw!\n";
        }
    }

    static void displayScores(Player &player1, Player &player2) {
        std::cout << "\n";
        std::cout << player1.name << ": " << player1.score << " | ";
        std::cout << player2.name << ": " << player2.score << "\n";
        std::cout << "\n";
    }
};

int main() {
    Board board;
    Player player1("Player 1");
    Player player2("Player 2");
    bool isPlayer1Turn = true;

    while (true) {
        board.display();
        IOHandler::displayScores(player1, player2);
        Player &currentPlayer = isPlayer1Turn ? player1 : player2;
        std::cout << currentPlayer.name << "'s turn.\n";

        int row, col;
        char letter;
        IOHandler::getMove(row, col, letter);

        if (!board.isValidMove(row, col)) {
            std::cout << "\nInvalid move. Try again.\n";
            continue;
        }

        board.placeLetter(row, col, letter);

        if (GameLogic::checkForSOS(board, row, col, letter)) {
            currentPlayer.incrementScore();
            std::cout << currentPlayer.name << " scores!\n";
        } else {
            isPlayer1Turn = !isPlayer1Turn;
        }

        if (board.isFull()) {
            std::cout << "\nThe board is full. Game over!\n";
            break;
        }
    }

    board.display();
    IOHandler::displayWinner(player1, player2);

    return 0;
}
