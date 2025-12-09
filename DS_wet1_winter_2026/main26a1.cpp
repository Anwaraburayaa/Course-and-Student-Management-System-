// 
// 234218 Data Structures 1.
// Semester: 2025A (Winter).
// Wet Exercise #1.
// 
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler will use our file.
// 
/*
#include "TechSystem26a1.h"
#include <string>
#include <iostream>
*/
/*
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
}
*/

/*
#include <iostream>
#include <cassert>
#include <string>
#include "AVLTree.h"

using namespace std;

// Helper function to print test results
void printTest(const string& testName, bool passed) {
    cout << (passed ? "✓ " : "✗ ") << testName << endl;
}

// Test 1: Basic insertion and find
void test_basic_insert_find() {
    AVLTree<int> tree;

    bool inserted = tree.insert(10, 100);
    assert(inserted == true);

    auto node = tree.find(10);
    assert(node != nullptr);
    assert(node->m_key == 10);

    // Try to insert duplicate
    inserted = tree.insert(10, 200);
    assert(inserted == false);

    printTest("Basic Insert and Find", true);
}

// Test 2: Multiple insertions
void test_multiple_insertions() {
    AVLTree<string> tree;

    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");
    tree.insert(6, "six");
    tree.insert(8, "eight");

    assert(tree.find(5) != nullptr);
    assert(tree.find(3) != nullptr);
    assert(tree.find(7) != nullptr);
    assert(tree.find(2) != nullptr);
    assert(tree.find(100) == nullptr);

    printTest("Multiple Insertions", true);
}

// Test 3: LL Rotation (Right rotation)
void test_ll_rotation() {
    AVLTree<int> tree;

    // Insert in descending order to trigger LL case
    tree.insert(30, 30);
    tree.insert(20, 20);
    tree.insert(10, 10);  // Should trigger right rotation

    // All nodes should still be findable
    assert(tree.find(30) != nullptr);
    assert(tree.find(20) != nullptr);
    assert(tree.find(10) != nullptr);

    printTest("LL Rotation (Right)", true);
}

// Test 4: RR Rotation (Left rotation)
void test_rr_rotation() {
    AVLTree<int> tree;

    // Insert in ascending order to trigger RR case
    tree.insert(10, 10);
    tree.insert(20, 20);
    tree.insert(30, 30);  // Should trigger left rotation

    assert(tree.find(10) != nullptr);
    assert(tree.find(20) != nullptr);
    assert(tree.find(30) != nullptr);

    printTest("RR Rotation (Left)", true);
}

// Test 5: LR Rotation
void test_lr_rotation() {
    AVLTree<int> tree;

    tree.insert(30, 30);
    tree.insert(10, 10);
    tree.insert(20, 20);  // Should trigger LR rotation

    assert(tree.find(30) != nullptr);
    assert(tree.find(10) != nullptr);
    assert(tree.find(20) != nullptr);

    printTest("LR Rotation", true);
}

// Test 6: RL Rotation
void test_rl_rotation() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(30, 30);
    tree.insert(20, 20);  // Should trigger RL rotation

    assert(tree.find(10) != nullptr);
    assert(tree.find(30) != nullptr);
    assert(tree.find(20) != nullptr);

    printTest("RL Rotation", true);
}

// Test 7: Remove leaf node
void test_remove_leaf() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);

    bool removed = tree.remove(5);
    assert(removed == true);
    assert(tree.find(5) == nullptr);
    assert(tree.find(10) != nullptr);
    assert(tree.find(15) != nullptr);

    printTest("Remove Leaf Node", true);
}

// Test 8: Remove node with one child
void test_remove_one_child() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(3, 3);

    // Remove 5 (has one left child: 3)
    bool removed = tree.remove(5);
    assert(removed == true);
    assert(tree.find(5) == nullptr);
    assert(tree.find(3) != nullptr);
    assert(tree.find(10) != nullptr);

    printTest("Remove Node with One Child", true);
}

// Test 9: Remove node with two children
void test_remove_two_children() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(12, 12);
    tree.insert(17, 17);

    // Remove 10 (has two children)
    bool removed = tree.remove(10);
    assert(removed == true);
    assert(tree.find(10) == nullptr);

    // All other nodes should still exist
    assert(tree.find(5) != nullptr);
    assert(tree.find(15) != nullptr);
    assert(tree.find(3) != nullptr);
    assert(tree.find(7) != nullptr);
    assert(tree.find(12) != nullptr);
    assert(tree.find(17) != nullptr);

    printTest("Remove Node with Two Children", true);
}

// Test 10: Remove non-existent key
void test_remove_nonexistent() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(5, 5);

    bool removed = tree.remove(100);
    assert(removed == false);

    printTest("Remove Non-existent Key", true);
}

// Test 11: Remove root
void test_remove_root() {
    AVLTree<int> tree;

    tree.insert(10, 10);

    bool removed = tree.remove(10);
    assert(removed == true);
    assert(tree.find(10) == nullptr);

    printTest("Remove Root Node", true);
}

// Test 12: Complex operations sequence
void test_complex_sequence() {
    AVLTree<int> tree;

    // Build a tree
    for (int i = 1; i <= 20; i++) {
        tree.insert(i, i * 10);
    }

    // Remove every other element
    for (int i = 2; i <= 20; i += 2) {
        tree.remove(i);
    }

    // Check remaining elements
    for (int i = 1; i <= 20; i++) {
        if (i % 2 == 1) {
            assert(tree.find(i) != nullptr);
        } else {
            assert(tree.find(i) == nullptr);
        }
    }

    printTest("Complex Operations Sequence", true);
}

// Test 13: Stress test with many insertions
void test_stress_insertions() {
    AVLTree<int> tree;

    // Insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        tree.insert(i, i);
    }

    // Verify all exist
    for (int i = 0; i < 1000; i++) {
        assert(tree.find(i) != nullptr);
    }

    printTest("Stress Test - 1000 Insertions", true);
}

// Test 14: Test with string data
void test_string_data() {
    AVLTree<string> tree;

    tree.insert(1, "apple");
    tree.insert(2, "banana");
    tree.insert(3, "cherry");

    auto node = tree.find(2);
    assert(node != nullptr);
    assert(node->m_data == "banana");

    printTest("String Data Type", true);
}

// Test 15: Insert and remove in alternating pattern
void test_alternating_operations() {
    AVLTree<int> tree;

    tree.insert(50, 50);
    tree.insert(25, 25);
    tree.insert(75, 75);
    tree.remove(25);
    tree.insert(30, 30);
    tree.insert(10, 10);
    tree.remove(75);
    tree.insert(80, 80);
    tree.insert(60, 60);

    assert(tree.find(50) != nullptr);
    assert(tree.find(25) == nullptr);
    assert(tree.find(75) == nullptr);
    assert(tree.find(30) != nullptr);
    assert(tree.find(10) != nullptr);
    assert(tree.find(80) != nullptr);
    assert(tree.find(60) != nullptr);

    printTest("Alternating Insert/Remove Operations", true);
}

int main() {
    cout << "=== AVL Tree Test Suite ===" << endl << endl;

    try {
        test_basic_insert_find();
        test_multiple_insertions();
        test_ll_rotation();
        test_rr_rotation();
        test_lr_rotation();
        test_rl_rotation();
        test_remove_leaf();
        test_remove_one_child();
        test_remove_two_children();
        test_remove_nonexistent();
        test_remove_root();
        test_complex_sequence();
        test_stress_insertions();
        test_string_data();
        test_alternating_operations();

        cout << "\n=== All tests passed! ===" << endl;
    } catch (const exception& e) {
        cout << "\n✗ Test failed with exception: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << "\n✗ Test failed with unknown exception" << endl;
        return 1;
    }

    return 0;
}*/
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include "AVLTree.h"

