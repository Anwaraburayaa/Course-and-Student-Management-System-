
//
// 234218 Data Structures 1.
// Semester: 2025A (Winter).
// Wet Exercise #1.
// 
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler will use our file.
// 

/*#include "TechSystem26a1.h"
#include <string>
#include <iostream>

using namespace std;

void print(string cmd, StatusType res);
void print(string cmd, output_t<int> res);
void print(string cmd, output_t<bool> res);

int main()
{
    
    int d1, d2;

    // Init
    TechSystem *obj = new TechSystem();
    
    // Execute all commands in file
    string op;
    while (cin >> op)
    {
        if (!op.compare("addStudent")) {
            cin >> d1;
            print(op, obj->addStudent(d1));
        } else if (!op.compare("removeStudent")) {
            cin >> d1;
            print(op, obj->removeStudent(d1));
        } else if (!op.compare("addCourse")) {
            cin >> d1 >> d2;
            print(op, obj->addCourse(d1, d2));
        } else if (!op.compare("removeCourse")) {
            cin >> d1;
            print(op, obj->removeCourse(d1));
        } else if (!op.compare("enrollStudent")) {
            cin >> d1 >> d2;
            print(op, obj->enrollStudent(d1, d2));
        } else if (!op.compare("completeCourse")) {
            cin >> d1 >> d2;
            print(op, obj->completeCourse(d1, d2));
        } else if (!op.compare("awardAcademicPoints")) {
            cin >> d1;
            print(op, obj->awardAcademicPoints(d1));
        } else if (!op.compare("getStudentPoints")) {
            cin >> d1;
            print(op, obj->getStudentPoints(d1));
        } else {
            cout << "Unknown command: " << op << endl;
            return -1;
        }
        // Verify no faults
        if (cin.fail()){
            cout << "Invalid input format" << endl;
            return -1;
        }
    }

    // Quit 
    delete obj;
    return 0;
}

// Helpers
static const char *StatusTypeStr[] =
{
    "SUCCESS",
    "ALLOCATION_ERROR",
    "INVALID_INPUT",
    "FAILURE"
};

void print(string cmd, StatusType res) 
{
    cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res)
{
    if (res.status() == StatusType::SUCCESS) {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

void print(string cmd, output_t<bool> res)
{
    if (res.status() == StatusType::SUCCESS) {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << (res.ans() ? "True" : "False") << endl;
    } else {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}*/


#include "TechSystem26a1.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Test result tracking
struct TestResult {
    string name;
    bool passed;
    string message;
};

vector<TestResult> test_results;

// Helper function to add test result
void add_test_result(bool passed, const string& test_name, const string& message = "") {
    test_results.push_back({test_name, passed, message});
    if (passed) {
        cout << "  ✓ " << test_name << endl;
    } else {
        cout << "  ✗ " << test_name;
        if (!message.empty()) {
            cout << " - " << message;
        }
        cout << endl;
    }
}

// Test Section Headers
void print_section(const string& section_name) {
    cout << "\n" << section_name << endl;
    cout << string(section_name.length(), '=') << endl;
}

// ========================================
// STUDENT MANAGEMENT TESTS
// ========================================

void test_add_student_basic() {
    print_section("Add Student - Basic Tests");
    TechSystem sys;

    add_test_result(sys.addStudent(1) == StatusType::SUCCESS, "Add student with valid ID");
    add_test_result(sys.addStudent(100) == StatusType::SUCCESS, "Add another student");
    add_test_result(sys.addStudent(1) == StatusType::FAILURE, "Add duplicate student (should fail)");
}

void test_add_student_invalid() {
    print_section("Add Student - Invalid Input Tests");
    TechSystem sys;

    add_test_result(sys.addStudent(0) == StatusType::INVALID_INPUT, "Add student with ID 0");
    add_test_result(sys.addStudent(-1) == StatusType::INVALID_INPUT, "Add student with negative ID");
    add_test_result(sys.addStudent(-100) == StatusType::INVALID_INPUT, "Add student with large negative ID");
}

