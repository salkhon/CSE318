#include "Board/Board.hpp"

class BoardFactory {
public:
    static std::unique_ptr<Board> move(std::unique_ptr<Board>, Move);
};

enum Move {
    LEFT, UP, RIGHT, DOWN
};