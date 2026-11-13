#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

const size_t MAX_BOOKS = 500;

struct Book {
    string title;
    string author;
    double price;
    int copies;
};

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return s;
}

void clearInput() {
    if (cin.eof()) {
        cout << "\nInput closed. Exiting.\n";
        exit(0);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& prompt, int minValue) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a whole number >= " << minValue << ".\n";
        clearInput();
    }
}

double readPrice(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0.0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Price must be a number >= 0.\n";
        clearInput();
    }
}

string readText(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) {
            clearInput();  // exits on EOF
            continue;
        }
        if (!line.empty()) return line;
        cout << "This field cannot be empty.\n";
    }
}

void printBook(const Book& b) {
    cout << "Title : " << b.title << "\n"
         << "Author: " << b.author << "\n"
         << "Price : " << fixed << setprecision(2) << b.price << " TK\n"
         << "Copies: " << b.copies << "\n";
}


void displayMenu() {
    cout << "\n**********************\n"
         << "Welcome to Our Book Shop\n"
         << "**********************\n\n"
         << "Please select a menu option number:\n"
         << "1) Menu.\n"
         << "2) Available books.\n"
         << "3) Add a book.\n"
         << "4) Search a book by title.\n"
         << "5) Total number of books.\n"
         << "6) Exit.\n\n";
}

void addBook(vector<Book>& books) {
    if (books.size() >= MAX_BOOKS) {
        cout << "Cannot add more books. Maximum limit reached.\n";
        return;
    }

    Book b;
    b.title = readText("Enter Book Title: ");
    b.author = readText("Enter Author Name: ");
    b.price = readPrice("Enter Book Price: ");
    b.copies = readInt("Enter Number of Copies: ", 0);

    books.push_back(b);
    cout << "Book added successfully!\n";
}

void displayBooks(const vector<Book>& books) {
    if (books.empty()) {
        cout << "No books found.\n";
        return;
    }

    cout << "\nBook List:\n";
    for (size_t i = 0; i < books.size(); i++) {
        cout << "Book " << i + 1 << ":\n";
        printBook(books[i]);
        cout << "-------------------\n";
    }
}

void searchBook(const vector<Book>& books) {
    if (books.empty()) {
        cout << "No books found.\n";
        return;
    }

    string query = toLower(readText("Enter book title to search: "));
    bool found = false;

    for (const Book& b : books) {
        if (toLower(b.title).find(query) != string::npos) {
            if (!found) cout << "\nBook(s) Found:\n";
            printBook(b);
            cout << "-------------------\n";
            found = true;
        }
    }

    if (!found) cout << "Book not found.\n";
}

int main() {
    vector<Book> books;
    int choice;

    do {
        displayMenu();
        choice = readInt("Enter your choice: ", 1);

        switch (choice) {
            case 1:
                break;
            case 2:
                displayBooks(books);
                break;
            case 3:
                addBook(books);
                break;
            case 4:
                searchBook(books);
                break;
            case 5:
                cout << "Total number of books: " << books.size() << "\n";
                break;
            case 6:
                cout << "Thank You\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
