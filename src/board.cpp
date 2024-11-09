#include"board.hpp"
#include<vector>

using std::string;
using std::vector;

Board::Board(const string& fen_string) noexcept {
  state = new State(fen_string);
}

Board::~Board() noexcept {
  delete state;
}

string Board::get_fen() const noexcept {
  return this->state->to_fen_string();
}

string Board::display() const noexcept {
  string s;
  s += "  a   b   c   d   e   f   g   h\n";
  s += "+---+---+---+---+---+---+---+---+\n";
  int index = 56;

  for(int _ = 0; _ < 64; _++) {
    char _ucir = Piece::get_uci_representation(this->state->get_board()[index]);

    if(_ucir == '-') _ucir = ' ';
    s += "| ";
    s += _ucir;
    s += " ";

    if(index % 8 == 7) {
      index -= 16;
      s += "| ";
      s += static_cast<char>((index + 1) / 8) + '2';
      s += "\n+---+---+---+---+---+---+---+---+\n";
      if(index < -1) break;
    }

    index++;
  }

  s += "\nFEN: ";
  s += this->state->to_fen_string();

  return s;
}

void Board::make_move(const Movement::move& _m) noexcept {
  unsigned char start = _m & 0b111111;
  unsigned char target = (_m >> 6) & 0b111111;
  unsigned char promotion = (_m >> 12) & 0b111;

  taken_pieces.push_back(this->state->get_board()[target]);
  this->state->get_board()[target] = this->state->get_board()[start];
  this->state->get_board()[start] = Piece::_NULL;
  Piece::Type _p_type = static_cast<Piece::Type>(promotion);
  if(_p_type != Piece::Type::NUL) Piece::set_type(this->state->get_board()[target], static_cast<Piece::Type>(promotion));

  moves.push_back(_m);
}

void Board::unmake_move() noexcept {
  Movement::move _m = moves.at(moves.size() - 1);
  unsigned char start = _m & 0b111111;
  unsigned char target = (_m >> 6) & 0b111111;
  unsigned char promotion = (_m >> 12) & 0b111;

  if(promotion != 0) Piece::set_type(this->state->get_board()[target], Piece::Type::PAWN);
  this->state->get_board()[start] = this->state->get_board()[target];
  this->state->get_board()[target] = taken_pieces.at(taken_pieces.size() - 1);

  moves.pop_back();
  taken_pieces.pop_back();
}

Movement::move Movement::from_uci(const string& _ucir) noexcept {
  char arr[5] = {' ', ' ', ' ', ' ', '-'};
  vector<char> origin;
  vector<char> target;

  size_t MAX = _ucir.size();
  if(MAX > 5) MAX = 5;

  for(size_t i = 0; i < MAX; i++) {
    arr[i] = _ucir.at(i);
  }

  origin.push_back(arr[0]);
  origin.push_back(arr[1]);
  target.push_back(arr[2]);
  target.push_back(arr[3]);

  unsigned short us = 0;
  us = us | Square::from_vec(origin);
  us = us | Square::from_vec(target) << 6;
  us = us | Piece::get_type(Piece::make(arr[4])) << 12;

  return us;
}

string Movement::from_u16(const Movement::move& _us) noexcept {
  string s;

  unsigned short origin = _us & 0b111111;
  unsigned short target = (_us >> 6) & 0b111111;
  unsigned short promotion = (_us >> 12) & 0b111;
  Piece::Type promotion_type = Piece::Type::NUL;
  if(promotion >= 0 && promotion <= 6) promotion_type = static_cast<Piece::Type>(promotion);

  vector<char> o = Square::from_byte(static_cast<unsigned char>(origin));
  vector<char> t = Square::from_byte(static_cast<unsigned char>(target));
  char p = Piece::get_uci_representation(Piece::make(promotion_type, Piece::Color::BLACK));

  s += string(o.begin(), o.end());
  s += string(t.begin(), t.end());
  if(p != '-') s += p;

  return s;
}