#include <iostream>
#include "book.h"
using namespace std;

int main(){
    Book b1;
    Book b2("The Great Gatsby", "F. Scott Fitzgerald", 10.99);
    Book b3(&b2);
    Book b4("To Kill a Mockingbird");
    return 0;
}