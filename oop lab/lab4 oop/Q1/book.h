#pragma once
#include <iostream>
using namespace std;

class Book{
    private:
        string *title;
        string *author;
        float *price;
    public:
        Book(){
            title = new string("Untitled");
            author = new string("Unknown");
            price = new float(0.0);
        }
        Book(string t, string a, float p){
            title = new string(t);
            author = new string(a);
            price = new float(p);
        }
        Book(Book *obj){
            title = obj->title;
            author = obj->author;
            price = obj->price;
        }
        Book(string t){
            title = new string(t);
            author = new string("Anonymous");
            price = new float(0.0);
        }
        
};
