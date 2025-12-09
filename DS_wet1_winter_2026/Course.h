#pragma once

#include "AVLTree.h"
#include "Student.h"

class Course {
private:
    int m_course_id;
    int m_credits;
    AVLTree<Student*> enrolled;

public:

    Course(int course_id, int credits) : m_course_id(course_id), m_credits(credits), enrolled() {

    }

    ~Course();

    int get_course_id() const;
    int get_credits() const;
    void set_course_id(int course_id);
    void set_credits(int credits);

};



