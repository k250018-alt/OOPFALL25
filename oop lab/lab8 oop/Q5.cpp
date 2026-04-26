#include<iostream>
using namespace std;
class Student{
    int subject_marks[5];
    public:
    Student(int marks[5])
    {
        for(int i=0; i<5; i++){
            subject_marks[i] = marks[i];
        }
    }
    void displayMarks()
    {
        cout << "Marks: ";
        for(int i=0; i<5; i++){
            cout << subject_marks[i] << " ";
        }
        cout << endl;
    }
    friend class Teacher;
    int calculateAverage()
    {
        int sum = 0;
        for(int i=0; i<5; i++){
            sum += subject_marks[i];
        }
        return sum / 5.0;
    }
};
class Teacher{
    int upgrading;
    public:
    Teacher(int u):upgrading(u){}
    Student operator+(Student& s)
    {   
        for(int i=0; i<5; i++){
            s.subject_marks[i] += upgrading;
        }
        return s;
    }
    
};
int main()
{
    int marks[5] = {80, 85, 90, 75, 95};
    Student s(marks);
    Teacher t(5);
    cout << "Before upgrading: ";
    s.displayMarks();
    s = t + s;
    cout << "After upgrading: ";
    s.displayMarks();
    cout << "Average Marks: " << s.calculateAverage() << endl;
    return 0;
}
