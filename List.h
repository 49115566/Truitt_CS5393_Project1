#pragma once
#include "bookInfo.h"

// Node structure for a sorted linked list
struct lNode {
	lNode* next;                    // Pointer to the next node
	bookInfo* val;                  // Pointer to the value (book information)

	lNode(bookInfo* v) : val(v), next(nullptr) {} // Constructor to initialize node
};

// Class definition for a sorted list (by ISBN)
class sortedList {
private:
	lNode* head;                    // Pointer to the head of the list

public:
	sortedList();                   // Constructor
	~sortedList();                  // Destructor
	void insert(bookInfo* v);        // Method to insert book information
	bookInfo* get(int ISBN);         // Method to retrieve a book by ISBN
	void remove(int ISBN);           // Method to remove a book by ISBN
};

// Constructor definition for the sorted list
sortedList::sortedList() {
	head = nullptr;                 // Initialize the head to null
}

// Destructor to clean up memory for the sorted list
sortedList::~sortedList() {
	lNode* temp;                    // Temporary pointer for deletion
	while (head) {                  // While the list is not empty
		temp = head->next;          // Move temp to the next node
		delete head;                // Delete the current head
		head = temp;                // Move head to the next node
	}
}

// Insert method to add a book into the sorted list
void sortedList::insert(bookInfo* v) {
	lNode* newNode = new lNode(v);  // Dynamically allocate a new lNode

	if (!head || head->val->ISBN > v->ISBN) {  // If the list is empty or the new book should be the first
		newNode->next = head;       // Set the new node's next to the current head
		head = newNode;             // Update the head to the new node
	}
	else {                         // Otherwise, find the correct position for insertion
		lNode* current = head;      // Start from the head
		lNode* next = head->next;   // Get the next node
		while (next && next->val->ISBN < v->ISBN) { // Traverse the list until the correct spot
			current = next;         // Move current to the next node
			next = current->next;   // Move next forward
		}
		current->next = newNode;    // Insert the new node at the correct position
		newNode->next = next;       // Link the new node to the rest of the list
	}
}

// Method to retrieve a book by its ISBN
bookInfo* sortedList::get(int ISBN) {
	lNode* current = head;          // Start from the head of the list
	while (current && current->val->ISBN < ISBN) current = current->next; // Traverse the list
	if (!current) return nullptr;   // If no book is found, return null
	if (current->val->ISBN != ISBN) return nullptr; // If ISBN doesn't match, return null
	return current->val;            // Return the book info if found
}

// Method to remove a book by its ISBN
void sortedList::remove(int ISBN) {
	if (head && head->val->ISBN <= ISBN) { // If the list is not empty and the head's ISBN is valid
		lNode* prev = head;         // Previous node pointer starts at the head
		lNode* current = head->next; // Current node pointer starts at the next node
		while (current && current->val->ISBN < ISBN) { // Traverse the list
			prev = current;         // Move prev to the next node
			current = prev->next;   // Move current forward
		}
		if (current && current->val->ISBN == ISBN) { // If the book is found
			current = current->next; // Move current to the next node
			delete prev->next;       // Delete the current node
			prev->next = current->next; // Link the previous node to the next one
		}
	}
}
