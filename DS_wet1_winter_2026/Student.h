#pragma once

//TODO anwar basic class functionality

class Student
{
private:
    int m_student_id;
    int m_enrolled_points;
    int m_earned_points;
    int m_applied_bonus;
public:
    // getters and setters for point updating
    int get_enrolled_points();
    int get_earned_points();
    void update_enrolled_points(int points);
    void update_earned_points(int points);

};







