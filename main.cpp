#include "playervsplayer.h"
#include <iostream>
#include <stdexcept> 

int main() {
  
  
  
  PlayerVsPlayerTicTacToe* gamePtr = nullptr;
  gamePtr = new PlayerVsPlayerTicTacToe();
  
  try {
    gamePtr->play();
  } catch (const invalid_argument& e) {
    cerr << "Invalid argument: " << e.what() << endl;
  } catch (const out_of_range& e) {
    cerr << "Out of range: " << e.what() << endl;
  } catch (const exception& e) {
    cerr << "Exception caught: " << e.what() << endl;
  } catch (...) {
    cerr << "Unknown exception caught" << endl;
  }
  
  delete gamePtr;

  string playAgain;

  cout << "Game Over! Do you want to play again? (y/n): ";
  cin >> playAgain;
  while(playAgain == "y"){
    gamePtr = new PlayerVsPlayerTicTacToe();
    gamePtr->play();
  }
    
  return 0;
}