void test_remove_student_basic() {
    print_section("Remove Student - Basic Tests");
    TechSystem sys;

    sys.addStudent(1);
    add_test_result(sys.removeStudent(1) == StatusType::SUCCESS, "Remove existing student with no courses");
    add_test_result(sys.removeStudent(1) == StatusType::FAILURE, "Remove non-existent student");
    add_test_result(sys.removeStudent(999) == StatusType::FAILURE, "Remove never-added student");
}

void test_remove_student_with_courses() {
    print_section("Remove Student - With Active Courses");
    TechSystem sys;

    sys.addStudent(1);
    sys.addCourse(101, 5);
    sys.enrollStudent(1, 101);

    add_test_result(sys.removeStudent(1) == StatusType::FAILURE, "Cannot remove student with active course");

    sys.completeCourse(1, 101);
    add_test_result(sys.removeStudent(1) == StatusType::SUCCESS, "Remove student after completing all courses");
}

void test_remove_student_invalid() {
    print_section("Remove Student - Invalid Input Tests");
    TechSystem sys;

    add_test_result(sys.removeStudent(0) == StatusType::INVALID_INPUT, "Remove student with ID 0");
    add_test_result(sys.removeStudent(-5) == StatusType::INVALID_INPUT, "Remove student with negative ID");
}

// ========================================
// COURSE MANAGEMENT TESTS
// ========================================

void test_add_course_basic() {
    print_section("Add Course - Basic Tests");
    TechSystem sys;

    add_test_result(sys.addCourse(101, 5) == StatusType::SUCCESS, "Add course with valid ID and points");
    add_test_result(sys.addCourse(202, 10) == StatusType::SUCCESS, "Add another course");
    add_test_result(sys.addCourse(101, 5) == StatusType::FAILURE, "Add duplicate course (should fail)");
}

void test_add_course_invalid() {
    print_section("Add Course - Invalid Input Tests");
    TechSystem sys;

    add_test_result(sys.addCourse(0, 5) == StatusType::INVALID_INPUT, "Add course with ID 0");
    add_test_result(sys.addCourse(-1, 5) == StatusType::INVALID_INPUT, "Add course with negative ID");
    add_test_result(sys.addCourse(101, 0) == StatusType::INVALID_INPUT, "Add course with 0 points");
    add_test_result(sys.addCourse(101, -5) == StatusType::INVALID_INPUT, "Add course with negative points");
    add_test_result(sys.addCourse(-1, -1) == StatusType::INVALID_INPUT, "Add course with both invalid");
}

void test_remove_course_basic() {
    print_section("Remove Course - Basic Tests");
    TechSystem sys;

    sys.addCourse(101, 5);
    add_test_result(sys.removeCourse(101) == StatusType::SUCCESS, "Remove empty course");
    add_test_result(sys.removeCourse(101) == StatusType::FAILURE, "Remove already-removed course");
    add_test_result(sys.removeCourse(999) == StatusType::FAILURE, "Remove non-existent course");
}

void test_remove_course_with_students() {
    print_section("Remove Course - With Enrolled Students");
    TechSystem sys;

    sys.addStudent(1);
    sys.addCourse(101, 5);
    sys.enrollStudent(1, 101);

    add_test_result(sys.removeCourse(101) == StatusType::FAILURE, "Cannot remove course with enrolled students");

    sys.completeCourse(1, 101);
    add_test_result(sys.removeCourse(101) == StatusType::SUCCESS, "Remove course after all students complete");
}

void test_remove_course_invalid() {
    print_section("Remove Course - Invalid Input Tests");
    TechSystem sys;

    add_test_result(sys.removeCourse(0) == StatusType::INVALID_INPUT, "Remove course with ID 0");
    add_test_result(sys.removeCourse(-10) == StatusType::INVALID_INPUT, "Remove course with negative ID");
}

// ========================================
// ENROLLMENT TESTS
// ========================================

void test_enroll_student_basic() {
    print_section("Enroll Student - Basic Tests");
    TechSystem sys;

    sys.addStudent(1);
    sys.addCourse(101, 5);

    add_test_result(sys.enrollStudent(1, 101) == StatusType::SUCCESS, "Enroll student in course");
    add_test_result(sys.enrollStudent(1, 101) == StatusType::FAILURE, "Enroll student in same course twice");
}

