#include<iostream>
#include<vector>
#include<string>
#include<bitset>

#include"board.hpp"

int main() {
  Board board("rnbqkbnr/pppppppp/8/8/4B3/8/PPPPPPPP/RNBQK1NR w KQkq - 0 1");
  // Board board;

  std::cout << board.display() << std::endl;
  return 0;
}