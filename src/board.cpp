#include"board.hpp"

using std::string;

Board::Board(const string& fen_string) noexcept {
  state = new State(fen_string);
}

Board::~Board() noexcept {
  delete state;
}

string Board::get_fen() const noexcept {
  return this->state->to_fen_string();
}