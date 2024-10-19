#include<string>
#include"state.hpp"

class Board {
  public:
  Board(const std::string& fen_string) noexcept;
  Board() noexcept : Board(STARTING_POSITION_FEN) {};
  ~Board() noexcept;
  std::string get_fen() const noexcept;
  std::string display() const noexcept;

  private:
  State* state;
};

namespace Movement {
  /// @brief Converts a UCI movement to the program's chosen representation
  /// @param _ucir Any UCI movement following the format crCRp where c=start column ; r=start row ; C=target column ; R=target row ; p=promotion (can be omitted)
  /// @return Unsigned short of notation: xPPPTTTTTTSSSSSS where P=Promotion ; T=Target ; S=Start
  unsigned short from_uci(const std::string& _ucir) noexcept;
  /// @brief Converts this program's chosen movement representation to human readable UCI notation
  /// @param _us Unsigned short of notation: xPPPTTTTTTSSSSSS where P=Promotion ; T=Target ; S=Start
  /// @return Corresponding UCI movement following the format crCRp where c=start column ; r=start row ; C=target column ; R=target row ; p=promotion (can be omitted)
  std::string from_u16(const unsigned short& _us) noexcept;
}