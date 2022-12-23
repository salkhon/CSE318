#pragma once
#include "../defs.hpp"
#include <vector>
#include "../CSP/CSP.hpp"

/**
 * @brief Variable consists of a domain in internal (1, N), based on search progress. It may also contain a value
 * assignment, where valid assignments are in (1, N). Value assignments outside this range is invalid, and indicates
 * the variable is not assigned. 
 */
struct Variable {
    std::vector<int> domain;
    int val;

    Variable(CSPPtr);
    bool is_assigned();
private:
    const CSPPtr csp_ptr;
};
