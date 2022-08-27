#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Student;

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
        cout << s->courses.at(i)->name << endl;
    }
    cout << endl;
}

void print_course(Course* c) {
    cout << "Course: " << c->name << endl << "Students Enrolled:" << endl;
    for (int i = 0;i < c->students.size();i++) {
        cout << c->students.at(i)->name << endl;
    }
    cout << endl;
}

void enroll(Student* s, Course* c) {
    s->courses.push_back(c);
    c->students.push_back(s);
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

    for (int i = 0;i < 4;i++) {
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
            cin.ignore();
            getline(cin, userInput);
            Student* current = new Student;
            current->name = userInput;
            students.push_back(current);
            s = current;
        }
        else { //Already existing student.
            cout << "What is the name of the student? (Case Sensitive)\n";
            cin.ignore();
            getline(cin,userInput);
            for (int i = 0;i < students.size();i++) {
                if (students.at(i)->name == userInput) { //Finds a match in the vector.
                    s = students.at(i);
                    cout << "Match Found.\n";
                }
            }
        }
        do {
            cout << "What course would you like? (Case Sensitive)\nOptions: COMP-110, COMP-112, COMP-165, COMP-200\n";
            cin >> userInput;
            for (int i = 0;i < 4;i++) { //Compares it
                if (userInput == courses.at(i)->name) {
                    c = courses.at(i);
                    found = true;
                }
            }
        } while (found == false);

        menu(s, c);
    } while (userInput != "q");
}
