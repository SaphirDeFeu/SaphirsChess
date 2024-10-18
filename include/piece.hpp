#include<vector>

class Piece {
  public:
  enum Type {
    NUL    = 0b000,
    PAWN   = 0b001,
    KNIGHT = 0b010,
    BISHOP = 0b011,
    ROOK   = 0b100,
    QUEEN  = 0b101,
    KING   = 0b110,
  };

  enum Color {
    BLACK = 0b1000,
    WHITE = 0b0000,
  };

  Piece(Type _type, Color _color) noexcept;
  Piece(unsigned char _ucir) noexcept;
  Piece() noexcept : Piece(Type::NUL, Color::WHITE) {};
  unsigned char get_uci_representation() const noexcept;

  private:
  Type type = Type::NUL;
  Color color = Color::WHITE;

};

namespace Square {
  std::vector<char> from_byte(unsigned char const &byte) noexcept;
  unsigned char from_vec(std::vector<char> const &vec) noexcept;

  const unsigned char NULL_SQUARE = 0b1000000;
}