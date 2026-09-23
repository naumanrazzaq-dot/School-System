#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Base Abstract Class
class Person {
protected:
    string name;
    int id;

public:
    static int totalMembers;

    Person(string name, int id) : name(name), id(id) {
        totalMembers++;
    }

    virtual ~Person() {
        cout << "[REMOVED] Record for " << name << " (ID: " << id << ") cleared." << endl;
        totalMembers--;
    }

    virtual void displayDetails() const = 0; // Pure Virtual Function
    virtual double calculateDuesOrPay() const = 0; // Pure Virtual Function
};

// Static member initialization
int Person::totalMembers = 0;

// Derived Class 1: Student
class Student : public Person {
private:
    double tuitionFee;
    double scholarshipPercentage;

public:
    Student(string name, int id, double fee, double scholarship)
        : Person(name, id), tuitionFee(fee), scholarshipPercentage(scholarship) {}

    ~Student() override {
        cout << " -> Archiving academic grades for Student " << name << "..." << endl;
    }

    double calculateDuesOrPay() const override {
        // Payable fee after scholarship discount
        return tuitionFee - (tuitionFee * (scholarshipPercentage / 100.0));
    }

    void displayDetails() const override {
        cout << "\n--- [STUDENT RECORD] ---" << endl;
        cout << "Name           : " << name << endl;
        cout << "Student ID     : " << id << endl;
        cout << "Scholarship    : " << scholarshipPercentage << "%" << endl;
        cout << "Net Fee Payable: Rs. " << fixed << setprecision(2) << calculateDuesOrPay() << endl;
    }
};

// Derived Class 2: Teacher
class Teacher : public Person {
private:
    double basicSalary;
    int extraClassesCount;

public:
    Teacher(string name, int id, double salary, int extraClasses)
        : Person(name, id), basicSalary(salary), extraClassesCount(extraClasses) {}

    ~Teacher() override {
        cout << " -> Processing payroll clearance for Teacher " << name << "..." << endl;
    }

    double calculateDuesOrPay() const override {
        // Rs. 1500 bonus per extra lecture
        return basicSalary + (extraClassesCount * 1500.0);
    }

    void displayDetails() const override {
        cout << "\n--- [TEACHER RECORD] ---" << endl;
        cout << "Name           : " << name << endl;
        cout << "Staff ID       : " << id << endl;
        cout << "Extra Classes  : " << extraClassesCount << endl;
        cout << "Total Salary   : Rs. " << fixed << setprecision(2) << calculateDuesOrPay() << endl;
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "   SCHOOL MANAGEMENT REGISTRY SYSTEM   " << endl;
    cout << "========================================" << endl;

    // Array of base class pointers
    const int SIZE = 2;
    Person* schoolList[SIZE];

    // Heap allocation
    schoolList[0] = new Student("Hamza Ali", 101, 45000.0, 20.0);
    schoolList[1] = new Teacher("Dr. Tariq", 501, 85000.0, 6);

    // Polymorphic display loop
    for (int i = 0; i < SIZE; i++) {
        schoolList[i]->displayDetails();
    }

    cout << "\n----------------------------------------" << endl;
    cout << "Total Active Campus Members: " << Person::totalMembers << endl;
    cout << "----------------------------------------\n" << endl;

    // Memory clean up (Virtual Destructors in action)
    for (int i = 0; i < SIZE; i++) {
        delete schoolList[i];
        schoolList[i] = nullptr;
    }

    cout << "\n----------------------------------------" << endl;
    cout << "Members in Memory after Deletion: " << Person::totalMembers << endl;
    cout << "----------------------------------------" << endl;

    return 0;
}