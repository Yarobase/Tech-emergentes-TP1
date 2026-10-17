#include <iostream>
#include "book.h"
#include <sstream>

#include "library.h"
#include "user.h"

using namespace std;

Library library;

Book::Book() : title(""), author(""), isbn(""), isAvailable(true), borrowerId("") {}

Book::Book(const string &title, const string &author, const string &isbn)
    : title(title), author(author), isbn(isbn) {}

string Book::getTitle() const {return title;}
string Book::getAuthor() const { return author; }
string Book::getISBN() const { return isbn; }
bool Book::getAvailability() const { return isAvailable; }
string Book::getBorrowerId() const { return borrowerId; }

void Book::setTitle(const string &title) { this->title = title; }
void Book::setAuthor(const string &author) { this->author = author; }
void Book::setISBN(const string &isbn) { this->isbn = isbn; }
void Book::setAvailability(const bool isAvailable) { this->isAvailable = isAvailable; }
void Book::setBorrowerId(const string &borrowerId) { this->borrowerId = borrowerId; }

// MÉTHODES

// Emprunter un livre
void Book::checkOut(const string &borrowerId)
{
    setAvailability(false);
    setBorrowerId(borrowerId);
}

// Retourner un livre
void Book::returnBook()
{
    setAvailability(true);
    setBorrowerId("");
}


// Export format pour le storage fichier
string Book::toFileFormat() const
{
    string available = "0";

    if (isAvailable == true)
    {
        available = "1";
    }

    string book = title + "|" + author + "|" + isbn + "|" + available + "|" + borrowerId;

    return book;
}

// Import les informations d'un livre d'un format fichier
void Book::fromFileFormat(const string &line)
{
    stringstream ss(line);
    string available;

    getline(ss, title, '|');
    getline(ss, author, '|');
    getline(ss, isbn, '|');
    getline(ss, available, '|');
    getline(ss, borrowerId, '|');

    if (available == "0")
    {
        isAvailable = false;
    }
    else
    {
        isAvailable = true;
    }
}

// Information d'un livre
string Book::toString() const
{

    string available = "available";

    if (isAvailable == true)
    {
        available  = "Disponible";
    }

    string book = "Titre: " + title + "\nAuteur: " + author + "\nISBN: " + isbn + "\nDisponibilité: " + available + "\nEmprunté par : " + borrowerId;

    return book;
}

// Information d'un livre avec nom
string Book::toStringName() const
{

    string available = "available";
    User* user = library.findUserById(borrowerId);
    string name;
    if (user != nullptr)
    {
        name = user->getName();
    }
    else
    {
        name = "Utilisateur inconnu";
    }

    if (isAvailable == true)
    {
        available = "Disponible";
    }

    string book = "Titre: " + title + "\nAuteur: " + author + "\nISBN: " + isbn + "\nDisponibilité: " + available + "\nEmprunté par : " + name;

    return book;
}