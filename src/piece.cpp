#include"piece.hpp"

using std::vector;

Piece::Piece(Piece::Type _type, Piece::Color _color) noexcept {
  this->type = _type;
  this->color = _color;
}

Piece::Piece(unsigned char _ucir) noexcept {
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

Piece::Piece() noexcept {
  this->type = Piece::Type::NUL;
  this->color = Piece::Color::WHITE;
}

unsigned char Piece::get_uci_representation() const noexcept {
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

unsigned char Square::from_vec(vector<char> const &vec) noexcept {
  if(vec.size() < 2) return 0;
  
  unsigned char row = vec.at(1) - '1';
  unsigned char col = vec.at(0) - 'a';
  
  if(row < 0 || row > 7) return 0;
  if(col < 0 || col > 7) return 0;

  return (row << 3) + col;
}

vector<char> Square::from_byte(unsigned char const &byte) noexcept {
  vector<char> vec = vector<char>();
  vec.push_back('-');
  if(byte == 0) return vec;

  char row = ((byte & 0b111000) >> 3) + '1';
  char col = (byte & 0b111) + 'a';

  if(col < 'a' || col > 'h') return vec;
  if(row < '1' || row > '8') return vec;

  vec.at(0) = col;
  vec.push_back(row);
  return vec;
}