#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Student; //Declaring the struct student so that I won't get an error for vector<Student*> students.

struct Course {
    string name;
    vector<Student*> students;
};

struct Student {
    string name;
    vector<Course*> courses;
};

void print_student(Student* s) {
    cout << "Student's name: " << s->name << endl << "Student's Courses:" << endl;
    for (int i = 0;i < s->courses.size();i++) {
        cout << s->courses.at(i)->name << endl; //Prints the student's courses from the vector;
    }
    cout << endl;
}

void print_course(Course* c) {
    cout << "Course: " << c->name << endl << "Students Enrolled:" << endl;
    for (int i = 0;i < c->students.size();i++) {
        cout << c->students.at(i)->name << endl; //Prints the courses' students from the vector;
    }
    cout << endl;
}

void enroll(Student* s, Course* c) {
    s->courses.push_back(c); //adds to the vector
    c->students.push_back(s); //adds to the vector
    cout << s->name << " has been sucessfully added to " << c->name << ".\n";
}

void menu(Student* s, Course* c) {
    char userInput;

    cout << "Menu:\ns - prints the name of a student and the names of all courses that the student takes\n";
    cout << "c - prints the name of a course and the names of all students in that course.\ne - enrolls the given student in the given course\nInput: ";

    cin >> userInput;

    switch (userInput) {
    case 's':
        print_student(s);
        break;
    case 'c':
        print_course(c);
        break;
    case 'e':
        enroll(s, c);
        break;
    }
}

int main()
{
    string userInput, name, courseNames[4] = { "COMP-110","COMP-112","COMP-165","COMP-200" };
    bool found = false;

    Course* c = new Course;
    Student* s = new Student;
    vector<Student*> students;
    vector<Course*> courses;

    for (int i = 0;i < 4;i++) { //Creates all the courses and adds them to the courses vector in main.
        Course* a = new Course;
        a->name = courseNames[i];
        courses.push_back(a);
    }

    do {
        cout << "Enter q to quit or enter any other character to continue.\n";
        cin >> userInput;
        if (userInput == "q") {
            break;
        }
        cout << "Are you creating a new student? (Case Sensitive) Y/N\n";
        cin >> userInput;
        if (
            userInput == "Y") {
            cout << "What is their name? (Case Sensitive)\n";
            cin.ignore(); //Prevent the getline issue.
            getline(cin, userInput);
            Student* current = new Student; //Creates a new Student.
            current->name = userInput; //Sets the new Student's name variable to userInput.
            students.push_back(current); //Adds the new Student to the students vector in main.
            s = current;
        }
        else { //Already existing student.
            cout << "What is the name of the student? (Case Sensitive)\n";
            cin.ignore(); //Prevent the getline issue.
            getline(cin,userInput);
            for (int i = 0;i < students.size();i++) {
                if (students.at(i)->name == userInput) { //Finds a match in the vector.
                    s = students.at(i); //Sets the pointer s to the matching student name.
                    cout << "Match Found.\n";
                }
            }
        }
        do {
            cout << "What course would you like? (Case Sensitive)\nOptions: COMP-110, COMP-112, COMP-165, COMP-200\n";
            cin >> userInput;
            for (int i = 0;i < 4;i++) { //Compares it
                if (userInput == courses.at(i)->name) {
                    c = courses.at(i); //Sets the pointer c to the corresponding course.
                    found = true;
                }
            }
        } while (found == false); //Runs this while loop, which asks for the course they would like to look into, until they input an available course.

        menu(s, c);
    } while (userInput != "q");
}
