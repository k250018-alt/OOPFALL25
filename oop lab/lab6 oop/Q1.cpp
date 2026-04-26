#include<iostream>
#include<string>
using namespace std;
 
class Book {
public:
    string title, author, publisher;
    Book(string t, string a, string p) : title(t), author(a), publisher(p) {}
    void display() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publisher: " << publisher << endl;
    }
};
 
class FictionBook : public Book {
public:
    string genre, protagonist;
    FictionBook(string t, string a, string p, string g, string pro)
        : Book(t, a, p), genre(g), protagonist(pro) {}
    void display() {
        Book::display();
        cout << "Genre: " << genre << endl;
        cout << "Protagonist: " << protagonist << endl;
    }
};
 
int main() {
    FictionBook fb("The Great Adventure", "John Doe", "XYZ Publishers", "Mystery", "Alice");
    fb.display();
    return 0;
}
