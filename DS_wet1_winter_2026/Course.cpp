#include "Course.h"


Course::Course(int course_id, int credits): m_course_id(course_id), m_points(credits), enrolled() {
}

Course::~Course() {

}

int Course::get_course_id() const {
    return m_course_id;
}

int Course::get_points() const {
    return m_points;
}

void Course::set_course_id(const int course_id) {
    this->m_course_id = course_id;
}

void Course::set_points(const int credits) {
    this->m_points = credits;
}

bool Course::is_empty() {
    return enrolled.tree_is_empty();
}

Student* Course::get_enrolled_student(int student_id) {
    return enrolled.find_node(student_id);
}

bool Course::remove_enrolled_student(int student_id) {
    return enrolled.remove(student_id);
}

bool Course::insert_enrolled_student(int student_id, Student* student_ptr) {
    return enrolled.insert(student_id, student_ptr);
}


