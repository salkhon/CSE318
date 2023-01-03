#include <iostream>
#include "CSPSolver/CSPSolver.hpp"
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include <fstream>
#include <ctime>
#include <cctype>

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

void trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(),
        [](char c) {
            return !std::isspace(c);
        }
    ));
    str.erase(std::find_if(str.rbegin(), str.rend(),
        [](char c) {
            return !std::isspace(c);
        }
    ).base(), str.end());
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

            for (auto& num_str : split_str(line, ",")) {
                trim(num_str);
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

enum SolverType {
    SIMPLE_BACKTRACKING, FORWARD_CHECKING
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "CSP solver needs Solver type, Variable order heuristic and Data path as argument." << std::endl;
        return 1;
    }

    bool is_forward_check = std::strcmp(argv[1], std::to_string(FORWARD_CHECKING).c_str()) == 0;
    const int VOH = std::atoi(argv[2]);
    const std::string DATA_PATH = argv[3];

    std::vector<std::vector<int>> board = read_board(DATA_PATH);
    // print_board(board);

    CSPSolver csp_solver(board, VOH, is_forward_check);

    clock_t start, end;

    start = clock();
    bool is_success = csp_solver.solve();
    end = clock();

    double exectime = double(end - start) / double(CLOCKS_PER_SEC);

    if (is_success) {
        std::cout << csp_solver.num_nodes << "," << csp_solver.num_backtrack << "," << exectime;
        // print_board(csp_solver.solution_board);
    } else {
        std::cout << -2 << "," << -2 << "," << -2;
        // std::cout << "NO SOLUTION" << std::endl;
    }
    
    return 0;
}