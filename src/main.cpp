#include<iostream>
#include<vector>
#include<string>
#include<bitset>

#include"board.hpp"

int main() {
  // Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  Board board;

  std::cout << board.display() << std::endl;
  // int depth = 3;
  // std::cout << board.perft(depth) << std::endl;
  board.make_move(Movement::from_uci("e2e4"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("f1d3"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("g1f3"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("e1g1"));
  std::cout << board.display() << std::endl;
  return 0;
}