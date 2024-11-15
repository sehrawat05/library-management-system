#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book {
private:
    int bookID;
    string title;
    string author;
    bool isIssued;

public:
    Book(int id, string t, string a) : bookID(id), title(t), author(a), isIssued(false) {}

    int getBookID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsIssued() const { return isIssued; }

    void issueBook() {
        if (!isIssued) {
            isIssued = true;
            cout << "Book issued successfully!" << endl;
        } else {
            cout << "Book is already issued!" << endl;
        }
    }

    void returnBook() {
        if (isIssued) {
            isIssued = false;
            cout << "Book returned successfully!" << endl;
        } else {
            cout << "Book was not issued!" << endl;
        }
    }

    void displayBook() const {
        cout << "Book ID: " << bookID << ", Title: " << title << ", Author: " << author
             << ", Status: " << (isIssued ? "Issued" : "Available") << endl;
    }
};

class Student {
private:
    int studentID;
    string name;
    int issuedBookID;

public:
    Student(int id, string n) : studentID(id), name(n), issuedBookID(-1) {}

    int getStudentID() const { return studentID; }
    string getName() const { return name; }
    int getIssuedBookID() const { return issuedBookID; }

    void issueBook(int bookID) {
        if (issuedBookID == -1) {
            issuedBookID = bookID;
            cout << "Book issued to " << name << endl;
        } else {
            cout << name << " already has a book issued!" << endl;
        }
    }

    void returnBook() {
        if (issuedBookID != -1) {
            issuedBookID = -1;
            cout << name << " returned the book." << endl;
        } else {
            cout << name << " has no book to return!" << endl;
        }
    }

    void displayStudent() const {
        cout << "Student ID: " << studentID << ", Name: " << name
             << ", Issued Book ID: " << (issuedBookID == -1 ? "None" : to_string(issuedBookID)) << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<Student> students;

public:
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Book added to the library." << endl;
    }

    void registerStudent(const Student& student) {
        students.push_back(student);
        cout << "Student registered in the library." << endl;
    }

    void issueBook(int studentID, int bookID) {
        for (auto& book : books) {
            if (book.getBookID() == bookID) {
                for (auto& student : students) {
                    if (student.getStudentID() == studentID) {
                        if (!book.getIsIssued() && student.getIssuedBookID() == -1) {
                            book.issueBook();
                            student.issueBook(bookID);
                        } else {
                            cout << "Book or student issue status not eligible." << endl;
                        }
                        return;
                    }
                }
                cout << "Student not found!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    void returnBook(int studentID, int bookID) {
        for (auto& book : books) {
            if (book.getBookID() == bookID && book.getIsIssued()) {
                for (auto& student : students) {
                    if (student.getStudentID() == studentID && student.getIssuedBookID() == bookID) {
                        book.returnBook();
                        student.returnBook();
                        return;
                    }
                }
                cout << "Student/book mismatch!" << endl;
                return;
            }
        }
        cout << "Book not found or not issued!" << endl;
    }

    void displayBooks() const {
        cout << "Library Books:" << endl;
        for (const auto& book : books) {
            book.displayBook();
        }
    }

    void displayStudents() const {
        cout << "Library Students:" << endl;
        for (const auto& student : students) {
            student.displayStudent();
        }
    }
};

int main() {
    Library lib;

    lib.addBook(Book(1, "The Great Gatsby", "F. Scott Fitzgerald"));
    lib.addBook(Book(2, "1984", "George Orwell"));
    lib.addBook(Book(3, "To Kill a Mockingbird", "Harper Lee"));

    lib.registerStudent(Student(101, "Alice"));
    lib.registerStudent(Student(102, "Bob"));

    lib.displayBooks();
    lib.displayStudents();

    lib.issueBook(101, 1);
    lib.issueBook(102, 2);

    lib.displayBooks();
    lib.displayStudents();

    lib.returnBook(101, 1);
    lib.displayBooks();
    lib.displayStudents();

    return 0;
}

