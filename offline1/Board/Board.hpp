#include <memory>
#include <vector>
#include <iostream>

class Board {
public:
    static const int BLANK = -1;

    const std::vector<std::vector<int>> board;
    const unsigned num_moves;
    const std::shared_ptr<Board> prev;

    Board(const std::vector<std::vector<int>>&, const unsigned, std::shared_ptr<Board>);
    size_t get_board_dim();

    std::ostream& operator<<(std::ostream&);
};
