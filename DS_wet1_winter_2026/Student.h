#pragma once

//TODO anwar basic class functionality

class Student
{
private:
    int m_student_id;
    int m_enrolled_points;
    int m_earned_points;
    int m_bonus_offset;
    //added this field in order to know when we can delete a student
    int m_active_courses_count;

public:
    //ctor & dtor:
    Student(int student_id, int creation_offset_value); // in techsystem the static field
    ~Student()=default;
    Student(const Student& other)=delete;
    Student& operator=(const Student& other)=delete;
    // getters and setters for point updating

    int get_student_id() const;
    int get_enrolled_points() const;
    int get_earned_points() const;
    void update_enrolled_points(int points);
    void update_earned_points(int points);
    int get_bonus(int current_total_bonus) const; // get the total when called in techsystem

    void increment_active_courses();
    void decrement_active_courses();
    //a helper method to check if the student is enrolled to any courses currently
    //we will use it to check if we can remove him from the system
    bool has_finished_courses() const;


};







