// TicTicToe.h
#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>

class TicTacToe {
public:
    TicTacToe();
    void StartGame();

private:
    std::vector<std::vector<int> > fBoard;
    int fCurrentPlayer;

    void DisplayBoard() const;
    bool UpdateBoard(int row, int col);
    void SwitchPlayer();
    bool CheckIsWin() const;
    bool CheckIsDraw() const;
};

#endif // TICTACTOE_H