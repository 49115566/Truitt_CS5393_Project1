#pragma once
#include "Queue.h"

// Structure for book information
struct bookInfo {
	int ISBN;                       // Integer representing the book's ISBN
	char* title;                    // Character pointer for the book title
	char* author;                   // Character pointer for the book author
	double price;                   // Double for the price of the book
	int quantity;                   // Integer for the quantity of the book
	Q reservations;                 // Queue for reservation requests

	bookInfo() {                    // Default constructor
		ISBN = -1;                  // Set default ISBN to -1
		title = nullptr;            // Set default title to null
		author = nullptr;           // Set default author to null
		price = -1;                 // Set default price to -1
		quantity = 0;               // Set default quantity to 0
	}

	void print() {                  // Method to print book information
		cout << "ISBN:\t" << ISBN << endl;      // Print ISBN
		if (title) cout << "Title:\t" << title << endl; // Print title if it exists
		if (author) cout << "Author:\t" << author << endl; // Print author if it exists
		cout << "Price:\t" << price << endl;    // Print price
		cout << "Quantity:\t" << quantity << endl << endl; // Print quantity
	}
};