using namespace std;

// No color codes - plain text output
#define RESET   ""
#define RED     ""
#define GREEN   ""
#define YELLOW  ""
#define BLUE    ""
#define MAGENTA ""
#define CYAN    ""
#define BOLD    ""

// Test statistics
int totalTests = 0;
int passedTests = 0;

// Helper function to print test results
void printTest(const string& testName, bool passed) {
    totalTests++;
    if (passed) passedTests++;
    cout << (passed ? GREEN "✓ " : RED "✗ ") << RESET << testName << endl;
}

void printSectionHeader(const string& section) {
    cout << "\n==========================================" << endl;
    cout << "  " << section << endl;
    cout << "==========================================" << endl << endl;
}

// Wrapper to show what operation is being performed
void visualizeOperation(const string& operation, const vector<int>& keys) {
    cout << "\n>> " << operation << endl;
    cout << "   Keys: ";
    for (int k : keys) cout << k << " ";
    cout << endl;
}

// ==================== BASIC OPERATION TESTS ====================

void test_empty_tree() {
    AVLTree<int> tree;
    assert(tree.find(1) == nullptr);
    printTest("Empty tree operations", true);
}

void test_single_element() {
    AVLTree<int> tree;
    tree.insert(10, 100);

    auto node = tree.find(10);
    assert(node != nullptr);
    assert(node->m_key == 10);
    assert(node->m_height == 1);

    printTest("Single element insertion", true);
}

