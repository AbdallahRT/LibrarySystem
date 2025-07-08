#include <bits/stdc++.h>
using namespace std;

class Book {
public:
    string name;
    int id;
    int count;

    Book(string name, int id, int count)
        : name(name), id(id), count(count) {}
};

class Library {
private:
    vector<Book> books;
    map<string, int> availableCopies;
    map<string, vector<string>> borrowedByUser;

public:
    void addBook() {
        cout << "Enter book name, id, and count: ";
        string name;
        int id, count;
        cin >> name >> id >> count;

        books.emplace_back(name, id, count);
        availableCopies[name] += count;

        cout << "Book added successfully.\n";
    }

    void searchByPrefix() {
        cout << "Enter book name prefix: ";
        string prefix;
        cin >> prefix;
        bool found = false;

        for (auto &book : books) {
            if (book.name.substr(0, prefix.size()) == prefix) {
                cout << book.name << "\n";
                found = true;
            }
        }

        if (!found)
            cout << "No books found with this prefix.\n";
    }

    void borrowBook() {
        cout << "Enter user name and book name: ";
        string user, bookName;
        cin >> user >> bookName;

        if (availableCopies[bookName] > 0) {
            borrowedByUser[bookName].push_back(user);
            availableCopies[bookName]--;
            cout << "Book borrowed successfully.\n";
        } else {
            cout << "Book not available.\n";
        }
    }

    void returnBook() {
        cout << "Enter user name and book name: ";
        string user, bookName;
        cin >> user >> bookName;

        auto &users = borrowedByUser[bookName];
        auto it = find(users.begin(), users.end(), user);
        if (it != users.end()) {
            users.erase(it);
            availableCopies[bookName]++;
            cout << "Book returned successfully.\n";
        } else {
            cout << "This user did not borrow this book.\n";
        }
    }

    void printWhoBorrowed() {
        cout << "Enter book name: ";
        string name;
        cin >> name;

        if (!borrowedByUser.count(name)) {
            cout << "No one has borrowed this book.\n";
            return;
        }

        cout << name << " borrowed by:\n";
        for (const auto &user : borrowedByUser[name]) {
            cout << user << "\n";
        }
    }

    void printAllBooksById() {
        vector<Book> sorted = books;
        sort(sorted.begin(), sorted.end(), [](Book &a, Book &b) {
            return a.id < b.id;
        });

        for (auto &book : sorted)
            cout << book.id << " " << book.name << " " << book.count << "\n";
    }

    void printAllBooksByName() {
        vector<Book> sorted = books;
        sort(sorted.begin(), sorted.end(), [](Book &a, Book &b) {
            return a.name < b.name;
        });

        for (auto &book : sorted)
            cout << book.name << " " << book.id << " " << book.count << "\n";
    }

    void printAllUsers() {
        for (auto &[book, users] : borrowedByUser) {
            cout << "Book: " << book << " borrowed by: ";
            for (auto &user : users)
                cout << user << " ";
            cout << "\n";
        }
    }
};

int main() {
    Library lib;

    while (true) {
        cout << "\nLibrary Menu:\n";
        cout << "1) Add Book\n";
        cout << "2) Search by Prefix\n";
        cout << "3) Borrow Book\n";
        cout << "4) Return Book\n";
        cout << "5) Print Who Borrowed a Book\n";
        cout << "6) Print Books by ID\n";
        cout << "7) Print Books by Name\n";
        cout << "8) Print All Users\n";
        cout << "9) Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.searchByPrefix(); break;
            case 3: lib.borrowBook(); break;
            case 4: lib.returnBook(); break;
            case 5: lib.printWhoBorrowed(); break;
            case 6: lib.printAllBooksById(); break;
            case 7: lib.printAllBooksByName(); break;
            case 8: lib.printAllUsers(); break;
            case 9: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid option.\n";
        }
    }
}
