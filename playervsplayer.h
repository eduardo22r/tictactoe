#ifndef PLAYERVSPPLAYERTICTACTOE_H
#define PLAYERVSPPLAYERTICTACTOE_H

#include "tictactoe.h"
using namespace std;
using namespace std::chrono;

class PlayerVsPlayerTicTacToe : public TicTacToe {
public:
  PlayerVsPlayerTicTacToe();
  ~PlayerVsPlayerTicTacToe() override = default;

  void play();
};

#endif // PLAYERVSPPLAYERTICTACTOE_H



#include <stdexcept> // For invalid_argument

PlayerVsPlayerTicTacToe::PlayerVsPlayerTicTacToe() : TicTacToe() {}

void PlayerVsPlayerTicTacToe::play() {
  startGameTimer();
  while (!gameOver()) {
    printBoard();
    cout << "Player " << currentPlayer
              << ", enter your move (row and column): ";
    int row, col;
    cin >> row >> col;

    if (cin.fail()) {
      cin.clear(); 
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
      throw invalid_argument("Invalid input. Please enter integers.");
    }

    if (isValidMove(row, col)) {
      makeMove(row, col);
      if (checkWin()) {
        printBoard();
        cout << currentPlayer << " wins!" << endl;
        isGameOver = true;
      } else if (checkDraw()) {
        printBoard();
        cout << "Draw!" << endl;
        isGameOver = true;
      }
      switchPlayer();
    } else {
      cout << "Invalid. Try again." << endl;
    }
  }
}
