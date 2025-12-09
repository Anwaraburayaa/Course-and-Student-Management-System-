#pragma once

#include "AVLTree.h"
#include "Student.h"

//TODO basic class functionality

class Course
{
private:
    int m_course_id;
    int m_credit;
    AVLTree<Student*> enrolled;



};