void test_enroll_student_nonexistent() {
    print_section("Enroll Student - Non-existent Entities");
    TechSystem sys;

    sys.addStudent(1);
    sys.addCourse(101, 5);

    add_test_result(sys.enrollStudent(999, 101) == StatusType::FAILURE, "Enroll non-existent student");
    add_test_result(sys.enrollStudent(1, 999) == StatusType::FAILURE, "Enroll in non-existent course");
    add_test_result(sys.enrollStudent(999, 999) == StatusType::FAILURE, "Enroll non-existent student in non-existent course");
}

void test_enroll_student_invalid() {
    print_section("Enroll Student - Invalid Input Tests");
    TechSystem sys;

    add_test_result(sys.enrollStudent(0, 101) == StatusType::INVALID_INPUT, "Enroll with student ID 0");
    add_test_result(sys.enrollStudent(1, 0) == StatusType::INVALID_INPUT, "Enroll with course ID 0");
    add_test_result(sys.enrollStudent(-1, 101) == StatusType::INVALID_INPUT, "Enroll with negative student ID");
    add_test_result(sys.enrollStudent(1, -1) == StatusType::INVALID_INPUT, "Enroll with negative course ID");
}

void test_enroll_multiple_courses() {
    print_section("Enroll Student - Multiple Courses");
    TechSystem sys;

    sys.addStudent(1);
    sys.addCourse(101, 5);
    sys.addCourse(102, 10);
    sys.addCourse(103, 3);

    add_test_result(sys.enrollStudent(1, 101) == StatusType::SUCCESS, "Enroll in first course");
    add_test_result(sys.enrollStudent(1, 102) == StatusType::SUCCESS, "Enroll in second course");
    add_test_result(sys.enrollStudent(1, 103) == StatusType::SUCCESS, "Enroll in third course");
}

// ========================================
// COURSE COMPLETION TESTS
// ========================================

void test_complete_course_basic() {
    print_section("Complete Course - Basic Tests");
    TechSystem sys;

    sys.addStudent(1);
    sys.addCourse(101, 5);
    sys.enrollStudent(1, 101);

    add_test_result(sys.completeCourse(1, 101) == StatusType::SUCCESS, "Complete enrolled course");
    add_test_result(sys.completeCourse(1, 101) == StatusType::FAILURE, "Complete same course twice");
}

void test_complete_course_not_enrolled() {
    print_section("Complete Course - Not Enrolled");
    TechSystem sys;

    sys.addStudent(1);
    sys.addCourse(101, 5);

    add_test_result(sys.completeCourse(1, 101) == StatusType::FAILURE, "Complete course without enrollment");
}

void test_complete_course_nonexistent() {
    print_section("Complete Course - Non-existent Entities");
    TechSystem sys;

    sys.addStudent(1);
    sys.addCourse(101, 5);
    sys.enrollStudent(1, 101);

    add_test_result(sys.completeCourse(999, 101) == StatusType::FAILURE, "Complete with non-existent student");
    add_test_result(sys.completeCourse(1, 999) == StatusType::FAILURE, "Complete non-existent course");
}

void test_complete_course_invalid() {
    print_section("Complete Course - Invalid Input Tests");
    TechSystem sys;

    add_test_result(sys.completeCourse(0, 101) == StatusType::INVALID_INPUT, "Complete with student ID 0");
    add_test_result(sys.completeCourse(1, 0) == StatusType::INVALID_INPUT, "Complete with course ID 0");
    add_test_result(sys.completeCourse(-1, 101) == StatusType::INVALID_INPUT, "Complete with negative student ID");
    add_test_result(sys.completeCourse(1, -1) == StatusType::INVALID_INPUT, "Complete with negative course ID");
}

// ========================================
// POINTS AND BONUS TESTS
// ========================================

void test_get_student_points_basic() {
    print_section("Get Student Points - Basic Tests");
    TechSystem sys;

    sys.addStudent(1);
    output_t<int> result1 = sys.getStudentPoints(1);
    add_test_result(result1.status() == StatusType::SUCCESS && result1.ans() == 0, "New student has 0 points");

    sys.addCourse(101, 5);
    sys.enrollStudent(1, 101);
    sys.completeCourse(1, 101);

    output_t<int> result2 = sys.getStudentPoints(1);
    add_test_result(result2.status() == StatusType::SUCCESS && result2.ans() == 5, "Student has 5 points after completing course");
}

