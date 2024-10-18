#include<iostream>
#include<vector>
#include<string>

#include"state.hpp"

int main() {
  State state(STARTING_POSITION_FEN);
  Piece* board = state.get_board();
  for(int i = 0; i < 64; i++) {
    std::cout << board[i].get_uci_representation() << std::endl;
    if(i % 8 == 7) std::cout << "/" << std::endl;
  }
  return 0;
}