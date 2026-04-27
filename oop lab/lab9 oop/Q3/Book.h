#pragma once
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    std::string ISBN;

public:
    Book(const std::string& title, const std::string& author, const std::string& ISBN)
        : title(title), author(author), ISBN(ISBN) {}

    std::string getTitle()  const { return title; }
    std::string getAuthor() const { return author; }
    std::string getISBN()   const { return ISBN; }
};