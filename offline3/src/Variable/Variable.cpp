#include "Variable.hpp"

Variable::Variable(int id, int nstudents)
    : id{ id }, nstudents{ nstudents }, day{ -1 } {
}

bool Variable::is_day_assigned() {
    return this->day >= 0;
}

std::ostream& operator<<(std::ostream& ostrm, const Variable& var) {
    ostrm << "< Variable " << var.id << " : " << var.day << " >";
    return ostrm;
}
