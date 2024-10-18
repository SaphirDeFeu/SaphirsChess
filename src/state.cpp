#include<vector>
#include<sstream>

#include"state.hpp"

using std::string;
using std::vector;

inline vector<string> split_string(string const& str, char delimiter) {
  vector<string> result;
  std::stringstream ss(str);
  string item;

  while(std::getline(ss, item, delimiter)) {
    result.push_back(item);
  }

  return result;
};

State::State(string const& fen_string) noexcept {
  if(fen_string.empty())
    return;
  
  this->board = new Piece[64];
  this->castle_rights = new bool[4];
  castle_rights[0] = false;
  castle_rights[1] = false;
  castle_rights[2] = false;
  castle_rights[3] = false;

  size_t index = 56;
  size_t string_index = 0;
  vector<string> stages = split_string(fen_string, ' '); // split the fen string into multiple stages to treat each of them one at a time

  const size_t FIRST_LEN = stages.at(0).size();
  while(FIRST_LEN > string_index) {
    char current_character = stages.at(0).at(string_index);

    if(current_character == '/') { // new line
      index -= 16;
      string_index++;
      continue;
    }

    if(current_character >= '1' && current_character <= '8') { // we're tracking a number
      int num = current_character - '0'; // int conversion (trust me bro)
      for(int i = 0; i < num; i++) {
        this->board[index] = Piece('-');
        index++;
      }
      string_index++;
      continue;
    }

    Piece::Color color = Piece::Color::WHITE;
    if(current_character >= 'a' && current_character <= 'z') // Lowercase check
      color = Piece::Color::BLACK;

    char lowercase_character = current_character;
    if(current_character >= 'A' && current_character <= 'Z') lowercase_character = current_character + ('a' - 'A');

    Piece::Type type;
    switch(lowercase_character) {
      case 'p': type = Piece::Type::PAWN; break;
      case 'n': type = Piece::Type::KNIGHT; break;
      case 'b': type = Piece::Type::BISHOP; break;
      case 'r': type = Piece::Type::ROOK; break;
      case 'q': type = Piece::Type::QUEEN; break;
      case 'k': type = Piece::Type::KING; break;
      default: type = Piece::Type::NUL; break;
    };

    this->board[index] = Piece(type, color);

    index++;
    string_index++;
  }

  if(stages.at(1).at(0) == 'w') {
    this->ply_player = Piece::Color::WHITE;
  } else {
    this->ply_player = Piece::Color::BLACK;
  }

  if(stages.at(2).at(0) != '-') {
    for(char c : stages.at(2)) {
      switch(c) {
        case 'K': this->castle_rights[0] = true; break;
        case 'Q': this->castle_rights[1] = true; break;
        case 'k': this->castle_rights[2] = true; break;
        case 'q': this->castle_rights[3] = true; break;
      }
    }
  }

  if(stages.at(3).at(0) != '-') {
    char col = stages.at(3).at(0);
    char row = stages.at(3).at(1);
    vector<char> tmp;
    tmp.push_back(col);
    tmp.push_back(row);
    unsigned char sq = Square::from_vec(tmp);
    this->en_passant = sq;
  }

  unsigned short halfmoves = static_cast<unsigned short>(std::stoul(stages.at(4)));
  unsigned int fullmoves = static_cast<unsigned int>(std::stoul(stages.at(5)));
  this->halfmove = halfmoves;
  this->fullmove = fullmoves;
};

State::~State() noexcept {
  delete[] (this->board);
  delete[] (this->castle_rights);
}

Piece* State::get_board() const noexcept {
  return this->board;
}

bool* State::get_castle_rights() const noexcept {
  return this->castle_rights;
}

Piece::Color* State::get_ply_player() noexcept {
  return &this->ply_player;
}

unsigned char* State::get_en_passant() noexcept {
  return &this->en_passant;
}

unsigned short* State::get_halfmove_clock() noexcept {
  return &this->halfmove;
}

unsigned int* State::get_fullmove_clock() noexcept {
  return &this->fullmove;
}