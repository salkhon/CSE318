#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "./Board/Board.hpp"
#include "./Board/BoardFactory/BoardFactory.hpp"
#include "./Solver/Solver.hpp"

int main() {
    std::ifstream input_file("./input.txt");
    if (input_file.is_open()) {
        int dim;
        input_file >> dim;
        std::vector<std::vector<int>> init_board_config(dim, std::vector<int>(dim, 0));

        std::string input;
        for (size_t i = 0; i < dim; i++) {
            for (size_t j = 0; j < dim; j++) {
                input_file >> input;
                if (input != "*" && input != "0") {
                    init_board_config[i][j] = std::stoi(input);
                } else {
                    init_board_config[i][j] = Board::BLANK;
                }
            }
        }

        // std::cout << *BoardFactory::init_board(init_board_config) << std::endl;

        Solver solver(dim, init_board_config);
        solver.solve();
    } else {
        std::cerr << "Could not open input file" << std::endl;
    }

    return 0;
}