void test_basic_insert_find() {
    AVLTree<int> tree;

    bool inserted = tree.insert(10, 100);
    assert(inserted == true);

    auto node = tree.find(10);
    assert(node != nullptr);
    assert(node->m_key == 10);

    inserted = tree.insert(10, 200);
    assert(inserted == false);

    printTest("Basic insert and find with duplicates", true);
}

void test_multiple_insertions() {
    AVLTree<string> tree;

    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");
    tree.insert(6, "six");
    tree.insert(8, "eight");

    assert(tree.find(5) != nullptr);
    assert(tree.find(3) != nullptr);
    assert(tree.find(7) != nullptr);
    assert(tree.find(2) != nullptr);
    assert(tree.find(100) == nullptr);

    printTest("Multiple sequential insertions", true);
}

// ==================== ROTATION TESTS ====================

void test_ll_rotation() {
    visualizeOperation("LL Rotation Test", {30, 20, 10});
    AVLTree<int> tree;

    tree.insert(30, 30);
    tree.insert(20, 20);
    tree.insert(10, 10);

    assert(tree.find(30) != nullptr);
    assert(tree.find(20) != nullptr);
    assert(tree.find(10) != nullptr);

    printTest("LL Rotation (descending order)", true);
}

void test_rr_rotation() {
    visualizeOperation("RR Rotation Test", {10, 20, 30});
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(20, 20);
    tree.insert(30, 30);

    assert(tree.find(10) != nullptr);
    assert(tree.find(20) != nullptr);
    assert(tree.find(30) != nullptr);

    printTest("RR Rotation (ascending order)", true);
}

void test_lr_rotation() {
    visualizeOperation("LR Rotation Test", {30, 10, 20});
    AVLTree<int> tree;

    tree.insert(30, 30);
    tree.insert(10, 10);
    tree.insert(20, 20);

    assert(tree.find(30) != nullptr);
    assert(tree.find(10) != nullptr);
    assert(tree.find(20) != nullptr);

    printTest("LR Rotation", true);
}

void test_rl_rotation() {
    visualizeOperation("RL Rotation Test", {10, 30, 20});
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(30, 30);
    tree.insert(20, 20);

    assert(tree.find(10) != nullptr);
    assert(tree.find(30) != nullptr);
    assert(tree.find(20) != nullptr);

    printTest("RL Rotation", true);
}

