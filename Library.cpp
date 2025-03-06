#include <iostream>
#include <string>
#include<stack>
#include<queue>
using namespace std;

const int MAX_BOOKS = 100;
const int MAX_REQUESTS = 100;
const int MAX_RETURNS = 100;

class Book {
public:
    string title;
    string author;
    bool isRequested;

    Book(string t = "", string a = "") {
        title = t;
        author = a;
        isRequested = false;
    }
};

class BookRequestQueue {
private:
    Book requestedBooks[MAX_REQUESTS];
    int front, rear;

public:
    BookRequestQueue() { front = rear = -1; }

    void enqueue(Book book) {
        if (rear >= MAX_REQUESTS - 1) {
            cout << "Queue overflow! Cannot add more book requests.\n";
            return;
        }
        if (front == -1) front = 0;
        requestedBooks[++rear] = book;
    }

    Book dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue underflow! No book requests to process.\n";
            return Book();
        }
        return requestedBooks[front++];
    }

    bool isEmpty() { return front == -1 || front > rear; }

    Book pop() {
        if (rear < 0) {
            cout << "Stack underflow! No returned books to process.\n";
            return Book();
        }
        return requestedBooks[rear--];
    }
    void display() {
        if (isEmpty()) {
            cout << "No requested books.\n";
            return;
        }
        cout << "Requested Books:\n";
        for (int i = front; i <= rear; i++) {
            cout << "- " << requestedBooks[i].title << " by " << requestedBooks[i].author << "\n";
        }
    }
};

class ReturnedBookStack {
private:
    Book returnedBooks[MAX_RETURNS];
    int top;

public:
    ReturnedBookStack() { top = -1; }

    void push(Book book) {
        if (top >= MAX_RETURNS - 1) {
            cout << "Stack overflow! Cannot add more returned books.\n";
            return;
        }
        returnedBooks[++top] = book;
    }

    Book pop() {
        if (top < 0) {
            cout << "Stack underflow! No returned books to process.\n";
            return Book();
        }
        return returnedBooks[top--];
    }

    bool isEmpty() { return top < 0; }

    void display() {
        if (isEmpty()) {
            cout << "No returned books.\n";
            return;
        }
        cout << "Returned Books:\n";
        for (int i = top; i >= 0; i--) {
            cout << "- " << returnedBooks[i].title << " by " << returnedBooks[i].author << "\n";
        }
    }
};

class Library {
private:
    Book books[MAX_BOOKS];
    int bookCount;
    BookRequestQueue requestedBooks;
    ReturnedBookStack returnedBooks;

public:
    Library() { bookCount = 0; }

    void addBook(string title, string author) {
        if (bookCount >= MAX_BOOKS) {
            cout << "Library is full! Cannot add more books.\n";
            return;
        }
        books[bookCount++] = Book(title, author);
        cout << "Book added: " << title << " by " << author << "\n";
    }

    void requestBook(string title) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].title == title && !books[i].isRequested) {
                books[i].isRequested = true;
                requestedBooks.enqueue(books[i]);
                cout << "Book requested: " << title << "\n";
                return;
            }
        }
        cout << "Book not found or already requested.\n";
    }

    void returnBook() {
        if (requestedBooks.isEmpty()) {
            cout << "No books to return.\n";
            return;
        }
        Book book = requestedBooks.pop(); 

        for (int i = 0; i < bookCount; i++) {
            if (books[i].title == book.title && books[i].author == book.author) {
                books[i].isRequested = false; 
                break;
            }
        }

        returnedBooks.push(book);
        cout << "Book returned: " << book.title << " by " << book.author << "\n";
    }

    void displayAllBooks() {
        if (bookCount == 0) {
            cout << "No books available in the library.\n";
            return;
        }
        cout << "All Books in the Library:\n";
        for (int i = 0; i < bookCount; i++) {
            cout << "- " << books[i].title << " by " << books[i].author;
            if (books[i].isRequested) {
                cout << " (Requested)";
            }
            cout << "\n";
        }
    }

    void displayRequestedBooks() {
        requestedBooks.display();
    }

    void displayReturnedBooks() {
        returnedBooks.display();
    }

    void autoRequestBook() {
        if (bookCount == 0) {
            cout << "No books available to request.\n";
            return;
        }
        for (int i = 0; i < bookCount; i++) {
            if (!books[i].isRequested) {
                requestBook(books[i].title);
                return;
            }
        }
        cout << "All books are already requested.\n";
    }

    void autoReturnBook() {
        returnBook();
    }
};

int main() {
    Library library;

    while (true) {
        cout << "\nLibrary Book Management System:\n";
        cout << "1. Add a book\n";
        cout << "2. Request a book\n";
        cout << "3. Return a book\n";
        cout << "4. Display all books\n";
        cout << "5. Display requested books\n";
        cout << "6. Display returned books\n";
        cout << "7. Auto-request a book\n";
        cout << "8. Auto-return a book\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();  
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        cin.ignore();
        if (choice == 1) {
            string title, author;
            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            library.addBook(title, author);
        }
        else if (choice == 2) {
            string title;
            cout << "Enter book title: ";
            getline(cin, title);
            library.requestBook(title);
        }
        else if (choice == 3) {
            library.returnBook();
        }
        else if (choice == 4) {
            library.displayAllBooks();
        }
        else if (choice == 5) {
            library.displayRequestedBooks();
        }
        else if (choice == 6) {
            library.displayReturnedBooks();
        }
        else if (choice == 7) {
            library.autoRequestBook();
        }
        else if (choice == 8) {
            library.autoReturnBook();
        }
        else if (choice == 9) {
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
