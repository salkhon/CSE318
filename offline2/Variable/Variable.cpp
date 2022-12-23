#include "Variable.hpp"
#include <numeric>

Variable::Variable(CSPPtr csp_ptr):
    csp_ptr{ csp_ptr }, domain{ csp_ptr->N }, val{ -1 } {
    std::iota(this->domain.begin(), this->domain.end(), 1); // fills (1, N)
}

/**
 * @brief Check if variable has been assigned a value.
 * 
 * @return true if `val` is within (1, N)
 * @return false otherwise
 */
bool Variable::is_assigned() {
    return this->val > 0 && this->val <= this->csp_ptr->N;
}
