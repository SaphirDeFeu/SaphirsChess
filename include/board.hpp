#include<string>
#include"state.hpp"

/**
 * Namespace for use to translate movements into the program's chosen syntax
 */
namespace Movement {
  using move = unsigned short;
  /**
   * @brief Converts a UCI movement to the program's chosen representation
   * \code {.cpp}
   * std::string s = "e2e4"; // move from e2 to e4 square
   * unsigned short u = Movement::from_uci(s); // returns 0 000 011 100 001 100 (-4e2e)
   * \endcode
   * @param _ucir Any UCI movement following the format `crCRp` where `c`=start column ; `r`=start row ; `C`=target column ; `R`=target row ; `p`=promotion (can be omitted)
   * @return Unsigned short of notation: `xPPPTTTTTTSSSSSS` where `P`=Promotion ; `T`=Target ; `S`=Start
   */
  move from_uci(const std::string& _ucir) noexcept;

  /**
   * @brief Converts this program's chosen movement representation to human readable UCI notation
   * \code {.cpp}
   * unsigned short u = 0b0000011100001100; // see Movement::from_uci(const std::string& _ucir)
   * std::string s = Movement::from_u16(u);
   * \endcode
   * @param _us Unsigned short of notation: `xPPPTTTTTTSSSSSS` where `P`=Promotion ; `T`=Target ; `S`=Start
   * @return Corresponding UCI movement following the format `crCRp` where `c`=start column ; `r`=start row ; `C`=target column ; `R`=target row ; `p`=promotion (can be omitted)
   */
  std::string from_u16(const move& _us) noexcept;
}

/**
 * Class used to interpret and interact with a chess board
 */
class Board {
  public:
  Board(const std::string& fen_string) noexcept;
  Board() noexcept : Board(STARTING_POSITION_FEN) {};
  ~Board() noexcept;
  /**
   * @brief Calculates a FEN string from the current state
   * @return a FEN string
   */
  std::string get_fen() const noexcept;
  /**
   * @brief Creates a nice-looking* string of the current state
   * @return the string corresponding to the current state
   */
  std::string display() const noexcept;

  /**
   * 
   */
  void generate_legal_moves() noexcept;

  /**
   * @brief Makes a move to the board that can be backtracked with \ref Board::unmake_move "Board::unmake_move"
   * @param _m A movement parsed from UCI into the program's trace (see \ref Movement::from_uci "Movement::from_uci()")
   */
  void make_move(const Movement::move& _m) noexcept;

  /**
   * @brief Backtracks the last move done on this board
   */
  void unmake_move() noexcept;

  private:
  State* state;
  std::vector<Movement::move> legal_moves = std::vector<Movement::move>();
  /**
   * Tracks all the moves done for each ply during this game
   */
  std::vector<Movement::move> moves = std::vector<Movement::move>();
  /**
   * Used in conjunction with \ref Board::moves "Board::moves". Used to track captured pieces for each ply of the game.
   */
  std::vector<Piece::piece> taken_pieces = std::vector<Piece::piece>();
};