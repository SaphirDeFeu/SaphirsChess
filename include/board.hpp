#include<string>
#include"state.hpp"

/**
 * 
 */
class Board {
  public:
  Board(const std::string& fen_string) noexcept;
  Board() noexcept : Board(STARTING_POSITION_FEN) {};
  ~Board() noexcept;
  /// @brief Calculates a FEN string from the current state
  /// @return a FEN string
  std::string get_fen() const noexcept;
  /// @brief Creates a nice-looking* string of the current state
  /// @return the string corresponding to the current state
  std::string display() const noexcept;

  private:
  State* state;
};

namespace Movement {
  /**
   * @brief Converts a UCI movement to the program's chosen representation
   * \code {.cpp}
   * std::string s = "e2e4"; // move from e2 to e4 square
   * unsigned short u = Movement::from_uci(s); // returns 0 000 011 100 001 100 (-4e2e)
   * \endcode
   * @param _ucir Any UCI movement following the format `crCRp` where `c`=start column ; `r`=start row ; `C`=target column ; `R`=target row ; `p`=promotion (can be omitted)
   * @return Unsigned short of notation: `xPPPTTTTTTSSSSSS` where `P`=Promotion ; `T`=Target ; `S`=Start
   */
  unsigned short from_uci(const std::string& _ucir) noexcept;

  /**
   * @brief Converts this program's chosen movement representation to human readable UCI notation
   * \code {.cpp}
   * unsigned short u = 0b0000011100001100; // see Movement::from_uci(const std::string& _ucir)
   * std::string s = Movement::from_u16(u);
   * \endcode
   * @param _us Unsigned short of notation: `xPPPTTTTTTSSSSSS` where `P`=Promotion ; `T`=Target ; `S`=Start
   * @return Corresponding UCI movement following the format `crCRp` where `c`=start column ; `r`=start row ; `C`=target column ; `R`=target row ; `p`=promotion (can be omitted)
   */
  std::string from_u16(const unsigned short& _us) noexcept;
}