void test_complex_rotations() {
    visualizeOperation("Complex Multiple Rotations", {50, 25, 75, 10, 30, 60, 80, 5, 15});
    AVLTree<int> tree;

    vector<int> keys = {50, 25, 75, 10, 30, 60, 80, 5, 15};
    for (int k : keys) {
        tree.insert(k, k);
    }

    for (int k : keys) {
        assert(tree.find(k) != nullptr);
    }

    printTest("Complex multi-rotation sequence", true);
}

// ==================== DELETION TESTS ====================

void test_remove_leaf() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);

    bool removed = tree.remove(5);
    assert(removed == true);
    assert(tree.find(5) == nullptr);
    assert(tree.find(10) != nullptr);
    assert(tree.find(15) != nullptr);

    printTest("Remove leaf node", true);
}

void test_remove_one_child_left() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(3, 3);

    bool removed = tree.remove(5);
    assert(removed == true);
    assert(tree.find(5) == nullptr);
    assert(tree.find(3) != nullptr);

    printTest("Remove node with left child only", true);
}

void test_remove_one_child_right() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(18, 18);

    bool removed = tree.remove(15);
    assert(removed == true);
    assert(tree.find(15) == nullptr);
    assert(tree.find(18) != nullptr);

    printTest("Remove node with right child only", true);
}

void test_remove_two_children() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(12, 12);
    tree.insert(17, 17);

    bool removed = tree.remove(10);
    assert(removed == true);
    assert(tree.find(10) == nullptr);

    assert(tree.find(5) != nullptr);
    assert(tree.find(15) != nullptr);
    assert(tree.find(3) != nullptr);
    assert(tree.find(7) != nullptr);
    assert(tree.find(12) != nullptr);
    assert(tree.find(17) != nullptr);

    printTest("Remove node with two children", true);
}

void test_remove_nonexistent() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(5, 5);

    bool removed = tree.remove(100);
    assert(removed == false);

    printTest("Remove non-existent key", true);
}

void test_remove_root_only() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    bool removed = tree.remove(10);
    assert(removed == true);
    assert(tree.find(10) == nullptr);

    printTest("Remove root (only element)", true);
}

void test_remove_root_with_children() {
    AVLTree<int> tree;

    tree.insert(10, 10);
    tree.insert(5, 5);
    tree.insert(15, 15);

    bool removed = tree.remove(10);
    assert(removed == true);
    assert(tree.find(10) == nullptr);
    assert(tree.find(5) != nullptr);
    assert(tree.find(15) != nullptr);

    printTest("Remove root with children", true);
}

void test_remove_all_elements() {
    AVLTree<int> tree;

    vector<int> keys = {10, 5, 15, 3, 7, 12, 17};
    for (int k : keys) {
        tree.insert(k, k);
    }

    for (int k : keys) {
        bool removed = tree.remove(k);
        assert(removed == true);
        assert(tree.find(k) == nullptr);
    }

    printTest("Remove all elements sequentially", true);
}

// ==================== EDGE CASE TESTS ====================

void test_large_ascending_sequence() {
    AVLTree<int> tree;

    for (int i = 1; i <= 100; i++) {
        tree.insert(i, i * 10);
    }

    for (int i = 1; i <= 100; i++) {
        assert(tree.find(i) != nullptr);
    }

    printTest("Large ascending sequence (1-100)", true);
}

void test_large_descending_sequence() {
    AVLTree<int> tree;

    for (int i = 100; i >= 1; i--) {
        tree.insert(i, i * 10);
    }

    for (int i = 1; i <= 100; i++) {
        assert(tree.find(i) != nullptr);
    }

    printTest("Large descending sequence (100-1)", true);
}

