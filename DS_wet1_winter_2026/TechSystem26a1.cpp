// You can edit anything you want in this file.
// However, you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"

int TechSystem::total_bonus_tracker = 0;

void TechSystem::update_bonus_tracker(int points) {
    total_bonus_tracker += points;
}

int TechSystem::get_total_bonus() {
    return total_bonus_tracker;
}

bool TechSystem::invalid_input(int id) {
    return id <= 0;
}

TechSystem::TechSystem()
{
    
}

TechSystem::~TechSystem()
{
    
}

StatusType TechSystem::addStudent(int studentId)
{
    return StatusType::FAILURE;
}

StatusType TechSystem::removeStudent(int studentId)
{
    return StatusType::FAILURE;
}

StatusType TechSystem::addCourse(int courseId, int points)
{
    if (invalid_input(courseId) || invalid_input(points)) {
        return StatusType::INVALID_INPUT;
    }
    if (courses.id_in_tree(courseId)) {
        return StatusType::FAILURE;
    }
    Course* new_course = nullptr;
    try {
        new_course = new Course(courseId, points);
        if (!courses.insert(courseId, new_course)) {
            delete new_course;
            return StatusType::FAILURE;
        }
    } catch (std::bad_alloc&) {
        delete new_course;
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType TechSystem::removeCourse(int courseId)
{
    if (invalid_input(courseId)) {
        return StatusType::INVALID_INPUT;
    }
    Course* course_to_remove = courses.find_node(courseId);
    if (!course_to_remove || !course_to_remove->is_empty()) {
        return StatusType::FAILURE;
    }
    delete course_to_remove;
    if (!courses.remove(courseId)) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;

}

StatusType TechSystem::enrollStudent(int studentId, int courseId)
{
    return StatusType::FAILURE;
}

StatusType TechSystem::completeCourse(int studentId, int courseId)
{
    if (invalid_input(studentId) || invalid_input(courseId)) {
        return StatusType::INVALID_INPUT;
    }
    Course* course_completed = courses.find_node(courseId); // log(m) finding the course
    if (!course_completed) {
        return StatusType::FAILURE;
    }
    Student* current_student = course_completed->get_enrolled_student(studentId);
    if (!current_student) {
        return StatusType::FAILURE;
    }
    current_student->update_earned_points(course_completed->get_points());
    current_student->update_enrolled_points(-1*course_completed->get_points());
    if (!course_completed->remove_enrolled_student(studentId)) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType TechSystem::awardAcademicPoints(int points)
{
    if (invalid_input(points)) {
        return StatusType::INVALID_INPUT;
    }
    update_bonus_tracker(points);
    return StatusType::SUCCESS;
}

output_t<int> TechSystem::getStudentPoints(int studentId)
{
    if (invalid_input(studentId)) {
        return StatusType::INVALID_INPUT;
    }
    Student* current_student = students.find_node(studentId);
    if (!current_student) {
        return StatusType::FAILURE;
    }
    return current_student->get_bonus(total_bonus_tracker) + current_student->get_earned_points();
    return StatusType::SUCCESS;
}