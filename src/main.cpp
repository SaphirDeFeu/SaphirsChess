#include<iostream>
#include<vector>
#include<string>
#include<bitset>

#include"board.hpp"

int main() {
  // Board board("rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 1");
  Board board;

  std::cout << board.display() << std::endl;
  return 0;
}