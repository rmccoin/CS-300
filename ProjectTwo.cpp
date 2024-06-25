//================================================================================
// Name        : ProjectTwo.cpp
// Author      : Rodrey McCoin 
// Description : Loads course data from a CSV file and loads into a data structure
//================================================================================
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Structure to hold course information
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;   //vector to store string for the prerequisites of the course
};

vector<Course> courses; //vector to store the course objects 


// Load Course data from CSV file into the data structure, csvPath
void loadCourses(const string& csvPath) {
    ifstream file("CS 300 ABCU_Advising_Program_Input.csv"); 

    //if file does not open, print error message, and exit function  
    if (!file.is_open()) { 
        cout << "The file, " << csvPath << "was unable to open. Try again." << endl;
        return; 
    }

    string line; // create string to store each line in the file 

    //read each line of the file, while line, store data in structure course
    while (getline(file, line)) {
        Course course; 
        size_t pos = line.find(","); 
        course.courseNumber = line.substr(0, pos); 
        line.erase(0, pos + 1); 
        pos = line.find(",");   //use commas to determine end of data
        course.title = line.substr(0, pos); 
        line.erase(0, pos + 1); 

        //loop to extract and store prerequisites of each course 
        while (!line.empty()) {
            pos = line.find(","); 
            string prerequisite = line.substr(0, pos); 
            course.prerequisites.push_back(prerequisite); 
            if (pos == string::npos) break; //if no more commas, end loop 
            line.erase(0, pos + 1); 
        }

        courses.push_back(course); // adds course object to the end of the vector 
    }

    //close the file 
    file.close(); 
}

// Function to print a list of courses in alphanumeric order
void printCourseList() {

    // Sort courses based on course number
    sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    cout << "Courses Listed:\n" << endl; 
    // Loops through each course and prints its number and title, seperates with a comma 
    for (const auto& course : courses) {
        cout << course.courseNumber << ", " << course.title << endl;
    }
}

// Function to print information about a specific course
void printCourse(const string& courseNumber) {
    // searches the courses for course number entered 
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
        return c.courseNumber == courseNumber;
        });

    //if course is found, print course number and title, followed by prerequisites 
    if (it != courses.end()) { 
        cout << it->courseNumber << ", " << it->title << endl; 
        cout << "Prerequisites: ";

        //if no prerequisites found, print none in place of their course number
        if (it->prerequisites.empty()) { 
            cout << "None" << endl; 
        }

        //else loop through and print out each prerequisite listed under the course 
        else {
            for (const auto& prerequisite : it->prerequisites) {
                cout << prerequisite << ", ";
            }
            cout << endl;
        }
    }

    //if no course found print error message 
    else { 
        cout << "No course found." << endl; 
    }
}

//main function that holds menu and cases
int main() {
    string csvPath; 
    int choice = 0; 
    string courseNumber; 

    cout << "Welcome to the course planner." << endl;

    //menu options for the user to select from
    while (choice != 9) {
        cout << "\n   1. Load Data Structure." << endl;
        cout << "   2. Print Course List." << endl;
        cout << "   3. Print Course." << endl;
        cout << "   9. Exit\n" << endl;
        cout << "What would you like to do? "; 
        cin >> choice; 

        switch (choice) { 
        case 1: 
            cout << "Enter the file name: "; 
            cin >> csvPath; //calls csvPath function to load file into data structure 
            loadCourses(csvPath);   //loads courses from CSV file into data structure 
            break; 
        case 2:
            printCourseList(); //prints all courses saved in the CSV file in a list 
            break; 
        case 3:
            cout << "What course do you want to know about? "; 
            cin >> courseNumber;    //enter courseNumber to view it along with data 
            printCourse(courseNumber);  // call printCourse function, print course number with prerequisites if they exist, if none, print "none" 
            break; 
        case 9: 
            cout << "Thank you for using the course planner!" << endl;  //message when choice 9 is selected and program exits
            break; 
        default: 
            cout << "Choice:" << choice << " is not valid." << endl;    //error message when choice entered does not exist
        }
    } 

    //end main function 
    return 0;
}