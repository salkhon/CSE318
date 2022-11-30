#include <memory>
#include <vector>

class Board {
    const std::vector<std::vector<int>> board;
    const unsigned num_moves;
    const std::unique_ptr<Board> prev;

public:
    Board(const std::vector<std::vector<int>>&, const unsigned, std::unique_ptr<Board>);
};

