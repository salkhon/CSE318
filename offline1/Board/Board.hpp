#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <string>

struct Board {
    static const int BLANK = -1;

    const std::vector<std::vector<int>> board_config;
    const unsigned num_moves;
    const std::shared_ptr<Board> prev;

    Board(const std::vector<std::vector<int>>&, const unsigned, std::shared_ptr<Board>);
    size_t get_board_dim();

    struct BoardConfigEqualsFunction {
        bool operator()(std::vector<std::vector<int>> const&, std::vector<std::vector<int>> const&) const;
    };

    struct BoardConfigHashFunction {
        size_t operator()(std::vector<std::vector<int>> const&) const;
    };
};

std::ostream& operator<<(std::ostream&, const Board&);