void test_alternating_pattern() {
    AVLTree<int> tree;

    // Insert: 50, 25, 75, 12, 37, 62, 87, ...
    vector<int> keys;
    keys.push_back(50);
    keys.push_back(25);
    keys.push_back(75);
    keys.push_back(12);
    keys.push_back(37);
    keys.push_back(62);
    keys.push_back(87);
    keys.push_back(6);
    keys.push_back(18);

    for (int k : keys) {
        tree.insert(k, k);
    }

    for (int k : keys) {
        assert(tree.find(k) != nullptr);
    }

    printTest("Alternating insertion pattern", true);
}

void test_negative_keys() {
    AVLTree<int> tree;

    tree.insert(-10, 10);
    tree.insert(-5, 5);
    tree.insert(-15, 15);
    tree.insert(0, 0);
    tree.insert(5, 50);

    assert(tree.find(-10) != nullptr);
    assert(tree.find(-5) != nullptr);
    assert(tree.find(-15) != nullptr);
    assert(tree.find(0) != nullptr);
    assert(tree.find(5) != nullptr);

    printTest("Negative and mixed keys", true);
}

// ==================== COMPLEX OPERATION TESTS ====================

void test_interleaved_insert_remove() {
    AVLTree<int> tree;

    tree.insert(50, 50);
    tree.insert(25, 25);
    tree.insert(75, 75);
    tree.remove(25);
    tree.insert(30, 30);
    tree.insert(10, 10);
    tree.remove(75);
    tree.insert(80, 80);
    tree.insert(60, 60);
    tree.remove(50);
    tree.insert(55, 55);

    assert(tree.find(50) == nullptr);
    assert(tree.find(25) == nullptr);
    assert(tree.find(75) == nullptr);
    assert(tree.find(30) != nullptr);
    assert(tree.find(10) != nullptr);
    assert(tree.find(80) != nullptr);
    assert(tree.find(60) != nullptr);
    assert(tree.find(55) != nullptr);

    printTest("Interleaved insert/remove operations", true);
}

void test_build_and_destroy() {
    AVLTree<int> tree;

    for (int i = 1; i <= 50; i++) {
        tree.insert(i, i);
    }

    for (int i = 1; i <= 50; i += 2) {
        tree.remove(i);
    }

    for (int i = 1; i <= 50; i++) {
        if (i % 2 == 1) {
            assert(tree.find(i) == nullptr);
        } else {
            assert(tree.find(i) != nullptr);
        }
    }

    printTest("Build tree and remove half (odds)", true);
}

void test_remove_with_rebalancing() {
    AVLTree<int> tree;

    // Build a specific structure that will require rebalancing on delete
    vector<int> keys = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 35};
    for (int k : keys) {
        tree.insert(k, k);
    }

    // Remove nodes that trigger rebalancing
    tree.remove(10);
    tree.remove(5);

    assert(tree.find(10) == nullptr);
    assert(tree.find(5) == nullptr);

    // Verify remaining structure
    for (int k : keys) {
        if (k != 10 && k != 5) {
            assert(tree.find(k) != nullptr);
        }
    }

    printTest("Deletions triggering rebalancing", true);
}

// ==================== DATA TYPE TESTS ====================

void test_string_data() {
    AVLTree<string> tree;

    tree.insert(1, "apple");
    tree.insert(2, "banana");
    tree.insert(3, "cherry");
    tree.insert(4, "date");
    tree.insert(5, "elderberry");

    auto node = tree.find(2);
    assert(node != nullptr);
    assert(node->m_data == "banana");

    auto node3 = tree.find(3);
    assert(node3->m_data == "cherry");

    printTest("String data type operations", true);
}

void test_double_data() {
    AVLTree<double> tree;

    tree.insert(1, 3.14159);
    tree.insert(2, 2.71828);
    tree.insert(3, 1.41421);

    auto node = tree.find(1);
    assert(node != nullptr);
    assert(node->m_data > 3.14 && node->m_data < 3.15);

    printTest("Double data type operations", true);
}

// ==================== STRESS TESTS ====================

