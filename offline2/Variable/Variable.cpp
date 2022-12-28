#include "Variable.hpp"
#include <numeric>

/**
 * @brief Construct a new Variable:: Variable object
 *
 * @param id Variable id
 * @param row Variable row
 * @param col Variable column
 * @param domain Domain for variable
 */
Variable::Variable(int id, int row, int col, std::vector<int> domain):
    id{ id }, row{ row }, col{ col }, domain{ domain }, val{ -1 } {
}

/**
 * @brief Check if variable has been assigned a value.
 *
 * @return true if `val` is within (1, N)
 * @return false otherwise
 */
bool Variable::is_assigned() {
    return this->val > 0;
}

/**
 * @brief Clears variable assignment
 *
 */
void Variable::erase_assignment() {
    this->val = -1;
}

std::ostream& operator<<(std::ostream& ostrm, const Variable& var) {
    ostrm << "< Variable " << var.id << " (" << var.row << "," << var.col << ") val=" << var.val << " [";
    for (int dom : var.domain) {
        ostrm << dom << ",";
    }
    ostrm << "] >";
    return ostrm;
}
