#include<iostream>
#include<string>
using namespace std;

class Person {
protected:
    string name, address, phoneNumber, email;
    int id;
public:
    Person(string n, int i, string addr, string phone, string mail)
        : name(n), id(i), address(addr), phoneNumber(phone), email(mail) {}

    virtual void displayInfo() {
        cout << "Name: " << name << " | ID: " << id << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phoneNumber << " | Email: " << email << endl;
    }
    void updateInfo(string addr, string phone, string mail) {
        address = addr; phoneNumber = phone; email = mail;
        cout << "Info updated." << endl;
    }
    virtual ~Person() {}
};

class Student : public Person {
    string courses[10];
    int courseCount;
    double GPA;
    int enrollmentYear;
public:
    Student(string n, int i, string addr, string phone, string mail, double gpa, int year)
        : Person(n, i, addr, phone, mail), GPA(gpa), enrollmentYear(year), courseCount(0) {}

    void enroll(string course) {
        if (courseCount < 10) courses[courseCount++] = course;
    }
    void displayInfo() override {
        Person::displayInfo();
        cout << "GPA: " << GPA << " | Enrolled: " << enrollmentYear << endl;
        cout << "Courses: ";
        for (int i = 0; i < courseCount; i++) cout << courses[i] << " ";
        cout << endl;
    }
};

class Professor : public Person {
    string department;
    string coursesTaught[10];
    int courseCount;
    double salary;
public:
    Professor(string n, int i, string addr, string phone, string mail, string dept, double sal)
        : Person(n, i, addr, phone, mail), department(dept), salary(sal), courseCount(0) {}

    void addCourse(string c) {
        if (courseCount < 10) coursesTaught[courseCount++] = c;
    }
    void displayInfo() override {
        Person::displayInfo();
        cout << "Department: " << department << " | Salary: $" << salary << endl;
        cout << "Courses Taught: ";
        for (int i = 0; i < courseCount; i++) cout << coursesTaught[i] << " ";
        cout << endl;
    }
};

class Staff : public Person {
    string department, position;
    double salary;
public:
    Staff(string n, int i, string addr, string phone, string mail, string dept, string pos, double sal)
        : Person(n, i, addr, phone, mail), department(dept), position(pos), salary(sal) {}

    void displayInfo() override {
        Person::displayInfo();
        cout << "Dept: " << department << " | Position: " << position
             << " | Salary: $" << salary << endl;
    }
};

class Course {
    string courseId, courseName, schedule;
    int credits;
    Professor* instructor;
    Student* students[50];
    int studentCount;
public:
    Course(string id, string name, int cr, Professor* prof, string sch)
        : courseId(id), courseName(name), credits(cr), instructor(prof),
          schedule(sch), studentCount(0) {}

    void registerStudent(Student* s) {
        if (studentCount < 50) {
            students[studentCount++] = s;
            cout << "Student registered in " << courseName << endl;
        }
    }
    void calculateGrades() {
        cout << "Calculating grades for " << courseName
             << " (" << studentCount << " students)" << endl;
    }
    void displayCourse() {
        cout << "Course: " << courseName << " | ID: " << courseId
             << " | Credits: " << credits << " | Schedule: " << schedule << endl;
    }
};

int main() {
    Student s("Ali", 1, "Karachi", "0300-1234567", "ali@uni.edu", 3.8, 2023);
    s.enroll("OOP"); s.enroll("DSA");
    s.displayInfo();

    Professor p("Dr. Ahmed", 101, "Lahore", "0321-0000001", "ahmed@uni.edu", "CS", 150000);
    p.addCourse("OOP"); p.addCourse("AI");
    p.displayInfo();

    Staff st("Mr. Usman", 201, "Islamabad", "0333-9999999", "usman@uni.edu", "Admin", "Registrar", 80000);
    st.displayInfo();

    Course oop("CS301", "OOP", 3, &p, "Mon/Wed 10am");
    oop.registerStudent(&s);
    oop.calculateGrades();
    oop.displayCourse();

    return 0;
}

