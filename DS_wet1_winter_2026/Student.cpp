#include "Student.h"
#include "wet1util.h"
Student::Student(int student_id, int creation_offset_value) :
    m_student_id(student_id),
    m_enrolled_points(0),
    m_earned_points(0),
    m_bonus_offset(creation_offset_value),
    m_active_courses_count(0)
{
    // The check for (student_id <= 0) happens in TechSystem::addStudent.
    // If we reach here, we assume the ID is valid.


int Student::get_bonus(int current_total_bonus) const {
    return current_total_bonus - this->m_bonus_offset;
}
