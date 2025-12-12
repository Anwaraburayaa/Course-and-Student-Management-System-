#include "Student.h"


int Student::get_bonus(int current_total_bonus) const {
    return current_total_bonus - this->m_bonus_offset;
}
