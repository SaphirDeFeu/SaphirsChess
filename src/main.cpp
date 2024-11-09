#include<iostream>
#include<vector>
#include<string>
#include<bitset>

#include"board.hpp"

int main() {
  Board board;
  Movement::move i = Movement::from_uci("e2e4");
  std::bitset<16> bitset(i);
  std::cout << bitset << " - " << i << std::endl << std::endl;
  std::cout << Movement::from_u16(i) << std::endl;

  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("e2e4"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("e7e5"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("g1f3"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("b8c6"));
  std::cout << board.display() << std::endl;
  board.make_move(Movement::from_uci("e4e5q"));
  std::cout << board.display() << std::endl;

  board.unmake_move();
  std::cout << board.display() << std::endl;
  return 0;
}