void test_stress_1000_insertions() {
    AVLTree<int> tree;

    for (int i = 0; i < 1000; i++) {
        tree.insert(i, i);
    }

    for (int i = 0; i < 1000; i++) {
        assert(tree.find(i) != nullptr);
    }

    printTest("Stress test: 1000 sequential insertions", true);
}

void test_stress_1000_random_operations() {
    AVLTree<int> tree;

    // Insert 500 elements
    for (int i = 0; i < 500; i++) {
        tree.insert(i, i * 2);
    }

    // Remove 250 elements
    for (int i = 0; i < 500; i += 2) {
        tree.remove(i);
    }

    // Verify correct elements remain
    for (int i = 0; i < 500; i++) {
        if (i % 2 == 0) {
            assert(tree.find(i) == nullptr);
        } else {
            assert(tree.find(i) != nullptr);
        }
    }

    printTest("Stress test: 500 inserts + 250 removes", true);
}

void test_stress_repeated_operations() {
    AVLTree<int> tree;

    for (int round = 0; round < 10; round++) {
        for (int i = 0; i < 50; i++) {
            tree.insert(i, i);
        }

        for (int i = 0; i < 25; i++) {
            tree.remove(i);
        }
    }

    for (int i = 25; i < 50; i++) {
        assert(tree.find(i) != nullptr);
    }

    printTest("Stress test: repeated insert/remove cycles", true);
}

// ==================== MAIN ====================

int main() {
    cout << "\n========================================================\n";
    cout << "                                                        \n";
    cout << "          AVL TREE COMPREHENSIVE TEST SUITE             \n";
    cout << "                                                        \n";
    cout << "========================================================\n";
    cout << endl;

    try {
        // Basic Operations
        printSectionHeader("BASIC OPERATIONS");
        test_empty_tree();
        test_single_element();
        test_basic_insert_find();
        test_multiple_insertions();

        // Rotation Tests
        printSectionHeader("ROTATION TESTS");
        test_ll_rotation();
        test_rr_rotation();
        test_lr_rotation();
        test_rl_rotation();
        test_complex_rotations();

        // Deletion Tests
        printSectionHeader("DELETION TESTS");
        test_remove_leaf();
        test_remove_one_child_left();
        test_remove_one_child_right();
        test_remove_two_children();
        test_remove_nonexistent();
        test_remove_root_only();
        test_remove_root_with_children();
        test_remove_all_elements();

        // Edge Cases
        printSectionHeader("EDGE CASE TESTS");
        test_large_ascending_sequence();
        test_large_descending_sequence();
        test_alternating_pattern();
        test_negative_keys();

        // Complex Operations
        printSectionHeader("COMPLEX OPERATIONS");
        test_interleaved_insert_remove();
        test_build_and_destroy();
        test_remove_with_rebalancing();

        // Data Types
        printSectionHeader("DATA TYPE TESTS");
        test_string_data();
        test_double_data();

        // Stress Tests
        printSectionHeader("STRESS TESTS");
        test_stress_1000_insertions();
        test_stress_1000_random_operations();
        test_stress_repeated_operations();

        // Summary
        cout << "\n========================================================\n";
        cout << "                    TEST SUMMARY                        \n";
        cout << "========================================================\n";

        cout << "\nTotal Tests: " << totalTests << endl;
        cout << "Passed: " << passedTests << endl;
        cout << "Failed: " << (totalTests - passedTests) << endl;

        if (passedTests == totalTests) {
            cout << "\n*** ALL TESTS PASSED! ***" << endl;
            cout << "Your AVL Tree implementation is working perfectly!" << endl;
        } else {
            cout << "\n*** SOME TESTS FAILED ***" << endl;
        }

        cout << endl;

    } catch (const exception& e) {
        cout << "\n[X] Test failed with exception: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << "\n[X] Test failed with unknown exception" << endl;
        return 1;
    }

    return (passedTests == totalTests) ? 0 : 1;
}



