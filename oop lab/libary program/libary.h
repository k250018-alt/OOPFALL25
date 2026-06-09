#pragma once
#include<iostream>
#include"Book.h"
#include"member.h"
using namespace std;
const int maxCapacity = 100;
class  Libary{
    string libaryname;
    int bookcount;
    int membercount;
    Book *books[maxCapacity];
    Member *member[maxCapacity];

    public:
    Libary(string Libaryname):libaryname(Libaryname),bookcount(0),membercount(0){};

    void addBook(string title , string isbn){
        if(bookcount < maxCapacity){
            books[bookcount] = new Book(title,isbn);
            bookcount++;
        }
        else{
            cout <<"Connot add mare books"<< endl;
        }
    }
    void addmember(Member *m){
        if(membercount < maxCapacity){
            member[membercount] = m;
            membercount++;
        }
        else{
            cout <<"Connot add mare members"<< endl;
        }
    }
    void displayDetails(){
        cout<<"-----------System state-----------"<<endl;
        cout<<"Total Books: "<<Book::totalBooks<<endl;
        for(int i = 0 ; i < bookcount ;i++){
            books[i]->displayBooks();
        }
        for(int i=0 ; i< membercount;i++){
            cout << "Member Name: "<<member[i]->getmember()<<endl;
        }
    }
    ~Libary(){
        for(int i =0 ; i < bookcount ; i++){
            delete books[i];
        }
    }
};
