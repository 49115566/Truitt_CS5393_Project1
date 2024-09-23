#pragma once
#include "bookInfo.h"

// Node structure for a garbage collection linked list
struct gNode {
	bookInfo* val;                // Pointer to the book information stored in the node
	gNode* next;                  // Pointer to the next node in the garbage list
};

// Class definition for a garbage collection list
class garbage {
private:
	gNode* head;                  // Pointer to the head of the garbage list

public:
	garbage();                    // Constructor to initialize the garbage list
	~garbage();                   // Destructor to clean up the garbage list
	void add(bookInfo* v);         // Method to add a book to the garbage list
};

// Constructor for the garbage list
garbage::garbage() {
	head = nullptr;                // Initialize the head of the garbage list as null (empty list)
}

// Destructor to clean up the garbage list
garbage::~garbage() {
	gNode* temp;                   // Temporary pointer for deletion
	while (head) {                 // While there are nodes in the garbage list
		temp = head->next;         // Move temp to the next node
		// Free dynamically allocated memory for the book info
		if (head->val->author) delete[] head->val->author; // Free the dynamically allocated author string
		if (head->val->title) delete[] head->val->title;   // Free the dynamically allocated title string
		delete head->val;          // Delete the bookInfo object
		delete head;               // Delete the current node
		head = temp;               // Move head to the next node
	}
}

// Method to add a book to the garbage collection list
void garbage::add(bookInfo* v) {
	gNode* newNode = new gNode;    // Dynamically allocate a new gNode
	newNode->val = v;              // Set the value of the node to the bookInfo
	newNode->next = head;          // Link the new node to the current head
	head = newNode;                // Update the head to the new node
}
