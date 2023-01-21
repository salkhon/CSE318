#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Solver/Solver.hpp"

const std::string DATA_PATH = "../data/";

std::vector<int> read_course_file(std::string dataset) {
    std::string filepath = DATA_PATH + dataset + ".crs";
    std::ifstream ifs(filepath);
    std::vector<int> course_nstudents;

    if (ifs) {
        std::string _course, nstudents;
        while (ifs >> _course >> nstudents) {
            course_nstudents.push_back(std::atoi(nstudents.c_str())); //* course idx = course num - 1
        }
    }

    return course_nstudents;
}

std::vector<std::string> split_str(const std::string& str, const std::string& delim) {
    std::vector<std::string> split;
    int str_start = 0;
    for (int delim_pos = str.find(delim); delim_pos != std::string::npos; delim_pos = str.find(delim, str_start)) {
        split.push_back(str.substr(str_start, delim_pos - str_start));
        str_start = delim_pos + delim.length();
    }
    split.push_back(str.substr(str_start));
    return split;
}

std::string trim(std::string& str) {
    str.erase(str.find_last_not_of(' ') + 1);
    str.erase(0, str.find_first_not_of(' '));
    return str;
}

std::vector<int> course_str_to_idx(const std::vector<std::string>& vec_str) {
    std::vector<int> vec_int;
    for (std::string str : vec_str) {
        trim(str);
        if (str.empty()) {
            continue;
        }

        vec_int.push_back(std::atoi(str.c_str()) - 1); //* course idx = course num - 1
    }
    return vec_int;
}

std::vector<std::vector<int>> read_student_file(std::string dataset) {
    std::string filepath = DATA_PATH + dataset + ".stu";
    std::ifstream ifs(filepath);
    std::vector<std::vector<int>> student_courses;

    if (ifs) {
        std::string line, course_num;
        while (std::getline(ifs, line)) {
            student_courses.push_back(course_str_to_idx(split_str(line, " ")));
        }
    }

    return student_courses;
}

template<typename T>
void print_vec(std::vector<T> vec) {
    std::cout << "[ ";
    for (const auto& v : vec) {
        std::cout << v << ", ";
    }
    std::cout << "]" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Wrong argument format. Please pass in dataset name, penalty, constructive heuristic in order" << std::endl;
    }

    std::string dataset = argv[1];
    int penalty = std::atoi(argv[2]), constructive = std::atoi(argv[3]);

    auto course_nstudents = read_course_file(dataset);
    auto student_courses = read_student_file(dataset);

    Solver solver(course_nstudents, student_courses, (PenaltyType) penalty, (ConstructiveHeuristicType) constructive);
    solver.solve();

    std::cout << dataset << "," << solver.get_ntimeslots() << "," << solver.get_penalty_after_constructive() <<
        "," << solver.get_penalty_after_kempe() << "," << solver.get_penalty_after_pairswap() << std::endl;
    

    return 0;
}