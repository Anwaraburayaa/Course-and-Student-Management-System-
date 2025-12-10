// You can edit anything you want in this file.
// However, you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"



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
    Course* course_to_remove = courses.get_data(courseId);
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
    return StatusType::FAILURE;
}

StatusType TechSystem::awardAcademicPoints(int points)
{
    return StatusType::FAILURE;
}

output_t<int> TechSystem::getStudentPoints(int studentId)
{
    return 0;
}