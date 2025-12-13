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

TechSystem::TechSystem() :students(),courses()
{
    total_bonus_tracker = 0;
}

TechSystem::~TechSystem() {
    //  deletes the actual 'Student*' pointers.
    students.delete_stored_data();

    // We call the helper on the courses tree.
    // Note: The ~Course() destructor will automatically run when a Course
    // is deleted, destroying the course's internal 'enrolled' tree.
    courses.delete_stored_data();
    //** The AVLTree destructors (~AVLTree) for 'students' and 'courses'
    //are called automatically at the end of this function to delete
    //**// the tree structure (the nodes themselves).
}

StatusType TechSystem::addStudent(int studentId)
{
    //check if the id is valid
    if (invalid_input(studentId)) {
    return StatusType::INVALID_INPUT;
}
    //check if the student already exists
    bool student_exists = students.id_in_tree(studentId);
    if (student_exists) {
        return StatusType::FAILURE;
    }

    Student* new_student = nullptr;
    try {
        new_student = new Student(studentId, total_bonus_tracker);
        bool inserted = students.insert(studentId, new_student);
        if (!inserted) {
            delete new_student;
            return StatusType::FAILURE; // Should not happen if id_in_tree passed
        }
    }
    catch (const std::bad_alloc& e) {
        // CRITICAL FIX: If insert throws, we must delete the student we created
        delete new_student;
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}



StatusType TechSystem::removeStudent(int studentId)
{
    if (invalid_input(studentId)) {
        return StatusType::INVALID_INPUT;
    }

    Student* student_to_remove = students.find_node(studentId);

    // 1. Check if the student exists
    if (!student_to_remove) {
        return StatusType::FAILURE;
    }

    // 2. Policy Check: Must have finished all courses
    if (!(student_to_remove->has_finished_courses())) {
        return StatusType::FAILURE;
    }

    // 3. Safely remove the node from the AVL tree structure first.
    if (!students.remove(studentId)) {
        return StatusType::FAILURE;
    }

    // 4. Delete the actual student object (now that it's no longer referenced by the tree).
    delete student_to_remove;

    return StatusType::SUCCESS;
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
    if (!courses.remove(courseId)) {
        return StatusType::FAILURE;
    }
    delete course_to_remove;
    return StatusType::SUCCESS;

}

StatusType TechSystem::enrollStudent(int studentId, int courseId)
{
    if (invalid_input(studentId) || invalid_input(courseId)) {
        return StatusType::INVALID_INPUT;
    }


    Course* course_enrolled = courses.find_node(courseId);
    if (!course_enrolled) {
        return StatusType::FAILURE;
    }


    Student* current_student = students.find_node(studentId);
    if (!current_student) {
        return StatusType::FAILURE;
    }

    try {

        // Returns false if student is already in the course
        bool is_enrolled = course_enrolled->insert_enrolled_student(studentId, current_student);

        if (!is_enrolled) {
            return StatusType::FAILURE;
        }

        // *** FIX: Update enrolled points (Missing logic) ***
        current_student->update_enrolled_points(course_enrolled->get_points());

        current_student->increment_active_courses();

        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc& e) {

        return StatusType::ALLOCATION_ERROR;
    }
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
    current_student->decrement_active_courses();
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

