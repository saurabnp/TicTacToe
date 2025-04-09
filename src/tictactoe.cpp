#include <iostream>
#include <string>
using namespace std;

class TicTacToe {
private:
    string player1;
    string player2;
    char board[9];
    int currentPlayer; // 0 for player1 (X), 1 for player2 (O)

public:
    TicTacToe();
    void start();

private:
    void getPlayerNames();
    void displayBoard();
    bool makeMove();
    bool isWinner();
    bool isDraw();
    void switchPlayer();
};

TicTacToe::TicTacToe() {
    for (int i = 0; i < 9; ++i) board[i] = '0' + i;
    currentPlayer = 0;
}

void TicTacToe::getPlayerNames() {
    cout << "Enter name for Player 1 (X): ";
    getline(cin, player1);
    cout << "Enter name for Player 2 (O): ";
    getline(cin, player2);
}

void TicTacToe::displayBoard() {
    cout << "\nCurrent Board:\n";
    for (int i = 0; i < 9; ++i) {
        cout << "|" << board[i];
        if (i % 3 == 2) cout << "|\n";
    }
}

bool TicTacToe::makeMove() {
    int pos;
    string currentPlayerName = currentPlayer == 0 ? player1 : player2;
    char symbol = currentPlayer == 0 ? 'X' : 'O';

    cout << currentPlayerName << "'s turn. Enter position (0-8): ";
    cin >> pos;

    while (cin.fail() || pos < 0 || pos > 8 || board[pos] == 'X' || board[pos] == 'O') {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Try again: ";
        cin >> pos;
    }

    board[pos] = symbol;
    return isWinner();
}

bool TicTacToe::isWinner() {
    const int wins[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    char symbol = currentPlayer == 0 ? 'X' : 'O';
    for (auto &line : wins) {
        if (board[line[0]] == symbol && board[line[1]] == symbol && board[line[2]] == symbol) {
            cout << (currentPlayer == 0 ? player1 : player2) << " wins!\n";
            return true;
        }
    }
    return false;
}

bool TicTacToe::isDraw() {
    for (char c : board) {
        if (c != 'X' && c != 'O') return false;
    }
    cout << "It's a draw!\n";
    return true;
}

void TicTacToe::switchPlayer() {
    currentPlayer = 1 - currentPlayer;
}

void TicTacToe::start() {
    getPlayerNames();
    displayBoard();

    while (true) {
        if (makeMove()) break;
        displayBoard();
        if (isDraw()) break;
        switchPlayer();
    }

    displayBoard();
    cout << "Game Over. Thanks for playing!\n";
}

int main() {
    TicTacToe game;
    game.start();
    return 0;
}
