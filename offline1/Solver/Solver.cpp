#include "Solver.hpp"

Solver::Solver(const size_t dim, std::vector<std::vector<int>> init_board_config)
    : DIM{ dim }, INIT_BOARD_CONFIG{ init_board_config }, GOAL_BOARD_CONFIG{ BoardFactory::get_goal_board(dim) },
    explored_nodes{ 0 }, expanded_nodes{ 0 } {
    std::cout << "GOAL\n\n" << *BoardFactory::init_board(GOAL_BOARD_CONFIG) << std::endl;
}

int Solver::hamming_dist(std::shared_ptr<Board> board_ptr) {
    size_t dist = 0;
    for (size_t i = 0; i < this->DIM; i++) {
        for (size_t j = 0; j < this->DIM; j++) {
            if (board_ptr->board_config[i][j] != this->GOAL_BOARD_CONFIG[i][j]) {
                dist++;
            }
        }
    }
    return dist;
}

int Solver::manhattan_dist(std::shared_ptr<Board> board_ptr) {
    int dist = 0;
    for (int row = 0; row < this->DIM; row++) {
        for (int col = 0; col < this->DIM; col++) {
            int val_row, val_col;
            if (board_ptr->board_config[row][col] != Board::BLANK) {
                val_row = (board_ptr->board_config[row][col] - 1) / this->DIM;
                val_col = (board_ptr->board_config[row][col] - 1) % this->DIM;
                dist += std::abs(row - val_row) + std::abs(col - val_col);
            }
        }
    }
    return dist;
}

bool Solver::is_solvable() {
    size_t num_inv = 0;
    for (size_t m = 0, r0, c0; m < this->DIM * this->DIM - 1; m++) {
        r0 = m / this->DIM;
        c0 = m % this->DIM;
        for (size_t n = m + 1, r1, c1; n < this->DIM * this->DIM; n++) {
            r1 = n / this->DIM;
            c1 = n % this->DIM;

            if (this->INIT_BOARD_CONFIG[r0][c0] != Board::BLANK && this->INIT_BOARD_CONFIG[r1][c1] != Board::BLANK &&
                this->INIT_BOARD_CONFIG[r0][c0] > this->INIT_BOARD_CONFIG[r1][c1]) {
                num_inv++;
            }
        }
    }

    if (this->DIM % 2 != 0) {
        return num_inv % 2 == 0;
    } else {
        size_t blank_row = 0;
        for (size_t i = 0; i < this->DIM; i++) {
            for (size_t j = 0; j < this->DIM; j++) {
                if (this->INIT_BOARD_CONFIG[i][j] == -1) {
                    blank_row = i;
                    break;
                }
            }
        }
        blank_row = this->DIM - blank_row;

        return (blank_row % 2 == 0 && num_inv % 2 != 0) || (blank_row % 2 != 0 && num_inv == 0);
    }
}

void Solver::print_moves(std::shared_ptr<Board> board_ptr, bool summary) {
    const std::shared_ptr<Board> end_board_ptr = board_ptr;
    if (!summary) {
        std::stack<std::shared_ptr<Board>> move_stack;
        while (board_ptr != nullptr) {
            move_stack.push(board_ptr);
            board_ptr = board_ptr->prev;
        }
        std::cout << "\n\n";
        while (!move_stack.empty()) {
            std::cout << *move_stack.top() << "\n\n";
            move_stack.pop();
        }
    }

    std::cout << "\n\nnum moves: " << end_board_ptr->num_moves << "\nexplored nodes: " << this->explored_nodes <<
        "\nexpanded nodes: " << this->expanded_nodes << std::endl;
}

void Solver::solve_helper(std::function< bool(std::shared_ptr<Board>, std::shared_ptr<Board>) > cmp) {
    if (!this->is_solvable()) {
        std::cout << "Not Solvable\n\n";
        return;
    }

    // max pq
    std::priority_queue<std::shared_ptr<Board>, std::vector<std::shared_ptr<Board>>, decltype(cmp)> pq(cmp);
    std::unordered_set<std::vector<std::vector<int>>, Board::BoardConfigHashFunction, Board::BoardConfigEqualsFunction> closed_board_configs;

    std::shared_ptr<Board> current;
    std::shared_ptr<Board> neighbor;
    Move move_enum;

    pq.push(BoardFactory::init_board(this->INIT_BOARD_CONFIG));
    closed_board_configs.insert(this->INIT_BOARD_CONFIG);
    while (!pq.empty()) {
        current = pq.top();
        pq.pop();
        explored_nodes++;
        if (current->board_config == this->GOAL_BOARD_CONFIG) {
            break;
        }

        for (int move = LEFT; move <= DOWN; move++) {
            move_enum = static_cast<Move>(move);
            if ((neighbor = BoardFactory::move_board(current, move_enum)) && !closed_board_configs.contains(neighbor->board_config)) {
                // std::cout << "Inserting: ----------\n" << *neighbor << std::endl;
                expanded_nodes++;
                pq.push(neighbor);
                closed_board_configs.insert(current->board_config);
            }
        }
    }

    if (current->board_config != this->GOAL_BOARD_CONFIG) {
        std::cout << "Could not find solution" << std::endl;
    } else {
        print_moves(current);
    }
}

void Solver::solve() {
    std::cout << "========================== Hamming =================================" << std::endl;
    auto cmp_hamming = [this](std::shared_ptr<Board> left, std::shared_ptr<Board> right) {
        return left->num_moves + this->hamming_dist(left) > right->num_moves + this->hamming_dist(right);
    };
    solve_helper(cmp_hamming);
    std::cout << "========================== X =================================\n" << std::endl;
    this->expanded_nodes = this->explored_nodes = 0;
    std::cout << "========================== Manhattan =================================" << std::endl;
    auto cmp_manhattan = [this](std::shared_ptr<Board> left, std::shared_ptr<Board> right) {
        return left->num_moves + this->manhattan_dist(left) > right->num_moves + this->manhattan_dist(right);
    };
    solve_helper(cmp_manhattan);
    std::cout << "========================== X =================================\n" << std::endl;
}