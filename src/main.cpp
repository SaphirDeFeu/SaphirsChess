#include<iostream>
#include<vector>
#include<string>

#include"board.hpp"

int main() {
  Board board;
  std::cout << board.get_fen() << std::endl;
  return 0;
}