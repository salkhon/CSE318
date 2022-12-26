#pragma once
#include "../defs.hpp"
#include "../Variable/Variable.hpp"
#include <memory>

/**
 * @brief Provides next variable in the context of the current assignements in CSP. This cannot have a one time
 * method returning a list of variables, because as the search progresses and variables are assigned the order
 * needs to dynamically adapt. So a method to get next singular variable analyzing the current states is needed.
 *
 */
struct VariableOrderHeuristic {
    VariableOrderHeuristic(CSPPtrWk);
    virtual VariablePtr next_var() = 0;
protected:
    const CSPPtrWk csp_ptrwk;
};