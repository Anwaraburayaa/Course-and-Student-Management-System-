#include "Course.h"


Course::Course(int course_id, int credits): m_course_id(course_id), m_credits(credits), enrolled() {
}

Course::~Course() {

}

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

bool Course::is_empty() {
    return enrolled.tree_is_empty();
}


