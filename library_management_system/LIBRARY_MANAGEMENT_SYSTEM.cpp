#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure for a book
struct Book {
    int bookId;
    string title;
    string author;
    int availableCopies;
};

// Structure for a library member
struct Member {
    int memberId;
    string name;
};

// Structure for book history
struct BookHistory {
    int bookId;
    int issuesCount;
};

// Function prototypes
void addBook(vector<Book> &books);
void addMember(vector<Member> &members);
void bubbleSortBooks(vector<Book> &books);
void printBooks(const vector<Book> &books);
void countBookHistory(const vector<Book> &books, const vector<BookHistory> &history);
void issueBook(vector<Book> &books, vector<BookHistory> &history);
void returnBook(vector<Book> &books, vector<BookHistory> &history);
void countingSortByAuthorLength(vector<Book> &arr);

// Counting sort function to sort books by author name length
void countingSortByAuthorLength(vector<Book>& arr) {
    int maxLen = 0;
    for (const auto& book : arr) {
        int len = book.author.length();
        if (len > maxLen) {
            maxLen = len;
        }
    }

    vector<Book> output(arr.size());
    vector<int> count(maxLen + 1, 0);

    for (const auto& book : arr) {
        count[book.author.length()]++;
    }

    for (int i = 1; i <= maxLen; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[arr[i].author.length()] - 1] = arr[i];
        count[arr[i].author.length()]--;
    }

    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = output[i];
    }
}

// Main function
int main() {
    vector<Book> books;
    vector<Member> members;
    vector<BookHistory> bookHistory;

    while (true) {
        cout << "\nLibrary Management System Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Total book history\n";
        cout << "4. Count Book Issue History\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Sort Books by Author Name Length\n";
        cout << "8. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(books);
                break;

            case 2:
                addMember(members);
                break;

            case 3:
                bubbleSortBooks(books);
                printBooks(books);
                break;

            case 4:
                countBookHistory(books, bookHistory);
                break;

            case 5:
                issueBook(books, bookHistory);
                break;

            case 6:
                returnBook(books, bookHistory);
                break;

            case 7:
                countingSortByAuthorLength(books);
                cout << "Books sorted by author name length.\n";
                printBooks(books);
                break;

            case 8:
                cout << "Exiting Library Management System.\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}

// Function to add a book to the library
void addBook(vector<Book> &books) {
    Book newBook;
    cout << "Enter Book ID: ";
    cin >> newBook.bookId;
    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter Author: ";
    getline(cin, newBook.author);
    cout << "Enter Number of Copies: ";
    cin >> newBook.availableCopies;

    books.push_back(newBook);
    cout << "Book added successfully!\n";
}

// Function to add a library member
void addMember(vector<Member> &members) {
    Member newMember;
    cout << "Enter Member ID: ";
    cin >> newMember.memberId;
    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, newMember.name);

    members.push_back(newMember);
    cout << "Member added successfully!\n";
}

// Bubble Sort for sorting books based on bookId
void bubbleSortBooks(vector<Book> &books) {
    int n = books.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (books[j].bookId > books[j + 1].bookId) {
                swap(books[j], books[j + 1]);
            }
        }
    }
}

// Function to print all books
void printBooks(const vector<Book> &books) {
    cout << "\nBooks:\n";
    for (const auto &book : books) {
        cout << "Book ID: " << book.bookId << ", Title: " << book.title << ", Author: " << book.author << ", Available Copies: " << book.availableCopies << endl;
    }
}

// Function to count book history
void countBookHistory(const vector<Book> &books, const vector<BookHistory> &history) {
    cout << "\nBook History:\n";
    for (const auto &book : books) {
        int count = 0;
        for (const auto &issue : history) {
            if (issue.bookId == book.bookId) {
                count += issue.issuesCount;
            }
        }
        cout << "Book ID: " << book.bookId << ", Title: " << book.title << ", Total Issues: " << count << endl;
    }
}
// Function to issue a book
void issueBook(vector<Book> &books, vector<BookHistory> &history) {
    int bookId;
    cout << "Enter Book ID to Issue: ";
    cin >> bookId;
    for (auto &book : books) {
        if (book.bookId == bookId) {
            if (book.availableCopies > 0) {
                book.availableCopies--;
                // Update book history
                bool found = false;
                for (auto &issue : history) {
                    if (issue.bookId == bookId) {
                        issue.issuesCount++;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    BookHistory newHistory = {bookId, 1};
                    history.push_back(newHistory);
                }
                cout << "Book issued successfully!\n";
            } else {
                cout << "No available copies of the book.\n";
            }
            return;
        }
    }
    cout << "Book not found.\n";
}

// Function to return a book
void returnBook(vector<Book> &books, vector<BookHistory> &history) {
    int bookId;
    cout << "Enter Book ID to Return: ";
    cin >> bookId;
    for (auto &book : books) {
        if (book.bookId == bookId) {
            book.availableCopies++;
            // Update book history
            for (auto &issue : history) {
                if (issue.bookId == bookId && issue.issuesCount > 0) {
                    issue.issuesCount--;
                    cout << "Book returned successfully!\n";
                    return;
                }
            }
            cout << "No history of this book being issued.\n";
            return;
        }
    }
    cout << "Book not found.\n";
}
