#include <queue>
#include <memory>
#include "Board/Board.hpp"
#include "Board/BoardFactory/BoardFactory.hpp"

class Solver {
public:
    const size_t dim;
    Solver(const size_t dim);
    int hamming_dist(std::shared_ptr<Board>, std::shared_ptr<Board>);
    int manhattan_dist(std::shared_ptr<Board>, std::shared_ptr<Board>);

    void solve(std::shared_ptr<Board>);
};