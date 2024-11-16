#include"piece.hpp"

using std::vector;

Piece::piece Piece::make(Piece::Type _type, Piece::Color _color) noexcept {
  Piece::piece _p = 0;
  _p |= static_cast<unsigned char>(_type);
  _p |= static_cast<unsigned char>(_color);

  return _p;
}

Piece::piece Piece::make(unsigned char _ucir) noexcept {
  if(_ucir == '-') return 0;

  Piece::piece _p = 0;

  if('a' <= _ucir && _ucir <= 'z') {
    _ucir = static_cast<unsigned char>(static_cast<int>(_ucir) - 32);
    Piece::set_color(_p, Piece::Color::BLACK);
  };

  switch(_ucir) {
    case 'P': Piece::set_type(_p, Piece::Type::PAWN); break;
    case 'N': Piece::set_type(_p, Piece::Type::KNIGHT); break;
    case 'B': Piece::set_type(_p, Piece::Type::BISHOP); break;
    case 'R': Piece::set_type(_p, Piece::Type::ROOK); break;
    case 'Q': Piece::set_type(_p, Piece::Type::QUEEN); break;
    case 'K': Piece::set_type(_p, Piece::Type::KING); break;
    default: break;
  }

  return _p;
}

char Piece::get_uci_representation(const Piece::piece& _p) noexcept {
  char code = '-';
  switch(Piece::get_type(_p)) {
    case Piece::Type::PAWN: code = 'p'; break;
    case Piece::Type::KNIGHT: code = 'n'; break;
    case Piece::Type::BISHOP: code = 'b'; break;
    case Piece::Type::ROOK: code = 'r'; break;
    case Piece::Type::QUEEN: code = 'q'; break;
    case Piece::Type::KING: code = 'k'; break;
    default: return code;
  }

  if(Piece::get_color(_p) == Piece::Color::WHITE) code -= ('a'-'A');

  return code;
}

Piece::Type Piece::get_type(const Piece::piece& _p) noexcept {
  return static_cast<Piece::Type>(_p & 0b111);
}

Piece::Color Piece::get_color(const Piece::piece& _p) noexcept {
  return static_cast<Piece::Color>(_p & 0b1000);
}

bool Piece::get_flag(const Piece::piece& _p, Piece::Flag _f) noexcept {
  return (_p & _f) != 0;
}

void Piece::set_type(Piece::piece& _p, Piece::Type type) noexcept {
  _p &= 0b000;
  _p |= static_cast<unsigned char>(type);
}

void Piece::set_color(Piece::piece& _p, Piece::Color color) noexcept {
  _p &= 0b0111;
  _p |= static_cast<unsigned char>(color);
}

void Piece::set_flag(Piece::piece& _p, Piece::Flag _f, int value) noexcept {
  unsigned char flag_filter = 0b11111111 ^ _f;
  _p &= flag_filter;
  unsigned char val = value * 0b11111111; // converts value from a 1-bit boolean value into either all 1's or all 0's
  unsigned char or_value = val ^ flag_filter;
  _p |= or_value;
}

unsigned char Square::from_vec(vector<char> const &vec) noexcept {
  if(vec.size() < 2) return 0b1000000;
  
  unsigned char row = vec.at(1) - '1';
  unsigned char col = vec.at(0) - 'a';
  
  if(row < 0 || row > 7) return 0b1000000;
  if(col < 0 || col > 7) return 0b1000000;

  return (row << 3) + col;
}

vector<char> Square::from_byte(unsigned char const &byte) noexcept {
  vector<char> vec = vector<char>();
  vec.push_back('-');
  if(byte == 0b1000000) return vec;

  char row = ((byte & 0b111000) >> 3) + '1';
  char col = (byte & 0b111) + 'a';

  if(col < 'a' || col > 'h') return vec;
  if(row < '1' || row > '8') return vec;

  vec.at(0) = col;
  vec.push_back(row);
  return vec;
}