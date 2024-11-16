// TicTicToe.cpp
#include <iostream>
#include <string>

#include "TicTacToe.h"

using namespace std;

namespace {
    const int BOARD_SIZE = 3;
    const string SEPARATOR = "-------------";
    const char SPACER = '|';

    enum Player {
        kEmpty = 0,
        kPlayerX = 1,
        kPlayerO = 2,
    };

    const char PlayerString(int player) {
        switch (player) {
            case kPlayerX:
                return 'X';
            case kPlayerO:
                return 'O';
            default:
                return ' ';
        }
    }

    bool CheckLine(const vector<int>& players) {
        if (players.empty() || players[0] == kEmpty) {
            return false;
        }
        for (auto player : players) {
            if (player != players[0]) {
                return false;
            }
        }
        return true;
    }
}

TicTacToe::TicTacToe() : fBoard(BOARD_SIZE, vector<int>(BOARD_SIZE, kEmpty)), fCurrentPlayer(kPlayerX) {}

void TicTacToe::StartGame() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    int row, col;
    while (true) {
        DisplayBoard();
        cout << "Player " << fCurrentPlayer << "'s turn. Enter row and column (0-2): ";
        cin >> row >> col;

        if (!UpdateBoard(row, col)) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        if (CheckIsWin()) {
            DisplayBoard();
            cout << "Player " << PlayerString(fCurrentPlayer) << " wins!" << endl;
            break;
        }
        if (CheckIsDraw()) {
            DisplayBoard();
            cout << "It's a draw!" << endl;
            break;
        }

        SwitchPlayer();
    }
}

void TicTacToe::DisplayBoard() const {
    cout << SEPARATOR << endl;
    for (int i=0; i<BOARD_SIZE; ++i) {
        cout << SPACER;
        for (int j=0; j<BOARD_SIZE; ++j) {
            cout << PlayerString(fBoard[i][j]) << SPACER;
        }
        cout << endl;
        cout << SEPARATOR << endl;
    }
}

bool TicTacToe::UpdateBoard(int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || fBoard[row][col] != kEmpty) {
        return false;
    }
    fBoard[row][col] = fCurrentPlayer;
    return true;
}

void TicTacToe::SwitchPlayer() {
    fCurrentPlayer = (fCurrentPlayer == kPlayerX) ? kPlayerO : kPlayerX;
}

bool TicTacToe::CheckIsWin() const {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        vector<int> column;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            column.push_back(fBoard[j][i]);
        }
        if (CheckLine(fBoard[i]) || CheckLine(column)) return true;
    }

    // Check diagonal
    vector<int> mainDiagonal, antiDiagonal;
    for (int i=0; i<BOARD_SIZE; ++i) {
        mainDiagonal.push_back(fBoard[i][i]);
        antiDiagonal.push_back(fBoard[i][BOARD_SIZE - i - 1]);
    }
    if (CheckLine(mainDiagonal) || CheckLine(antiDiagonal)) return true;

    return false;
}

bool TicTacToe::CheckIsDraw() const {
    for (int i=0; i<BOARD_SIZE; ++i) {
        for (int j=0; j<BOARD_SIZE; ++j) {
            if (fBoard[i][j] == kEmpty) {
                return false;
            }
        }
    }
    return true;
}