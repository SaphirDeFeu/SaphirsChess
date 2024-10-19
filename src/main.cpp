#include<iostream>
#include<vector>
#include<string>
#include<bitset>

#include"board.hpp"

int main() {
  Board board;
  unsigned short i = Movement::from_uci("d7c8b");
  std::bitset<16> bitset(i);
  std::cout << bitset << " - " << i << std::endl << std::endl;
  std::cout << Movement::from_u16(i) << std::endl;
  return 0;
}