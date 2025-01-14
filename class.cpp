#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

// allows lowercase letters
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// The Book class
class Book {
public:
    std::string author{};
    std::string category{};
    std::string name{};

    void print() const {
        std::cout << "Book: " << author << " / " << category << " / " << name << '\n';
    }

    std::string toFileString() const {
        return author + ";" + category + ";" + name;
    }

    static Book fromFileString(const std::string& line) {
        std::stringstream ss(line);
        Book book;
        std::getline(ss, book.author, ';');
        std::getline(ss, book.category, ';');
        std::getline(ss, book.name, ';');
        return book;
    }
};

// Load books from a file
void loadBooksFromFile(const std::string& filename, std::vector<Book>& books) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << '\n';
        return;
    }

    books.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            books.push_back(Book::fromFileString(line));
        }
    }

    file.close();
}

// Save books to a file
void saveBooksToFile(const std::string& filename, const std::vector<Book>& books) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << '\n';
        return;
    }

    for (const auto& book : books) {
        file << book.toFileString() << '\n';
    }

    file.close();
}

// Class for the users
class User {
public:
    int id{};
    std::string name{};
    std::string role{}; // "Student", "Teacher", or "Librarian"

    void input() {
        std::cout << "Enter User ID: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Enter User Name: ";
        std::getline(std::cin, name);
        std::cout << "Enter Role (Student/Teacher/Librarian): ";
        std::getline(std::cin, role);
    }

    void print() const {
        std::cout << "User: ID = " << id << ", Name = " << name << ", Role = " << role << '\n';
    }

    bool isTeacher() const {
        return toLower(role) == "teacher";
    }

    bool isStudent() const {
        return toLower(role) == "student";
    }

    bool isLibrarian() const {
        return toLower(role) == "librarian";
    }
};

// The Librarian class
class Librarian : public User {
public:
    int librarianId{};
};

// Display books
void displayBooks(const std::vector<Book>& books) {
    std::cout << "\nBook List:\n";
    if (books.empty()) {
        std::cout << "No books available.\n";
    }
    else {
        int index = 1;
        for (const auto& book : books) {
            std::cout << index++ << ". ";
            book.print();
        }
    }
}

// Allow the student to choose a book
void chooseBook(const std::vector<Book>& books) {
    if (books.empty()) {
        std::cout << "No books available to choose from.\n";
        return;
    }

    displayBooks(books);

    int choice;
    std::cout << "Enter the number of the book you want to choose (1 to " << books.size() << "): ";
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(books.size())) {
        std::cout << "Invalid selection.\n";
    }
    else {
        std::cout << "You have chosen:\n";
        books[choice - 1].print();
    }
}

// allows librarian or teacher to add a book
void addBook(std::vector<Book>& books, const std::string& filename) {
    Book newBook;
    std::cin.ignore();
    std::cout << "Enter author name: ";
    std::getline(std::cin, newBook.author);
    std::cout << "Enter category: ";
    std::getline(std::cin, newBook.category);
    std::cout << "Enter book name: ";
    std::getline(std::cin, newBook.name);

    books.push_back(newBook);
    saveBooksToFile(filename, books);
    std::cout << "Book added successfully.\n";
}

// allows librarian or teacher to remove a current book
void removeBook(std::vector<Book>& books, const std::string& filename) {
    if (books.empty()) {
        std::cout << "No books to remove.\n";
        return;
    }

    displayBooks(books);
    int index;
    std::cout << "Enter the number of the book to remove (1 to " << books.size() << "): ";
    std::cin >> index;

    if (index < 1 || index > static_cast<int>(books.size())) {
        std::cout << "Invalid selection.\n";
    }
    else {
        books.erase(books.begin() + (index - 1));
        saveBooksToFile(filename, books);
        std::cout << "Book removed successfully.\n";
    }
}

int main() 
{
    // File to store books
    const std::string filename = "books.txt";

    // List of all the books
    std::vector<Book> books;
    loadBooksFromFile(filename, books);

    // Allow the user input
    User user;
    std::cout << "Enter user details:\n";
    user.input();

    if (user.isTeacher() || user.isLibrarian()) {
        int choice;
        do {
            std::cout << (user.isTeacher() ? "\nTeacher Menu:\n" : "\nLibrarian Menu:\n");
            std::cout << "1. Display Books\n";
            std::cout << "2. Add a Book\n";
            std::cout << "3. Remove a Book\n";
            std::cout << "4. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                displayBooks(books);
                break;
            case 2:
                addBook(books, filename);
                break;
            case 3:
                removeBook(books, filename);
                break;
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid input. Please try again.\n";
            }
        } while (choice != 4);
    }
    else if (user.isStudent()) {
        int choice;
        do {
            std::cout << "\nStudent Menu:\n";
            std::cout << "1. Display Books\n";
            std::cout << "2. Choose a Book\n";
            std::cout << "3. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                displayBooks(books);
                break;
            case 2:
                chooseBook(books);
                break;
            case 3:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid input. Please try again.\n";
            }
        } while (choice != 3);
    }
    else {
        std::cout << "Invalid role. Only Students, Teachers, or Librarians are allowed.\n";
    }

    return 0;
}