void test_get_student_points_multiple_courses() {
    print_section("Get Student Points - Multiple Courses");
    TechSystem sys;

    sys.addStudent(1);
    sys.addCourse(101, 5);
    sys.addCourse(102, 10);
    sys.addCourse(103, 3);

    sys.enrollStudent(1, 101);
    sys.enrollStudent(1, 102);
    sys.enrollStudent(1, 103);

    sys.completeCourse(1, 101);
    output_t<int> result1 = sys.getStudentPoints(1);
    add_test_result(result1.status() == StatusType::SUCCESS && result1.ans() == 5, "Points after first course (expected 5)");

    sys.completeCourse(1, 102);
    output_t<int> result2 = sys.getStudentPoints(1);
    add_test_result(result2.status() == StatusType::SUCCESS && result2.ans() == 15, "Points after second course (expected 15)");

    sys.completeCourse(1, 103);
    output_t<int> result3 = sys.getStudentPoints(1);
    add_test_result(result3.status() == StatusType::SUCCESS && result3.ans() == 18, "Points after third course (expected 18)");
}

void test_get_student_points_invalid() {
    print_section("Get Student Points - Invalid Input Tests");
    TechSystem sys;

    output_t<int> result1 = sys.getStudentPoints(0);
    add_test_result(result1.status() == StatusType::INVALID_INPUT, "Get points with ID 0");

    output_t<int> result2 = sys.getStudentPoints(-1);
    add_test_result(result2.status() == StatusType::INVALID_INPUT, "Get points with negative ID");
}

void test_get_student_points_nonexistent() {
    print_section("Get Student Points - Non-existent Student");
    TechSystem sys;

    output_t<int> result = sys.getStudentPoints(999);
    add_test_result(result.status() == StatusType::FAILURE, "Get points for non-existent student");
}

void test_award_academic_points_basic() {
    print_section("Award Academic Points - Basic Tests");
    TechSystem sys;

    add_test_result(sys.awardAcademicPoints(10) == StatusType::SUCCESS, "Award 10 bonus points");
    add_test_result(sys.awardAcademicPoints(5) == StatusType::SUCCESS, "Award 5 more bonus points");
}

void test_award_academic_points_invalid() {
    print_section("Award Academic Points - Invalid Input Tests");
    TechSystem sys;

    add_test_result(sys.awardAcademicPoints(0) == StatusType::INVALID_INPUT, "Award 0 points");
    add_test_result(sys.awardAcademicPoints(-5) == StatusType::INVALID_INPUT, "Award negative points");
}

void test_bonus_points_distribution() {
    print_section("Bonus Points - Distribution Logic");
    TechSystem sys;

    // Award bonus before adding students
    sys.awardAcademicPoints(10);

    sys.addStudent(1);
    output_t<int> result1 = sys.getStudentPoints(1);
    add_test_result(result1.status() == StatusType::SUCCESS && result1.ans() == 0, "Student 1 gets no previous bonus (expected 0)");

    sys.awardAcademicPoints(5);
    output_t<int> result2 = sys.getStudentPoints(1);
    add_test_result(result2.status() == StatusType::SUCCESS && result2.ans() == 5, "Student 1 gets new bonus (expected 5)");

    sys.addStudent(2);
    output_t<int> result3 = sys.getStudentPoints(2);
    add_test_result(result3.status() == StatusType::SUCCESS && result3.ans() == 0, "Student 2 gets no previous bonus (expected 0)");

    sys.awardAcademicPoints(3);
    output_t<int> result4 = sys.getStudentPoints(1);
    add_test_result(result4.status() == StatusType::SUCCESS && result4.ans() == 8, "Student 1 gets 5+3 bonus (expected 8)");

    output_t<int> result5 = sys.getStudentPoints(2);
    add_test_result(result5.status() == StatusType::SUCCESS && result5.ans() == 3, "Student 2 gets only 3 bonus (expected 3)");
}

// ========================================
// COMPLEX SCENARIO TESTS
// ========================================

