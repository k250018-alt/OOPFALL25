#include "iostream"
using namespace std; // CLion free
int n;
typedef struct
{
    string title;
    string author;
    int year;
    string genere;
} Book;

void create(int n, Book *books)
{
    n++;
    Book *books = new Book[n];
    cout << "Enter the title of the book";
    cin >> books[n].title;
    cout << "Enter the author of the book";
    cin >> books[n].author;
    cout << "Enter the year of publication of the book";
    cin >> books[n].year;
    cout << "Enter the genere of the book";
    cin >> books[n].genere;
}
void modification(int pointer_of_book, Book *books)
{
    cout << "Enter the new title of the book";
    cin >> books[pointer_of_book].title;
    cout << "Enter the new author of the book";
    cin >> books[pointer_of_book].author;
    cout << "Enter the new year of publication of the book";
    cin >> books[pointer_of_book].year;
    cout << "Enter the new genere of the book";
    cin >> books[pointer_of_book].genere;
}
void display(int n, Book *books)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Title of the book: " << books[i].title << endl;
        cout << "Author of the book: " << books[i].author << endl;
        cout << "Year of publication of the book: " << books[i].year << endl;
        cout << "Genere of the book: " << books[i].genere << endl;
    }
}
void input(int n, Book *books)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the title of the book";
        cin >> books[i].title;
        cout << "Enter the author of the book";
        cin >> books[i].author;
        cout << "Enter the year of publication of the book";
        cin >> books[i].year;
        cout << "Enter the genere of the book";
        cin >> books[i].genere;
    }
}
void search_by_title(int n, Book *books, string title)
{
    for (int i = 0; i < n; i++)
    {
        if (books[i].title == title)
        {
            cout << "Book found: " << endl;
            cout << "Title: " << books[i].title << endl;
            cout << "Author: " << books[i].author << endl;
            cout << "Year: " << books[i].year << endl;
            cout << "Genere: " << books[i].genere << endl;
            return;
        }
    }
    cout << "Book not found" << endl;
}
void search_by_author(int n, Book *books, string author)
{
    for (int i = 0; i < n; i++)
    {
        if (books[i].author == author)
        {
            cout << "Book found: " << endl;
            cout << "Title: " << books[i].title << endl;
            cout << "Author: " << books[i].author << endl;
            cout << "Year: " << books[i].year << endl;
            cout << "Genere: " << books[i].genere << endl;
            return;
        }
    }
    cout << "Book not found" << endl;
}
int main()
{
    cout << "Enter the number of books";
    cin >> n;
    Book *books = new Book[n];
    create(n, books);
    int pointer_of_book;
    input(n, books);
    int choice;
    do
    {
        cout << "Menu: \n1. Modification of book details\n2. Display all books\n3. Search book by title\n4. Search book by author\n5. Exit\n";
        cin >> choice;
        if (choice == 1)
        {
            cout << "Enter the pointer of the book to be modified";
            cin >> pointer_of_book;
            modification(pointer_of_book, books);
        }
        else if (choice == 2)
        {
            display(n, books);
        }
        else if (choice == 3)
        {
            string title;
            cout << "Enter the title of the book to be searched";
            cin >> title;
            search_by_title(n, books, title);
        }
        else if (choice == 4)
        {
            string author;
            cout << "Enter the author of the book to be searched";
            cin >> author;
            search_by_author(n, books, author);
        }
    } while (choice != 5);
    delete[] books;
}