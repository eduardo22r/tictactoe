#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <iostream>
#include <stdexcept> // For std::invalid_argument and std::out_of_range
using namespace std;
using namespace std::chrono;

class Game {
protected:
  time_point<steady_clock> gameStartTime;
  const seconds gameTimeLimit{60}; // 1 minute for the entire game

public:
  Game();
  virtual ~Game() = default;

  void startGameTimer();
  bool isGameTimeExpired();
  void handleGameTimeout();
  void printTimers();
};

#endif // GAME_H


Game::Game() {}

void Game::startGameTimer() {
  gameStartTime =steady_clock::now();
}


bool Game::isGameTimeExpired() {
  auto now = steady_clock::now();
  auto elapsed =duration_cast<seconds>(now - gameStartTime);
  return elapsed >= gameTimeLimit;
}


void Game::handleGameTimeout() {
  throw runtime_error("Game time limit exceeded");
}

void Game::printTimers() {
  auto now = steady_clock::now();
  auto gameElapsed = duration_cast<seconds>(now - gameStartTime);
  cout << "Game timer: " << gameTimeLimit.count() - gameElapsed.count() << " seconds remaining\n";
}