void test_complex_scenario_1() {
    print_section("Complex Scenario - Multiple Students and Courses");
    TechSystem sys;

    // Setup
    sys.addStudent(1);
    sys.addStudent(2);
    sys.addStudent(3);
    sys.addCourse(101, 5);
    sys.addCourse(102, 10);
    sys.addCourse(103, 3);

    sys.enrollStudent(1, 101);
    sys.enrollStudent(1, 102);
    sys.enrollStudent(2, 101);
    sys.enrollStudent(3, 103);

    sys.awardAcademicPoints(2);
    sys.completeCourse(1, 101);
    sys.completeCourse(2, 101);

    output_t<int> result1 = sys.getStudentPoints(1);
    add_test_result(result1.status() == StatusType::SUCCESS && result1.ans() == 7, "Student 1: 5 earned + 2 bonus (expected 7)");

    output_t<int> result2 = sys.getStudentPoints(2);
    add_test_result(result2.status() == StatusType::SUCCESS && result2.ans() == 7, "Student 2: 5 earned + 2 bonus (expected 7)");

    output_t<int> result3 = sys.getStudentPoints(3);
    add_test_result(result3.status() == StatusType::SUCCESS && result3.ans() == 2, "Student 3: 0 earned + 2 bonus (expected 2)");

    sys.completeCourse(1, 102);
    sys.completeCourse(3, 103);

    output_t<int> result4 = sys.getStudentPoints(1);
    add_test_result(result4.status() == StatusType::SUCCESS && result4.ans() == 17, "Student 1: 15 earned + 2 bonus (expected 17)");

    output_t<int> result5 = sys.getStudentPoints(3);
    add_test_result(result5.status() == StatusType::SUCCESS && result5.ans() == 5, "Student 3: 3 earned + 2 bonus (expected 5)");
}

void test_complex_scenario_2() {
    print_section("Complex Scenario - Remove After Completion");
    TechSystem sys;

    sys.addStudent(1);
    sys.addCourse(101, 5);
    sys.addCourse(102, 10);

    sys.enrollStudent(1, 101);
    sys.enrollStudent(1, 102);

    add_test_result(sys.removeStudent(1) == StatusType::FAILURE, "Cannot remove with active courses");

    sys.completeCourse(1, 101);
    add_test_result(sys.removeStudent(1) == StatusType::FAILURE, "Cannot remove with one active course");

    sys.completeCourse(1, 102);
    add_test_result(sys.removeStudent(1) == StatusType::SUCCESS, "Can remove after all courses completed");

    add_test_result(sys.removeCourse(101) == StatusType::SUCCESS, "Remove course after student removed");
    add_test_result(sys.removeCourse(102) == StatusType::SUCCESS, "Remove another course");
}

void test_large_scale_operations() {
    print_section("Large Scale Operations (100 students, 50 courses)");
    TechSystem sys;

    // Add many students
    bool all_students_added = true;
    for (int i = 1; i <= 100; i++) {
        if (sys.addStudent(i) != StatusType::SUCCESS) {
            all_students_added = false;
            break;
        }
    }
    add_test_result(all_students_added, "Add 100 students");

    // Add many courses
    bool all_courses_added = true;
    for (int i = 1; i <= 50; i++) {
        if (sys.addCourse(i, i) != StatusType::SUCCESS) {
            all_courses_added = false;
            break;
        }
    }
    add_test_result(all_courses_added, "Add 50 courses");

    // Enroll and complete
    for (int s = 1; s <= 100; s++) {
        for (int c = 1; c <= 10; c++) {
            sys.enrollStudent(s, c);
        }
    }

    for (int s = 1; s <= 100; s++) {
        for (int c = 1; c <= 10; c++) {
            sys.completeCourse(s, c);
        }
    }

    add_test_result(true, "1000 enrollments and 1000 completions without crashes");
}

