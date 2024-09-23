#pragma once
#include "Garbage.h"
#include "Queue.h"
#include "BST.h"
#include "Hash.h"
#include "Stack.h"
#include <fstream>
#include <sstream>

// Helper function to append one string to the end of another
void addToEnd(char* beg, char* end) {
	int i;                        // Integer for indexing
	for (i = 0; beg[i]; i++);      // Move i to the end of the first string (beg)
	beg[i++] = ',';					//This function gets called when a comma splits titles, so 
	for (int j = 0; end[j]; i++, j++) { // Copy the second string (end) to the first string (beg)
		beg[i] = end[j];
	}
	beg[i] = 0;						// Add null to the end of the string to finish output
}

// Library Management System (LMS) class definition
class LMS {
private:
	AVL byTitle;                  // AVL tree to store books by title
	hashTable byISBN;             // Hash table to store books by ISBN
	stack borrowed;               // Stack to track borrowed books
	garbage deleteWhenDone;       // Garbage collection to handle book deletions

public:
	LMS();                        // Constructor to initialize the LMS system
	~LMS();                       // Destructor to clean up the LMS system
	void interface();             // Method to handle user interface for borrowing/returning books
};

// Constructor for the Library Management System (LMS)
LMS::LMS() : byISBN(100) {        // Initialize the AVL tree, hash table, and other structures
	ifstream file("Book Dataset.csv"); // Open the book dataset file

	if (!file.is_open()) {         // If the file failed to open, display an error message
		cerr << "Failed to open file" << endl;
		return;
	}

	char line[150];                // Buffer to store each line from the file
	bookInfo* v;                   // Pointer to store book information
	char num[10];                  // Buffer to store numbers as strings
	while (file.getline(line, 1500) && line[0] != ',') { // Read each line of the CSV file
		v = new bookInfo;          // Dynamically allocate memory for a new book

		stringstream ss(line);     // Create a stringstream from the line

		ss.getline(num, 10, ',');  // Get the ISBN from the string
		if (num[0] >= '0' && num[0] <= '9') { // Check if the ISBN is valid
			v->ISBN = stoi(num);   // Convert the string to an integer (ISBN)

			v->title = new char[110]; // Allocate memory for the title
			ss.getline(v->title, 110, ','); // Get the title from the string

			v->author = new char[60]; // Allocate memory for the author
			ss.getline(v->author, 60, ','); // Get the author from the string
			while (v->author[0] == ' ') { // Author's names don't start with ' '; this was a part of the title!
				addToEnd(v->title, v->author); // Append it to the title
				ss.getline(v->author, 60, ','); // Get the next part of the author name
			}

			ss.getline(num, 10, ','); // Get the price as a string
			v->price = stod(num);    // Convert the price string to a double

			ss.getline(num, 10, ','); // Get the quantity as a string
			v->quantity = stoi(num);  // Convert the quantity string to an integer

			deleteWhenDone.add(v);   // Add the book to the garbage collector
			byTitle.insert(v);       // Insert the book into the AVL tree (by title)
			byISBN.insert(v);        // Insert the book into the hash table (by ISBN)
		}
		else delete v;               // If ISBN is invalid, delete the book object
	}
}

// Destructor for the LMS system
LMS::~LMS() {
	deleteWhenDone.~garbage();     // Clean up the garbage collector
	// Note: AVL and hashTable destructors are called automatically
}

// Method to handle the user interface for borrowing/returning books
void LMS::interface() {
	char* title = new char[50];    // Dynamically allocate memory for the book title
	int ISBN;                      // Integer to store the book ISBN
	bookInfo* toReserve;           // Pointer to store the reserved book
	char choice;                   // Character for the user's choice
	char* name = new char[20];     // Dynamically allocate memory for the user's name

	cout << "Enter your username, email address, or name: ";	//Prompt for input
	cin.getline(name, 20);         // Get the user's name

	cout << "Would you like to a) borrow a book, b) return a book, c) or quit? <a/b/c>: ";	//Prompt for input
	cin >> choice;	//Input the user's choice
	cin.ignore(); // Flush the newline after 'choice' input

	while (choice == 'a' || choice == 'b') {	//While the user is borrowing or returning
		if (choice == 'a') {	//If they are borrowing
			cout << "Query by: a) Title b) ISBN <a/b>: ";	//Prompt for querry type
			cin >> choice;	//Input choice
			cin.ignore(); // Flush newline after choice input

			if (choice == 'a') {	//If they search by title
				cout << "What is the title? ";	//Prompt for title
				cin.getline(title, 50); // Read the title
				cout << "Performing Binary Search ..." << endl;	//Alert the user
				toReserve = byTitle.retrieve(title);	//Search for & store book information
			}
			else {	//If they search by ISBN
				cout << "What is the ISBN? ";	//Prompt for ISBN
				cin >> ISBN;	//Read the ISBN
				cout << "Performing hash on ISBN ..." << endl;	//Alert the user
				toReserve = byISBN.get(ISBN);	//Search for & store book information
				cin.ignore(); // Flush newline after ISBN input
			}

			if (toReserve) {	//If the book is found
				if (toReserve->quantity != 0) {	//If the book is in stock
					borrowed.push(toReserve);	//Borrow the book
					toReserve->quantity--;	//Decrease the number of available copies
					cout << "Successfully reserved. We have " << toReserve->quantity	//Alert the user
						<< " copies of " << toReserve->title << " left." << endl;
				}
				else {	//If the book is out of stock
					cout << "All copies of " << toReserve->title << " taken." << endl;	//Alert the user
					toReserve->reservations.enqueue(name);	//Queue the user's reservation
					cout << "You have reserved this book. There are " << toReserve->reservations.length() - 1	//Alert the user
						<< " reservations in front of you." << endl;
					cout << "The current list of people who have reserved this book is: ";	//Display the current reservations
					toReserve->reservations.displayAll();
				}
			}
			else {	//If the book is not found
				cout << "Could not find book. Try again." << endl;	//Alert the user
			}
		}
		else {	//If returning a book
			if (!borrowed.peep()) {	//If they haven't borrowed a book
				cout << "No books borrowed." << endl;	//Alert the user
			}
			else {	//Otherwise
				cout << "Returning " << borrowed.peep()->title << endl;	//Alert the user of return
				borrowed.peep()->quantity++;	//Increase the number of available copies

				while (!borrowed.peep()->reservations.isEmpty() && borrowed.peep()->quantity > 0) {	//While there is a reservation & an available copy
					if (strcmp(borrowed.peep()->reservations.dequeue(), name) == 0) {	//If the current user borrowed it
						cout << "Your reservation for " << borrowed.peep()->title	//Ask if they want the book
							<< " is available. Would you like to a) retrieve or b) forfeit? <a/b>: ";
						cin >> choice;	//Input choice
						cin.ignore(); // Flush newline after choice input
						if (choice == 'a') {	//If they want it
							borrowed.peep()->quantity--;	//Decrease available copies
							borrowed.push(borrowed.pop());	//Borrow book (Note: this will actually be returned in a line & they will keep their previous copy)
						}
					}
				}
				borrowed.pop(); // Remove the returned book from the borrowed stack
			}
		}

		cout << "Would you like to a) borrow a book, b) return a book, c) or quit? <a/b/c>: ";	//Prompt again
		cin >> choice;	//Input choice
		cin.ignore(); // Flush newline after choice input
	}

	delete[] name;  // Free dynamically allocated memory
	delete[] title; // Free dynamically allocated memory
}
