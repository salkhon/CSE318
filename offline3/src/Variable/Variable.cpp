#include "Variable.hpp"

Variable::Variable(int id, int nstudents)
    : id{ id }, nstudents{ nstudents }, day{ -1 } {
}

bool Variable::is_day_assigned() {
    return this->day >= 0;
}
