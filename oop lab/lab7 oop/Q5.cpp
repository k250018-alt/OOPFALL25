#include<iostream>
#include<string>
using namespace std;

class Media {
protected:
    string title, publisher, uniqueID;
    int publicationDate;
    bool checkedOut;
public:
    Media(string t, string pub, string id, int date)
        : title(t), publisher(pub), uniqueID(id), publicationDate(date), checkedOut(false) {}

    virtual void displayInfo() {
        cout << "ID: " << uniqueID << " | Title: " << title
             << " | Publisher: " << publisher << " | Year: " << publicationDate << endl;
    }
    void checkOut() {
        if (checkedOut) { cout << title << " is already checked out." << endl; return; }
        checkedOut = true;
        cout << title << " checked out successfully." << endl;
    }
    void returnItem() {
        if (!checkedOut) { cout << title << " was not checked out." << endl; return; }
        checkedOut = false;
        cout << title << " returned successfully." << endl;
    }
    string getTitle() const { return title; }
    int getYear() const { return publicationDate; }
    virtual ~Media() {}
};

class Book : public Media {
    string author, ISBN;
    int numberOfPages;
public:
    Book(string t, string pub, string id, int date, string auth, string isbn, int pages)
        : Media(t, pub, id, date), author(auth), ISBN(isbn), numberOfPages(pages) {}

    void displayInfo() override {
        Media::displayInfo();
        cout << "Author: " << author << " | ISBN: " << ISBN
             << " | Pages: " << numberOfPages << endl;
    }
    string getAuthor() const { return author; }
};

class DVD : public Media {
    string director, rating;
    int duration;
public:
    DVD(string t, string pub, string id, int date, string dir, int dur, string rat)
        : Media(t, pub, id, date), director(dir), duration(dur), rating(rat) {}

    void displayInfo() override {
        Media::displayInfo();
        cout << "Director: " << director << " | Duration: " << duration
             << " min | Rating: " << rating << endl;
    }
};

class CD : public Media {
    string artist, genre;
    int numberOfTracks;
public:
    CD(string t, string pub, string id, int date, string art, int tracks, string gen)
        : Media(t, pub, id, date), artist(art), numberOfTracks(tracks), genre(gen) {}

    void displayInfo() override {
        Media::displayInfo();
        cout << "Artist: " << artist << " | Tracks: " << numberOfTracks
             << " | Genre: " << genre << endl;
    }
};

class Magazine : public Media {
    int issueNumber;
    string category;
public:
    Magazine(string t, string pub, string id, int date, int issue, string cat)
        : Media(t, pub, id, date), issueNumber(issue), category(cat) {}

    void displayInfo() override {
        Media::displayInfo();
        cout << "Issue: " << issueNumber << " | Category: " << category << endl;
    }
};

class Library {
    Media* items[100];
    int count;
public:
    Library() : count(0) {}

    void addItem(Media* m) {
        if (count < 100) items[count++] = m;
    }
    // search by title
    void search(string title) {
        cout << "\nSearch by Title: " << title << endl;
        for (int i = 0; i < count; i++)
            if (items[i]->getTitle() == title) { items[i]->displayInfo(); return; }
        cout << "Not found." << endl;
    }
    // search by year
    void search(int year) {
        cout << "\nSearch by Year: " << year << endl;
        for (int i = 0; i < count; i++)
            if (items[i]->getYear() == year) items[i]->displayInfo();
    }
    // search by author
    void search(string field, string value) {
        cout << "\nSearch by Author: " << value << endl;
        for (int i = 0; i < count; i++) {
            Book* b = dynamic_cast<Book*>(items[i]);
            if (b && b->getAuthor() == value) b->displayInfo();
        }
    }
};

int main() {
    Book b("C++ Primer", "Addison-Wesley", "B001", 2020, "Lippman", "978-0321714114", 976);
    DVD d("Interstellar", "Paramount", "D001", 2014, "Christopher Nolan", 169, "PG-13");
    CD c("Thriller", "Epic", "C001", 1982, "Michael Jackson", 9, "Pop");
    Magazine m("National Geographic", "NatGeo", "M001", 2023, 101, "Science");

    b.displayInfo(); cout << endl;
    d.displayInfo(); cout << endl;
    c.displayInfo(); cout << endl;
    m.displayInfo(); cout << endl;

    b.checkOut();
    b.checkOut();
    b.returnItem();

    Library lib;
    lib.addItem(&b); lib.addItem(&d); lib.addItem(&c); lib.addItem(&m);
    lib.search("C++ Primer");
    lib.search(2014);
    lib.search("author", "Lippman");

    return 0;
}

