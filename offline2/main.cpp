#include <iostream>
#include "CSPSolver/CSPSolver.hpp"
#include <string>
#include <vector>
#include <memory>
#include <fstream>

std::vector<std::string> split_str(std::string str, std::string delim) {
    std::vector<std::string> split;
    int str_start = 0;
    for (int delim_pos = str.find(delim); delim_pos != std::string::npos; delim_pos = str.find(delim, str_start)) {
        split.push_back(str.substr(str_start, delim_pos - str_start));
        str_start = delim_pos + delim.length();
    }
    split.push_back(str.substr(str_start));
    return split;
}

std::vector<std::vector<int>> read_board(const std::string path) {
    std::vector<std::vector<int>> board;
    std::ifstream file(path);
    if (file) {
        std::string line;
        std::getline(file, line);
        line.erase(0, 2); // remove "N="
        const int N = std::atoi(line.c_str());
        std::getline(file, line); // "start="
        std::getline(file, line); // "[|"

        std::vector<int> board_row;
        for (size_t i = 0; i < N; i++) {
            std::getline(file, line);
            if (i < N - 1) {
                line.erase(line.size() - 2, 2); // " |"
            } else {
                // lastline
                line.erase(line.size() - 4, 4); // " |];"
            }

            for (auto& num_str : split_str(line, ", ")) {
                board_row.push_back(std::atoi(num_str.c_str()));
            }
            board.push_back(board_row);
            board_row.clear();
        }
    }
    return board;
}

void print_board(const std::vector<std::vector<int>>& board) {
    std::cout << "------------------------" << std::endl;
    for (auto& row : board) {
        for (size_t col = 0; col < board.size(); col++) {
            std::cout << row[col] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}

int main() {
    const std::string DATA_PATH = "./data/d-15-01.txt";
    const int VOH = 1;

    std::vector<std::vector<int>> board = read_board(DATA_PATH);

    CSPSolver csp_solver(board, VOH);
    csp_solver.solve();
    print_board(csp_solver.solution_board);
    return 0;
}