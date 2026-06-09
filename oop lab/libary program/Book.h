#pragma once
#include <iostream>
using namespace std;

class Book{
    string title;
    string isbn;

    public:
    static int totalBooks;
    Book(string title , string isbn) : title(title), isbn(isbn){
        totalBooks++;
    };

    void displayBooks(){
        cout << isbn <<"       "<<title<<endl;
    }
    ~Book(){
        totalBooks--;
        cout<<"Book "<< title <<" deleted"<<endl;
        cout<<"Total books :" << totalBooks <<endl;
    }

};
int Book::totalBooks =0;