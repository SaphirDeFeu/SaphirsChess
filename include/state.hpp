#include<string>
#include"piece.hpp"

const std::string STARTING_POSITION_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class State {
  public:
  State(std::string const& fen_string) noexcept;
  State() noexcept : State(STARTING_POSITION_FEN) {};
  ~State() noexcept;
  std::string to_fen_string() const noexcept;

  Piece* get_board() const noexcept;
  Piece::Color* get_ply_player() noexcept;
  bool* get_castle_rights() const noexcept;
  unsigned char* get_en_passant() noexcept;
  unsigned short* get_halfmove_clock() noexcept;
  unsigned int* get_fullmove_clock() noexcept;

  private:
  Piece* board;
  Piece::Color ply_player = Piece::Color::WHITE;
  bool* castle_rights;
  unsigned char en_passant = Square::NULL_SQUARE;
  unsigned short halfmove = 0;
  unsigned int fullmove = 1;
};