void test_edge_case_enrolled_points() {
    print_section("Edge Case - Enrolled Points Tracking");
    TechSystem sys;

    sys.addStudent(1);
    sys.addCourse(101, 5);
    sys.addCourse(102, 10);

    sys.enrollStudent(1, 101);
    sys.enrollStudent(1, 102);

    add_test_result(sys.removeStudent(1) == StatusType::FAILURE, "Cannot remove with enrolled points = 15");

    sys.completeCourse(1, 101);
    add_test_result(sys.removeStudent(1) == StatusType::FAILURE, "Cannot remove with enrolled points = 10");

    sys.completeCourse(1, 102);
    add_test_result(sys.removeStudent(1) == StatusType::SUCCESS, "Can remove when enrolled points = 0");
}

void test_multiple_students_same_course() {
    print_section("Multiple Students in Same Course");
    TechSystem sys;

    sys.addStudent(1);
    sys.addStudent(2);
    sys.addStudent(3);
    sys.addCourse(101, 10);

    add_test_result(sys.enrollStudent(1, 101) == StatusType::SUCCESS, "Student 1 enrolls");
    add_test_result(sys.enrollStudent(2, 101) == StatusType::SUCCESS, "Student 2 enrolls");
    add_test_result(sys.enrollStudent(3, 101) == StatusType::SUCCESS, "Student 3 enrolls");

    add_test_result(sys.removeCourse(101) == StatusType::FAILURE, "Cannot remove course with 3 students");

    sys.completeCourse(1, 101);
    add_test_result(sys.removeCourse(101) == StatusType::FAILURE, "Cannot remove course with 2 students");

    sys.completeCourse(2, 101);
    add_test_result(sys.removeCourse(101) == StatusType::FAILURE, "Cannot remove course with 1 student");

    sys.completeCourse(3, 101);
    add_test_result(sys.removeCourse(101) == StatusType::SUCCESS, "Can remove course with 0 students");
}

// ========================================
// SUMMARY GENERATION
// ========================================

void print_summary() {
    int passed = 0;
    int failed = 0;

    for (const auto& result : test_results) {
        if (result.passed) {
            passed++;
        } else {
            failed++;
        }
    }

    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                     TEST SUMMARY                          ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\nTests Passed: " << passed << " / " << (passed + failed) << endl;
    cout << "Tests Failed: " << failed << " / " << (passed + failed) << endl;

    if (failed > 0) {
        cout << "\n--- Failed Tests ---" << endl;
        for (const auto& result : test_results) {
            if (!result.passed) {
                cout << "  ✗ " << result.name;
                if (!result.message.empty()) {
                    cout << " - " << result.message;
                }
                cout << endl;
            }
        }
    }

    if (failed == 0) {
        cout << "\n🎉 ALL TESTS PASSED! 🎉\n" << endl;
    } else {
        cout << "\n⚠️  " << failed << " TEST(S) FAILED ⚠️\n" << endl;
    }
}

// ========================================
// MAIN TEST RUNNER
// ========================================

int main() {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              TECHSYSTEM COMPREHENSIVE TEST SUITE          ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;

    // Student Management Tests
    test_add_student_basic();
    test_add_student_invalid();
    test_remove_student_basic();
    test_remove_student_with_courses();
    test_remove_student_invalid();

    // Course Management Tests
    test_add_course_basic();
    test_add_course_invalid();
    test_remove_course_basic();
    test_remove_course_with_students();
    test_remove_course_invalid();

    // Enrollment Tests
    test_enroll_student_basic();
    test_enroll_student_nonexistent();
    test_enroll_student_invalid();
    test_enroll_multiple_courses();

    // Course Completion Tests
    test_complete_course_basic();
    test_complete_course_not_enrolled();
    test_complete_course_nonexistent();
    test_complete_course_invalid();

    // Points and Bonus Tests
    test_get_student_points_basic();
    test_get_student_points_multiple_courses();
    test_get_student_points_invalid();
    test_get_student_points_nonexistent();
    test_award_academic_points_basic();
    test_award_academic_points_invalid();
    test_bonus_points_distribution();

    // Complex Scenarios
    test_complex_scenario_1();
    test_complex_scenario_2();
    test_large_scale_operations();
    test_edge_case_enrolled_points();
    test_multiple_students_same_course();

    // Print Summary
    print_summary();

    // Return appropriate exit code
    int failed_count = 0;
    for (const auto& result : test_results) {
        if (!result.passed) failed_count++;
    }

    return (failed_count == 0) ? 0 : 1;
}











