#ifndef PIECE_HPP
#define PIECE_HPP

#pragma once
#include<vector>

/**
 * @brief Namespaced used to interpret and clear piece data.
 * \code {.cpp}
 * Piece::piece p = Piece::make();
 * \endcode
 * 
 * @see Piece::make(Piece::Type _type, Piece::Color _color)
 * @see Piece::make()
 * @see Piece::make(unsigned char _ucir)
 */

namespace Piece {
  using piece = unsigned char;

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

  enum Flag {
    /// @brief Flag to check if piece has ever moved
    HAS_MOVED = 0b10000,
    /// @brief Flag to check if in check
    CHECK     = 0b100000,
  };

  /**
   * @brief Creates a piece of type `_type` and color `_color`
   * \code {.cpp}
   * Piece::piece piece = make(Piece::Type::PAWN, Piece::Color::WHITE); // creates a white pawn
   * \endcode
   * 
   * @param _type  a `Piece::Type` value, represents this piece's type
   * @param _color a `Piece::Color` value, represents this piece's color
   */
  piece make(Type _type, Color _color) noexcept;

  /**
   * @brief Creates a piece from its corresponding UCI representation
   * \code {.cpp}
   * Piece::piece piece = make('q'); // creates a black queen
   * \endcode
   * 
   * @param _ucir The piece's UCI representation, with any character `pnbrqk` being its type, and its color being UPPERCASE=WHITE and LOWERCASE=BLACK. Can be `-` if null.
   * `_ucir` can be any letter in the string `pnbrqk` - `p`=pawn, `n`=knight, `b`=bishop, `r`=rook, `q`=queen, `k`=king. Making it uppercase renders it a white piece
   * 
   * @overload
   */
  piece make(unsigned char _ucir) noexcept;

  /**
   * @brief Gets the piece's representation according to UCI (or, the representation within a FEN string)
   * \code {.cpp}
   * get_uci_representation(piece); // for a null piece, returns '-'
   * \endcode
   * 
   * @param _p A \ref Piece::piece
   * 
   * @return Any character in `-pnbrqk` according to this piece's type (uppercase if the piece is white)
   */
  char get_uci_representation(const piece& _p) noexcept;

  /**
   * @brief Gets the piece's type
   * @param _p A \ref Piece::piece
   * @return \ref Piece::Type "A Type value"
   */
  Type get_type(const piece& _p) noexcept;

  /**
   * @brief Gets the piece's color
   * @param _p A \ref Piece::piece
   * @return \ref Piece::Color "A Color value"
   */
  Color get_color(const piece& _p) noexcept;

  /**
   * @brief Returns a selected flag of the piece
   * @param _p A \ref Piece::piece
   * @param _f Any \ref Piece::Flag
   * @return The value of said flag
   */
  bool get_flag(const piece& _p, Flag _f) noexcept;

  /**
   * @brief Sets a piece's color
   * @param _p A \ref Piece::piece "piece"
   * @param type A piece \ref Piece::Type "Type"
   */
  void set_type(piece& _p, Type type) noexcept;

  /**
   * @brief Sets a piece's color
   * @param _p A \ref Piece::piece "piece"
   * @param color A piece \ref Piece::Color "Color"
   */
  void set_color(piece& _p, Color color) noexcept;

  /**
   * @brief Sets a piece's color
   * @param _p A \ref Piece::piece "piece"
   * @param _f A \ref Piece::Flag "flag"
   * @param value The value of the flag to be set (1-bit only)
   */
  void set_flag(piece& _p, Flag _f, int value) noexcept;

  constexpr piece NIL = 0;
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
  constexpr unsigned char NULL_SQUARE = 0b1000000;
}

#endif