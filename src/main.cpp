#include<iostream>
#include<vector>
#include<string>

#include"state.hpp"

int main() {
  State state(STARTING_POSITION_FEN);
  std::cout << state.to_fen_string() << std::endl;
  return 0;
}