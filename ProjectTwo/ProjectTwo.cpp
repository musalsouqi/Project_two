#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Structure to represent a Course
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    // Initializes course data
    Course(string number = "", string title = "", vector<string> prereqs = {})
        : courseNumber(number), courseTitle(title), prerequisites(prereqs) {}
};

// Node structure for the Binary Search Tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Initializes the node with a course
    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class CourseBST {
private:
    Node* root;

    // Prints all courses in sorted order
    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            // Traverse left subtree
            inOrderTraversal(node->left);

            // Print course details
            cout << node->course.courseNumber << ": " << node->course.courseTitle << endl;

            // Print prerequisites if available
            if (!node->course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (const string& prereq : node->course.prerequisites) {
                    cout << prereq << " ";
                }
                cout << endl;
            }
            else {
                cout << "Prerequisites: None" << endl;
            }

            // Traverse right subtree
            inOrderTraversal(node->right);
        }
    }

    // Inserts a course into the tree
    Node* insert(Node* node, Course course) {
        if (node == nullptr) {
            // Create a new node if the current node is empty
            return new Node(course);
        }

        // Insert into the left subtree if the course number is smaller
        if (course.courseNumber < node->course.courseNumber) {
            node->left = insert(node->left, course);
        }
        // Insert into the right subtree if the course number is larger
        else if (course.courseNumber > node->course.courseNumber) {
            node->right = insert(node->right, course);
        }

        return node;
    }

    // Searches for a course by course number
    Node* search(Node* node, const string& courseNumber) {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            // Return the node if found or if the tree is empty
            return node;
        }

        // Search left subtree if the course number is smaller
        if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }

        // Search right subtree if the course number is larger
        return search(node->right, courseNumber);
    }

public:
    // Initializes the binary search tree
    CourseBST() : root(nullptr) {}

    // Inserts a course into the tree
    void insertCourse(Course course) {
        root = insert(root, course);
    }

    // Prints all courses in sorted order
    void printAllCourses() {
        inOrderTraversal(root);
    }

    // Prints details of a specific course
    void printCourseDetails(const string& courseNumber) {
        // Search for the course in the tree
        Node* node = search(root, courseNumber);

        if (node == nullptr) {
            // Print if the course is not found
            cout << "Course not found." << endl;
        }
        else {
            // Print the course details
            cout << node->course.courseNumber << ": " << node->course.courseTitle << endl;

            // Print prerequisites if available
            if (!node->course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (const string& prereq : node->course.prerequisites) {
                    cout << prereq << " ";
                }
                cout << endl;
            }
            else {
                cout << "Prerequisites: None" << endl;
            }
        }
    }

    // Checks if the tree is empty
    bool isEmpty() {
        return root == nullptr;
    }
};

// Loads and parses the CSV file
void loadCoursesFromFile(CourseBST& bst) {
    const string fileName = "CS 300 ABCU_Advising_Program_Input.csv"; // File name
    ifstream file(fileName);

    // Check if the file can be opened
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq1, prereq2;

        // Read course number, title, and prerequisites from the line
        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');
        getline(ss, prereq1, ',');
        getline(ss, prereq2, ',');

        // Skip invalid rows
        if (courseNumber.empty() || courseTitle.empty()) {
            cout << "Error: Invalid format in line: " << line << endl;
            continue;
        }

        // Collect prerequisites
        vector<string> prerequisites;
        if (!prereq1.empty()) prerequisites.push_back(prereq1);
        if (!prereq2.empty()) prerequisites.push_back(prereq2);

        // Create a course object and insert into the tree
        Course course(courseNumber, courseTitle, prerequisites);
        bst.insertCourse(course);
    }

    file.close();
    cout << "Courses successfully loaded from file." << endl;
}

// Displays the menu options
void displayMenu() {
    cout << "\nMenu Options:" << endl;
    cout << "1. Load the file data into the data structure" << endl;
    cout << "2. Print an alphanumerically ordered list of all courses" << endl;
    cout << "3. Print course title and prerequisites for a specific course" << endl;
    cout << "9. Exit the program" << endl;
}

// Handles the menu and user input
void menu() {
    CourseBST bst; // Create the binary search tree
    int choice = 0;

    while (true) {
        displayMenu();

        // Read user choice
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // Load course data
            cout << "Loading file data..." << endl;
            loadCoursesFromFile(bst);
            cout << "Data successfully loaded!" << endl;
        }
        else if (choice == 2) {
            if (bst.isEmpty()) {
                // Handle case where no data is loaded
                cout << "No data loaded. Please load the file data first." << endl;
            }
            else {
                // Print all courses
                cout << "Printing all courses in alphanumeric order..." << endl;
                bst.printAllCourses();
            }
        }
        else if (choice == 3) {
            if (bst.isEmpty()) {
                // Handle case where no data is loaded
                cout << "No data loaded. Please load the file data first." << endl;
            }
            else {
                // Search for a specific course
                cout << "Enter the course number to search: ";
                string courseNumber;
                cin >> courseNumber;
                bst.printCourseDetails(courseNumber);
            }
        }
        else if (choice == 9) {
            // Exit the program
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
        else {
            // Handle invalid menu choices
            cout << "Invalid option. Please try again." << endl;
        }
    }
}

// Main function
int main() {
    menu(); // Run the menu
    return 0;
}
