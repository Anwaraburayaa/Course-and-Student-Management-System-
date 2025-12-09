#include "Course.h"


int Course::get_course_id() const {
    return m_course_id;
}

int Course::get_credits() const {
    return m_credits;
}

void Course::set_course_id(const int course_id) {
    this->m_course_id = course_id;
}

void Course::set_credits(const int credits) {
    this->m_credits = credits;
}


