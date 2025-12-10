#pragma once

#include "AVLTree.h"
#include "Student.h"

class Course {
private:
    int m_course_id;
    int m_points;
    AVLTree<Student*> enrolled;

public:

    Course(int course_id, int credits);
    ~Course();

    int get_course_id() const;
    int get_points() const;
    void set_course_id(int course_id);
    void set_points(int credits);
    bool is_empty();
    Student* get_enrolled_student(int student_id);
    bool remove_enrolled_student(int student_id);
    bool insert_enrolled_student(int student_id, Student* student_ptr);

};



