#include <iostream>
#include <string>
#include "Book.h"

class Library {
private:
    static const int MAX = 10;
    Book* books[MAX];
    int count;

public:
    Library() : count(0) {
        for (int i = 0; i < MAX; i++)
            books[i] = nullptr;
    }

    ~Library() {
        for (int i = 0; i < count; i++)
            delete books[i];
    }

    void addBook(const std::string& title, const std::string& author, const std::string& ISBN) {
        if (count < MAX) {
            books[count++] = new Book(title, author, ISBN);
            std::cout << "Added: \"" << title << "\"\n";
        } else {
            std::cout << "Library is full.\n";
        }
    }

    bool removeBook(const std::string& ISBN) {
        for (int i = 0; i < count; i++) {
            if (books[i]->getISBN() == ISBN) {
                std::cout << "Removed: \"" << books[i]->getTitle() << "\"\n";
                delete books[i];
                books[i] = books[--count];
                books[count] = nullptr;
                return true;
            }
        }
        std::cout << "Book not found.\n";
        return false;
    }

    void searchBook(const std::string& title) const {
        for (int i = 0; i < count; i++) {
            if (books[i]->getTitle().find(title) != std::string::npos) {
                std::cout << "Found: \"" << books[i]->getTitle()
                          << "\" | Author: " << books[i]->getAuthor()
                          << " | ISBN: "     << books[i]->getISBN() << "\n";
                return;
            }
        }
        std::cout << "\"" << title << "\" not found.\n";
    }

    void displayAll() const {
        if (count == 0) {
            std::cout << "No books in the library.\n";
            return;
        }
        std::cout << "\n--- Library (" << count << " books) ---\n";
        for (int i = 0; i < count; i++) {
            std::cout << i + 1 << ". \"" << books[i]->getTitle()
                      << "\" | " << books[i]->getAuthor()
                      << " | "   << books[i]->getISBN() << "\n";
        }
        std::cout << "---------------------------\n";
    }
};

int main() {
    Library lib;

    lib.addBook("The Great Gatsby",      "F. Scott Fitzgerald", "978-0-7432-7356-5");
    lib.addBook("To Kill a Mockingbird", "Harper Lee",          "978-0-0613-5527-2");
    lib.addBook("1984",                  "George Orwell",       "978-0-4517-2484-3");
    lib.addBook("Brave New World",       "Aldous Huxley",       "978-0-0699-2840-8");

    lib.displayAll();

    std::cout << "\n--- Search ---\n";
    lib.searchBook("1984");

    std::cout << "\n--- Remove ---\n";
    lib.removeBook("978-0-0613-5527-2");

    lib.displayAll();

    return 0;
}