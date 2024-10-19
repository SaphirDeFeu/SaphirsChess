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
    unsigned char _ucir = this->state->get_board()[index].get_uci_representation();

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

unsigned short Movement::from_uci(const string& _ucir) noexcept {
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
  us = us | Piece(arr[4]).get_type() << 12;

  return us;
}

string Movement::from_u16(const unsigned short& _us) noexcept {
  string s;

  unsigned short origin = _us & 0b111111;
  unsigned short target = (_us >> 6) & 0b111111;
  unsigned short promotion = (_us >> 12) & 0b111;
  Piece::Type promotion_type = Piece::Type::NUL;
  if(promotion >= 0 && promotion <= 6) promotion_type = static_cast<Piece::Type>(promotion);

  vector<char> o = Square::from_byte(static_cast<unsigned char>(origin));
  vector<char> t = Square::from_byte(static_cast<unsigned char>(target));
  unsigned char p = Piece(promotion_type, Piece::Color::BLACK).get_uci_representation();

  s += string(o.begin(), o.end());
  s += string(t.begin(), t.end());
  if(p != '-') s += p;

  return s;
}