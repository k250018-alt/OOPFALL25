#include"iostream"
using namespace std;
void setgrade(int m , char &gra){
        if(m>=90)
            gra='A';
        else if(m>=80)
            gra='B';
        else if(m>=70)
            gra='C';
        else if(m>=60)
            gra='D';
        else
            gra='F';
    }
class Subject{
    string name;
    int marks;
    char grade;
    public:
    Subject(){
        cout<<"enter subject name: ";
        cin>>name;
        cout<<"enter marks for " << name << " : ";
        cin>>marks;
        setgrade(marks , grade);
    }
    int getmarks(){
        return marks;
    }
    char getgrade(){
        return grade;
    }
    string getname(){
        return name;
    }
};
class Student{
    int avg_marks;
    int total_marks;
    char std_grade;
    public:
    Student(Subject s[], int n){
        total_marks=0;
        avg_marks=0;
        for(int i=0;i<n;i++){
            total_marks+=s[i].getmarks();
        }
        avg_marks=total_marks/n;
    }
    void show_details(Subject s[] ,int n ){
        cout<< "Subject name  |    marks      |      grade" << endl;
        for(int i=0;i<n;i++){
            cout<<s[i].getname() << ":" << s[i].getmarks() << "|" << s[i].getgrade() <<endl;
        }
        cout<< "average : " << avg_marks << endl;
        cout<< "total  :  " << total_marks << endl;
        setgrade(avg_marks , std_grade);
        cout<< "grade  : "<< std_grade ;
    }
};
int main(){
    Subject subs[6];
    Student stud(subs , 6);
    stud.show_details(subs , 6);
}