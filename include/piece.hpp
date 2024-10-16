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

  Piece(Type _type, Color _color);
  Piece(unsigned char _ucir);
  unsigned char getUCIRepresentation();

  private:
  Type type = Type::NUL;
  Color color = Color::WHITE;

};