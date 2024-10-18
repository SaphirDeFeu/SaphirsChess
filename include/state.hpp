#include<string>
#include"piece.hpp"

class State {
  public:
  inline State(std::string const& fen_string) noexcept;
  inline std::string to_fen_string() const noexcept;

  inline Piece* get_board() const noexcept;
  inline Piece::Color& get_ply_player() const noexcept;
  inline bool* get_castle_rights() const noexcept;
  inline unsigned char& get_en_passant() const noexcept;
  inline unsigned short& get_halfmove_clock() const noexcept;
  inline unsigned int& get_fullmove_clock() const noexcept;

  private:
  Piece board[64];
  Piece::Color ply_player = Piece::Color::WHITE;
  bool castle_rights[4] = { false, false, false, false };
  unsigned char en_passant = Square::NULL_SQUARE;
  unsigned short halfmove = 0;
  unsigned int fullmove = 1;
};

const std::string STARTING_POSITION_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

struct SetSizedPieceArray {
  Piece* p;
  unsigned int length;
};