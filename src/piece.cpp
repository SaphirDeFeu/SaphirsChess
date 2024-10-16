#include"piece.hpp"

Piece::Piece(Piece::Type _type, Piece::Color _color) {
  this->type = _type;
  this->color = _color;
}

Piece::Piece(unsigned char _ucir) {
  if(_ucir == '-') return;

  if('a' <= _ucir && _ucir <= 'z') {
    _ucir = (unsigned char) (((int) _ucir) - 32);
    this->color = Piece::Color::BLACK;
  };

  switch(_ucir) {
    case 'P': this->type = Piece::Type::PAWN; break;
    case 'N': this->type = Piece::Type::KNIGHT; break;
    case 'B': this->type = Piece::Type::BISHOP; break;
    case 'R': this->type = Piece::Type::ROOK; break;
    case 'Q': this->type = Piece::Type::QUEEN; break;
    case 'K': this->type = Piece::Type::KING; break;
    default: break;
  }
}

unsigned char Piece::getUCIRepresentation() {
  unsigned char code = '-';
  switch(this->type) {
    case Piece::Type::PAWN: code = 'p'; break;
    case Piece::Type::KNIGHT: code = 'n'; break;
    case Piece::Type::BISHOP: code = 'b'; break;
    case Piece::Type::ROOK: code = 'r'; break;
    case Piece::Type::QUEEN: code = 'q'; break;
    case Piece::Type::KING: code = 'k'; break;
    default: return code; break;
  }

  if(this->color == Piece::Color::WHITE) code -= ('a'-'A');

  return code;
}