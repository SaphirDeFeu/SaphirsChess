#include"state.hpp"

using std::string;

inline State::State(string const& fen_string) noexcept {
  if(fen_string.empty()) return;

  int index = 56;
  int string_index = 0;
  string stages[];
  /*if(fen == null) throw new IllegalArgumentException("fen cannot be null");
        GameState gameState = new GameState();

        int index = 56;
        int stringIndex = 0;
        String[] stages = fen.split(" ");

        while(stages[0].length() > stringIndex) {
            char currentCharacter = stages[0].charAt(stringIndex);
            String currentCharString = String.format("%c", currentCharacter);

            if(currentCharacter == '/') {
                index -= 16;
                stringIndex++;
                continue;
            }

            try {
                int num = Integer.parseInt(currentCharString);
                for(int i = 0; i < num; i++) {
                    gameState.getBoard()[index] = null;
                    index++;
                }
                stringIndex++;
                continue;
            } catch(Exception ignored) {}

            Piece.Color color = Piece.Color.WHITE;
            if(currentCharString.toLowerCase().equals(currentCharString)) color = Piece.Color.BLACK;

            Piece.Type type = switch(currentCharString.toLowerCase()) {
                case "p" -> Piece.Type.PAWN;
                case "n" -> Piece.Type.KNIGHT;
                case "b" -> Piece.Type.BISHOP;
                case "r" -> Piece.Type.ROOK;
                case "q" -> Piece.Type.QUEEN;
                case "k" -> Piece.Type.KING;
                default -> null;
            };

            gameState.getBoard()[index] = new Piece(type, color);

            index++;
            stringIndex++;
        }

        if(stages[1].equals("w")) {
            gameState.setPlyPlayer(Piece.Color.WHITE);
        } else {
            gameState.setPlyPlayer(Piece.Color.BLACK);
        }

        if(!stages[2].equals("-")) {
            for(String s : stages[2].split("(?!^)")) {
                char c = s.charAt(0);
                switch(c) {
                    case 'K' -> gameState.getCastleRights()[0] = true;
                    case 'Q' -> gameState.getCastleRights()[1] = true;
                    case 'k' -> gameState.getCastleRights()[2] = true;
                    case 'q' -> gameState.getCastleRights()[3] = true;
                }
            }
        }

        if(!stages[3].equals("-")) {
            char col = stages[3].charAt(0);
            char row = stages[3].charAt(1);
            byte sq = Square.fromAlgebraicNotation(col, row);
            gameState.setEnPassant(sq);
        }

        try {
            final byte halfmove = Byte.parseByte(stages[4]);
            final int fullmove = Integer.parseInt(stages[5]);
            gameState.setHalfmoveClock(halfmove);
            gameState.setFullmove(fullmove);
        } catch (NumberFormatException ignored) {}

        return gameState; */
};