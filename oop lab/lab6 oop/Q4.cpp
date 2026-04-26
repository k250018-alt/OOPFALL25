#include<iostream>
#include<string>
using namespace std;
 
class Person {
public:
    string name;
    int age;
    Person(string n, int a) : name(n), age(a) {}
    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};
 
class Student : virtual public Person {
public:
    string studentID;
    int gradeLevel;
    Student(string n, int a, string id, int gl)
        : Person(n, a), studentID(id), gradeLevel(gl) {}
    void display() {
        Person::display();
        cout << "Student ID: " << studentID << ", Grade Level: " << gradeLevel << endl;
    }
};
 
class Teacher : virtual public Person {
public:
    string subject;
    int roomNumber;
    Teacher(string n, int a, string sub, int room)
        : Person(n, a), subject(sub), roomNumber(room) {}
    void display() {
        Person::display();
        cout << "Subject: " << subject << ", Room: " << roomNumber << endl;
    }
};
 
class GraduateStudent : public Student, public Teacher {
public:
    GraduateStudent(string n, int a, string id, int gl, string sub, int room)
        : Person(n, a), Student(n, a, id, gl), Teacher(n, a, sub, room) {}
    void display() {
        Person::display();
        cout << "Student ID: " << studentID << ", Grade: " << gradeLevel << endl;
        cout << "Subject: " << subject << ", Room: " << roomNumber << endl;
    }
};
 
int main() {
    GraduateStudent gs("Ali", 24, "S101", 4, "Mathematics", 305);
    gs.display();
    return 0;
}
