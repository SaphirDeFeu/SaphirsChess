#include<iostream>
#include<vector>
#include<string>
#include<bitset>

#include"board.hpp"

int main() {
  // Board board("rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 1");
  Board board;

  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("a7a5"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("b7b5"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("c7c5"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("d7d5"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("e7e5"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("f7f5"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("g7g5"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("h7h5"));
  std::cout << board.display() << std::endl;
  // // std::cout << board.display() << std::endl;
  // board.make_move(Movement::from_uci("h7h5"));
  // std::cout << board.display() << std::endl;
  // board.make_move(Movement::from_uci("g1f3"));
  // std::cout << board.display() << std::endl;
  // board.make_move(Movement::from_uci("b8c6"));
  // std::cout << board.display() << std::endl;
  // board.make_move(Movement::from_uci("e4e5q"));
  // std::cout << board.display() << std::endl;

  // board.unmake_move();
  // std::cout << board.display() << std::endl;
  return 0;
}