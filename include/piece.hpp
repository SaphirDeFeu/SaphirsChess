#include<vector>

/**
 * @brief Class used to interpret and store individual piece data.
 * \code {.cpp}
 * Piece piece();
 * \endcode
 * 
 * @see Piece::Piece(Piece::Type _type, Piece::Color _color)
 * @see Piece::Piece()
 * @see Piece::Piece(unsigned char _ucir)
 */
class Piece {
  public:
  enum Type {
    /// @brief A `null` type - Equivalent to `-` or ` ` (numeric value: `0`)
    NUL    = 0b000,
    /// @brief Equivalent to `p` or `P` (numeric value: `1`)
    PAWN   = 0b001,
    /// @brief Equivalent to `n` or `N` (numeric value: `2`)
    KNIGHT = 0b010,
    /// @brief Equivalent to `b` or `B` (numeric value: `3`)
    BISHOP = 0b011,
    /// @brief Equivalent to `r` or `R` (numeric value: `4`)
    ROOK   = 0b100,
    /// @brief Equivalent to `q` or `Q` (numeric value: `5`)
    QUEEN  = 0b101,
    /// @brief Equivalent to `k` or `K` (numeric value: `6`)
    KING   = 0b110,
  };

  enum Color {
    /// @brief Forces lowercase on a piece (aka. colored black) (numeric value: `8`)
    BLACK = 0b1000,
    /// @brief Forces uppercase on a piece (aka. colored white) (numeric value: `0`) - In conjunction with \ref Piece::Type::NUL "Type::NUL" - represents a null piece
    WHITE = 0b0000,
  };

  /**
   * @brief Creates a piece of type `_type` and color `_color`
   * \code {.cpp}
   * Piece piece(Piece::Type::PAWN, Piece::Color::WHITE); // creates a white pawn
   * \endcode
   * 
   * @param _type  a `Piece::Type` value, represents this piece's type
   * @param _color a `Piece::Color` value, represents this piece's color
   */
  Piece(Type _type, Color _color) noexcept;

  /**
   * @brief Creates a piece of type \ref Piece::Type::NUL "Type::NUL" and of color \ref Piece::Color::WHITE "Color::WHITE"
   * \code {.cpp}
   * Piece piece(); // creates a null piece
   * \endcode
   * 
   * @overload
   */
  inline Piece() noexcept : Piece(Type::NUL, Color::WHITE) {};

  /**
   * @brief Creates a piece from its corresponding UCI representation
   * \code {.cpp}
   * Piece piece('q'); // creates a black queen
   * \endcode
   * 
   * @param _ucir The piece's UCI representation, with any character `pnbrqk` being its type, and its color being UPPERCASE=WHITE and LOWERCASE=BLACK. Can be `-` if null.
   * `_ucir` can be any letter in the string `pnbrqk` - `p`=pawn, `n`=knight, `b`=bishop, `r`=rook, `q`=queen, `k`=king. Making it uppercase renders it a white piece
   */
  Piece(unsigned char _ucir) noexcept;

  /**
   * @brief Gets the piece's representation according to UCI (or, the representation within a FEN string)
   * \code {.cpp}
   * piece.get_uci_representation(); // for a null piece, returns '-'
   * \endcode
   * 
   * @return Any character in `-pnbrqk` according to this piece's type (uppercase if the piece is white)
   */
  unsigned char get_uci_representation() const noexcept;

  /**
   * @brief Gets the piece's type
   * @return \ref Piece::Type "A Type value"
   */
  Type get_type() const noexcept;

  /**
   * @brief Gets the piece's color
   * @return \ref Piece::Color "A Color value"
   */
  Color get_color() const noexcept;

  private:
  /// @brief This piece's \ref Piece::Type "Type"
  Type type = Type::NUL;
  /// @brief This piece's \ref Piece::Color "Color"
  Color color = Color::WHITE;

};

namespace Square {
  /**
   * @brief Converts an unsigned 8-bit integer to a two-character vector (both representing a square's location on the board)
   * \code {.cpp}
   * std::vector<char> sq = Square::from_byte(0b010011); // returns the vector equivalent to [0b011, 0b010], or [3, 2], or ['d', '3']
   * std::string s(sq.begin(), sq.end()); // transforms the vector into a string
   * \endcode
   * 
   * @param byte According to the format `xNRRRCCC` where `N`=null? (1 if yes, 0 if not) ; `C`=column ; `R`=row
   * @return A vector of format `[C, R]` where `C`=column (as a `char` from `a-h`) ; `R`=row (as a `char` from `1-8`)
   * @see Square::from_vec
   */
  std::vector<char> from_byte(unsigned char const &byte) noexcept;
  
  /**
   * @brief Converts a two-character vector to an unsigned 8-bit integer (both representing a square's location on the board)
   * \code {.cpp}
   * std::vector<char> vec;
   * vec.push_back('d');
   * vec.push_back('4');
   * unsigned char sq = Square::from_vec(vec); // transforms 'd4' ['d', '4'] into the equivalent byte (0b011011)
   * \endcode
   * 
   * @param vec A vector of format `[C, R]` where `C`=column (as a `char` from `a-h`) ; `R`=row (as a `char` from `1-8`)
   * @return According to the format `xNRRRCCC` where `N`=null? (1 if yes, 0 if not) ; `C`=column ; `R`=row
   * @see Square::from_byte
   */
  unsigned char from_vec(std::vector<char> const &vec) noexcept;

  /// @brief An unsigned 8-bit integer that is always converted to `-` when using \ref Square::from_byte(unsigned char const& byte) "Square::from_byte(NULL_SQUARE)"
  const unsigned char NULL_SQUARE = 0b1000000;
}