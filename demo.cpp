#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int roll;
    string name;
    string course;

    void input() {
        cout << "Enter Roll No: ";
        cin >> roll;
        cin.ignore();  // clears the input buffer
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() {
        cout << "\nRoll No: " << roll;
        cout << "\nName: " << name;
        cout << "\nCourse: " << course << "\n";
    }
};

void addStudent() {
    Student s;
    s.input();

    ofstream outFile("students.txt", ios::app);
    outFile << s.roll << '\n'
            << s.name << '\n'
            << s.course << '\n';
    outFile.close();

    cout << "Student record added successfully.\n";
}

void displayAll() {
    Student s;
    ifstream inFile("students.txt");

    while (inFile >> s.roll) {
        inFile.ignore();
        getline(inFile, s.name);
        getline(inFile, s.course);
        s.display();
        cout << "---------------------\n";
    }

    inFile.close();
}

void searchStudent(int rollNo) {
    Student s;
    bool found = false;
    ifstream inFile("students.txt");

    while (inFile >> s.roll) {
        inFile.ignore();
        getline(inFile, s.name);
        getline(inFile, s.course);

        if (s.roll == rollNo) {
            s.display();
            found = true;
        }
    }

    inFile.close();
    if (!found)
        cout << "Student not found.\n";
}

void deleteStudent(int rollNo) {
    Student s;
    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt");

    bool found = false;

    while (inFile >> s.roll) {
        inFile.ignore();
        getline(inFile, s.name);
        getline(inFile, s.course);

        if (s.roll != rollNo) {
            tempFile << s.roll << '\n'
                     << s.name << '\n'
                     << s.course << '\n';
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student record deleted successfully.\n";
    else
        cout << "Student not found.\n";
}

void updateStudent(int rollNo) {
    Student s;
    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt");

    bool found = false;

    while (inFile >> s.roll) {
        inFile.ignore();
        getline(inFile, s.name);
        getline(inFile, s.course);

        if (s.roll == rollNo) {
            cout << "Current record:\n";
            s.display();
            cout << "Enter new details:\n";
            s.input();
            found = true;
        }

        tempFile << s.roll << '\n'
                 << s.name << '\n'
                 << s.course << '\n';
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student record updated successfully.\n";
    else
        cout << "Student not found.\n";
}

int main() {
    ofstream clear("students.txt", ios::trunc);  // clears old records
    clear.close();

    int choice, rollNo;

    do {
        cout << "\n--- Student Record Management ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            cout << "Enter Roll No: ";
            cin >> rollNo;
            searchStudent(rollNo);
            break;
        case 4:
            cout << "Enter Roll No to delete: ";
            cin >> rollNo;
            deleteStudent(rollNo);
            break;
        case 5:
            cout << "Enter Roll No to update: ";
            cin >> rollNo;
            updateStudent(rollNo);
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}