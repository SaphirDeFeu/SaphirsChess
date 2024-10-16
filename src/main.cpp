#include<iostream>
#include"piece.hpp"

int main() {
  Piece piece = Piece(Piece::Type::NUL, Piece::Color::BLACK);
  std::cout << piece.getUCIRepresentation() << " " << std::endl;
  return 0;
}