#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "game.h"
#include <stdexcept> // For invalid_argument

using namespace std;
using namespace chrono;

class TicTacToe : public Game {
protected:
  char board[3][3];   // 3x3 Tic-Tac-Toe board
  char currentPlayer; // 'X' or 'O'
  bool isGameOver;

public:
  TicTacToe();
  virtual ~TicTacToe() = default;

  void play();
  bool isValidMove(int row, int col);
  void makeMove(int row, int col);
  void printBoard();
  bool checkWin();
  bool checkDraw();
  void switchPlayer();
  bool gameOver();
};

#endif // TICTACTOE_H


TicTacToe::TicTacToe() {
  currentPlayer = 'X';
  isGameOver = false;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      board[i][j] = ' ';
    }
  }
}

void TicTacToe::play() {
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
        cout << "Player " << currentPlayer << " wins!" << endl;
        isGameOver = true;
      } else if (checkDraw()) {
        printBoard();
        cout << "It's a draw!" << endl;
        isGameOver = true;
      }
      switchPlayer();
    } else {
      cout << "Invalid move! Try again." << endl;
    }
  }
}

bool TicTacToe::isValidMove(int row, int col) {
  return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}

void TicTacToe::makeMove(int row, int col) {
  board[row][col] = currentPlayer;
}

void TicTacToe::printBoard() {

  
  cout << "Current board:\n";
  cout << "-------------" << endl;
  for (int i = 0; i < 3; ++i) {
    cout << "| ";
    for (int j = 0; j < 3; ++j) {
      cout << board[i][j] << " | ";
    }
    cout << endl << "-------------" << endl;
  }
  printTimers();
}

bool TicTacToe::checkWin() {
  for (int i = 0; i < 3; ++i) {
    if (board[i][0] == currentPlayer && board[i][1] == currentPlayer &&
        board[i][2] == currentPlayer) {
      return true; // Row win
    }
    if (board[0][i] == currentPlayer && board[1][i] == currentPlayer &&
        board[2][i] == currentPlayer) {
      return true; // Column win
    }
  }
  if (board[0][0] == currentPlayer && board[1][1] == currentPlayer &&
      board[2][2] == currentPlayer) {
    return true; // Diagonal (top-left to bottom-right) win
  }
  if (board[0][2] == currentPlayer && board[1][1] == currentPlayer &&
      board[2][0] == currentPlayer) {
    return true; // Diagonal (top-right to bottom-left) win
  }
  return false;
}

bool TicTacToe::checkDraw() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (board[i][j] == ' ') {
        return false;
      }
    }
  }
  return true;
}

void TicTacToe::switchPlayer() {
  currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool TicTacToe::gameOver() {
  return isGameOver || isGameTimeExpired();
}
