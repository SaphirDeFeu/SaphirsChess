#include"board.hpp"
#include<vector>
#include<algorithm>
#include<iostream>
#include<cmath>

using std::string;
using std::vector;

Board::Board(const string& fen_string) noexcept {
  state = new State(fen_string);
  generate_legal_moves();
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

void Board::generate_sliding_moves(
    State* s,
    int* row_offsets,
    int* col_offsets,
    const int& sq,
    const Piece::piece& og_piece,
    int len,
    std::vector<Movement::move>* legal_moves) noexcept 
  {

  int row = (sq >> 3) & 0b111;
  int col = sq & 0b111;
  Piece::Color piece_color = Piece::get_color(og_piece);

  for(int dir = 0; dir < len; dir++) {
    int target = sq;
    int new_row = row;
    int new_col = col;

    int depth = 7;
    if(Piece::get_type(og_piece) == Piece::Type::KING) depth = 1;
    for(int i = 0; i < depth; i++) {
      new_row += row_offsets[dir];
      new_col += col_offsets[dir];
      if(new_row < 0 || new_row > 7 || new_col < 0 || new_col > 7) break;

      target = (new_row << 3) | new_col; // add offsets to reach the target square
      Piece::piece _p = s->get_board()[target];
      if(Piece::get_type(_p) == Piece::Type::NUL) {
        Movement::move mv = (target << 6) | sq;
        legal_moves->push_back(mv);
        continue;
      }

      // Not an empty space
      if(Piece::get_color(_p) == piece_color) break;
      else if(Piece::get_type(_p) == Piece::Type::KING) {
        Piece::set_flag(_p, Piece::Flag::CHECK, 1);
        break;
      } else {
        Movement::move mv = (target << 6) | sq;
        legal_moves->push_back(mv);
        break;
      }
    }
  }
}

void Board::generate_legal_moves() noexcept {
  this->legal_moves = generate_pseudolegal_moves(this->state);
  remove_pseudolegal_moves();
}

void Board::remove_pseudolegal_moves() noexcept {
  // Pseudo legal moves include :
  // - Moving into a check
  // - Leaving your king checked and not doing anything about it
  // - Moving out of the way of an attack that threatens your king

  // Getting the king
  // State* next_state = new State(this->state);
  // Piece::Color cl = *next_state->get_ply_player();
  // Piece::Color enemy = static_cast<Piece::Color>(static_cast<char>(cl) ^ 0b1000);
  

}

std::vector<Movement::move> Board::generate_pseudolegal_moves(State* s) noexcept {
  std::vector<Movement::move> legal_moves;

  for(int sq = 0; sq < 64; sq++) {
    int row = (sq >> 3) & 0b111;
    int col = sq & 0b111;

    Piece::piece current_piece = s->get_board()[sq];
    Piece::Type piece_type = Piece::get_type(current_piece);
    if(piece_type == Piece::Type::NUL) continue;
    Piece::Color piece_color = Piece::get_color(current_piece);
    if(piece_color != *s->get_ply_player()) continue;

    switch(piece_type) {

      case Piece::Type::PAWN: {
        int row_offset = 8;
        if(piece_color == Piece::Color::BLACK) row_offset *= -1;
        int col_offset = 1;

        // squares to be checked are : the one in front, the one after the one in front, the one to our left & the one to our right
        int squares_to_check[4] = { sq + row_offset, sq + row_offset * 2, sq + row_offset - col_offset, sq + row_offset + col_offset };
        int squares_allowed[4] = { true, true, false, false };

        if(s->get_board()[squares_to_check[1]] != Piece::Type::NUL) { // no free space 2 steps ahead of us
          squares_allowed[1] = false;

          if(s->get_board()[squares_to_check[0]] != Piece::Type::NUL) squares_allowed[0] = false; // no free space 1 step ahead of us
        }

        if(Piece::get_flag(current_piece, Piece::Flag::HAS_MOVED)) { // already moved, can't move 2 spaces ahead
          squares_allowed[1] = false;
        }

        Piece::piece left_piece = s->get_board()[squares_to_check[2]];
        if(Piece::get_color(left_piece) != piece_color && Piece::get_type(left_piece) != Piece::Type::NUL) {
          squares_allowed[2] = true;
          if(Piece::get_type(left_piece) == Piece::Type::KING) Piece::set_flag(left_piece, Piece::Flag::CHECK, 1);
        }
        if(squares_to_check[2] == *s->get_en_passant()) {
          if(Piece::get_color(s->get_board()[squares_to_check[2] + row_offset]) != piece_color) squares_allowed[2] = true;
        }

        Piece::piece right_piece = s->get_board()[squares_to_check[3]];
        if(Piece::get_color(right_piece) != piece_color && Piece::get_type(right_piece) != Piece::Type::NUL) {
          squares_allowed[3] = true;
          if(Piece::get_type(right_piece) == Piece::Type::KING) Piece::set_flag(right_piece, Piece::Flag::CHECK, 1);
        }
        if(squares_to_check[3] == *s->get_en_passant()) {
          if(Piece::get_color(s->get_board()[squares_to_check[3] + row_offset]) != piece_color) squares_allowed[3] = true;
        }

        // Check if we aren't going outside the board, by checking if all three of those moves are on the same row. If not, one must have somehow wrapped around the board
        if((squares_to_check[2] & 0b111000) != (squares_to_check[0] & 0b111000)) squares_allowed[2] = false;
        if((squares_to_check[3] & 0b111000) != (squares_to_check[0] & 0b111000)) squares_allowed[3] = false;

        // Once we finished our checks, add thingies to add to legal moves

        for(int i = 0; i < 4; i++) {
          if(squares_allowed[i] == false) continue;
          int target = squares_to_check[i];
          int origin = sq;
          Movement::move mv = (target << 6) | origin;
          legal_moves.push_back(mv);
        }

        break;
      }
      
      case Piece::Type::KNIGHT: {
        int row_offsets[8] = { row + 2, row + 2, row + 1, row - 1, row - 2, row - 2, row - 1, row + 1 };
        int col_offsets[8] = { col - 1, col + 1, col + 2, col + 2, col + 1, col - 1, col - 2, col - 2 };

        // Filter out spaces that go beyond the board's layout
        for(int i = 0; i < 8; i++) {
          if(row_offsets[i] > 7 || row_offsets[i] < 0 || col_offsets[i] > 7 || col_offsets[i] < 0) {
            row_offsets[i] = -1;
            col_offsets[i] = -1;
          };
        }

        // Restrict them into a single array of possibilities
        int options[8];
        for(int i = 0; i < 8; i++) {
          if(row_offsets[i] < 0 || col_offsets[i] < 0) {
            options[i] = -1;
            continue;
          };
          options[i] = (row_offsets[i] << 3) | col_offsets[i];

          Piece::piece _p = s->get_board()[options[i]];
          if(Piece::get_color(_p) == piece_color && Piece::get_type(_p) != Piece::Type::NUL) options[i] = -1;

          if(Piece::get_type(_p) == Piece::Type::KING && Piece::get_color(_p) != piece_color) Piece::set_flag(_p, Piece::Flag::CHECK, 1);
        }

        for(int i = 0; i < 8; i++) {
          if(options[i] == -1) continue;
          Movement::move mv = (options[i] << 6) | sq;
          legal_moves.push_back(mv);
        }

        break;
      }
      
      case Piece::Type::BISHOP: {
        int row_offsets[4] = { 1, -1, -1, 1 };
        int col_offsets[4] = { 1, 1, -1, -1 };
        generate_sliding_moves(s, row_offsets, col_offsets, sq, current_piece, 4, &legal_moves);
        break;
      }
      
      case Piece::Type::ROOK: {
        int row_offsets[4] = { 1, 0, -1, 0 };
        int col_offsets[4] = { 0, 1, 0, -1 };
        generate_sliding_moves(s, row_offsets, col_offsets, sq, current_piece, 4, &legal_moves);
        break;
      }
      
      case Piece::Type::QUEEN: {
        int row_offsets[8] = { 1, 0, -1, 0, 1, -1, -1, 1 };
        int col_offsets[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };
        generate_sliding_moves(s, row_offsets, col_offsets, sq, current_piece, 8, &legal_moves);
        break;
      }

      case Piece::Type::KING: {
        int row_offsets[8] = { 1, 0, -1, 0, 1, -1, -1, 1 };
        int col_offsets[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };
        generate_sliding_moves(s, row_offsets, col_offsets, sq, current_piece, 8, &legal_moves);

        int queenside = 0b01;
        int color = static_cast<int>(piece_color) >> 2;
        
        int c_square = (row << 3) | 2;
        int g_square = (row << 3) | 6;

        if(s->get_castle_rights()[color | queenside]) {
          if(
            Piece::get_type(s->get_board()[sq - 1]) == Piece::Type::NUL &&
            Piece::get_type(s->get_board()[sq - 2]) == Piece::Type::NUL &&
            Piece::get_type(s->get_board()[sq - 3]) == Piece::Type::NUL) {
              Movement::move mv = (c_square << 6) | sq;
              legal_moves.push_back(mv);
            }
        }
        if(s->get_castle_rights()[color]) {
          if(
            Piece::get_type(s->get_board()[sq + 1]) == Piece::Type::NUL &&
            Piece::get_type(s->get_board()[sq + 2]) == Piece::Type::NUL) {
              Movement::move mv = (g_square << 6) | sq;
              legal_moves.push_back(mv);
            }
        }
        break;
      }
      default: break;
    }
  }

  return legal_moves;
}

// ! Oh boy I do sure hope there are *no memory leaks* :D

void Board::make_move(const Movement::move& _m) noexcept {
  Movement::move root_move = _m & 0b111111111111; // Remove promotion part
  // Basically means "if not in legal_moves"
  if(std::find(this->legal_moves.begin(), this->legal_moves.end(), root_move) == this->legal_moves.end()) return;

  states.push_back(this->state);
  this->state = new State(this->state);

  unsigned char start = _m & 0b111111;
  unsigned char target = (_m >> 6) & 0b111111;
  unsigned char promotion = (_m >> 12) & 0b111;

  bool reset_halfmove = false;

  reset_halfmove = reset_halfmove || (Piece::get_type(this->state->get_board()[target]) != Piece::Type::NUL);
  reset_halfmove = reset_halfmove || (Piece::get_type(this->state->get_board()[start]) == Piece::Type::PAWN);

  int row_difference = ((target >> 3) & 0b111) - ((start >> 3) & 0b111);
  if(abs(row_difference) == 2 && Piece::get_type(this->state->get_board()[start]) == Piece::Type::PAWN) {
    int en_passant_sq = start + (row_difference / 2 * 8); // divide by 2 to get 1 row difference, multiply by 8 to get overall add/sub squares
    *this->state->get_en_passant() = en_passant_sq;
  } else {
    *this->state->get_en_passant() = Square::NULL_SQUARE;
  }

  int col_difference = (target & 0b111) - (start & 0b111);

  // Castling
  if(abs(col_difference) == 2 && Piece::get_type(this->state->get_board()[start]) == Piece::Type::KING) {
    unsigned char target_col = target & 0b111;
    unsigned char rook_col = 0;
    unsigned char rook_dest_col = 3;
    if(target_col == 6) { rook_col = 7; rook_dest_col = 5; }

    unsigned char rook_square = (target & 0b111000) | rook_col;
    unsigned char rook_dest_square = (target & 0b111000) | rook_dest_col;

    short color = static_cast<short>(Piece::get_color(this->state->get_board()[start])) >> 2;

    this->state->get_castle_rights()[color] = false;
    this->state->get_castle_rights()[color | 1] = false;

    this->state->get_board()[rook_dest_square] = this->state->get_board()[rook_square];
    this->state->get_board()[rook_square] = Piece::_NULL;

    Piece::set_flag(this->state->get_board()[rook_dest_square], Piece::Flag::HAS_MOVED, 1); 
  }

  if(Piece::get_flag(this->state->get_board()[start], Piece::Flag::HAS_MOVED) == 0 &&
    Piece::get_type(this->state->get_board()[start]) == Piece::Type::ROOK) {
      short color = static_cast<short>(Piece::get_color(this->state->get_board()[start])) >> 2;
      unsigned char col = start & 0b111;

      short queenside = 0;
      if(col == 0) queenside = 1;

      this->state->get_castle_rights()[color | queenside] = false;
  }

  Piece::set_flag(this->state->get_board()[start], Piece::Flag::HAS_MOVED, 1);

  this->state->get_board()[target] = this->state->get_board()[start];
  this->state->get_board()[start] = Piece::_NULL;
  Piece::Type _p_type = static_cast<Piece::Type>(promotion);
  if(_p_type != Piece::Type::NUL) Piece::set_type(this->state->get_board()[target], static_cast<Piece::Type>(promotion));

  unsigned char pc = static_cast<unsigned char>(*this->state->get_ply_player());
  pc ^= 0b1000;
  *this->state->get_ply_player() = static_cast<Piece::Color>(pc);

  if(reset_halfmove) *this->state->get_halfmove_clock() = 0;
  else (*this->state->get_halfmove_clock())++;

  if(*this->state->get_ply_player() == Piece::Color::WHITE) (*this->state->get_fullmove_clock())++;

  generate_legal_moves();
}

void Board::unmake_move() noexcept {
  delete this->state;
  this->state = states.at(states.size() - 1);

  states.pop_back();
  generate_legal_moves();
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

size_t Board::perft(size_t depth) noexcept {
  if(depth == 0) return 1;

  size_t positions = 0;

  size_t SIZE = this->legal_moves.size();
  for(size_t i = 0; i < SIZE; i++) {
    make_move(this->legal_moves.at(i));
    positions += perft(depth - 1);
    unmake_move();
  }

  return positions;
}
