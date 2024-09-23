#pragma once
#include "bookInfo.h"

// Stack class definition
class stack {
private:
	sNode* top;                   // Pointer to the top node of the stack

public:
	stack();                      // Constructor to initialize the stack
	~stack();                     // Destructor to clean up the stack
	void push(bookInfo* v);        // Method to push a book onto the stack
	bookInfo* pop();               // Method to pop a book off the stack
	bookInfo* peep();              // Method to peek at the top book without removing it
};

// Constructor for the stack
stack::stack() {
	top = nullptr;                // Initialize the top of the stack as null (empty stack)
}

// Destructor to clean up the stack
stack::~stack() {
	sNode* below;                 // Temporary pointer to store the node below
	while (top) {                 // While there are nodes in the stack
		below = top->below;       // Move below to the next node in the stack
		delete top;               // Delete the current top node
		top = below;              // Move top to the next node in the stack
	}
}

// Method to push a book onto the stack
void stack::push(bookInfo* v) {
	sNode* newNode = new sNode(v); // Dynamically allocate a new node with bookInfo
	if (top) top->above = newNode; // If the stack is not empty, set the current top's above to new node
	newNode->below = top;          // Set the new node's below pointer to the current top
	top = newNode;                 // Update the top of the stack to the new node
}

// Method to pop a book off the stack
bookInfo* stack::pop() {
	if (!top) return nullptr;      // If the stack is empty, return null

	bookInfo* ret = top->val;      // Get the bookInfo stored at the top of the stack
	sNode* temp = top;             // Temporarily store the current top node
	top = top->below;              // Move top to the next node in the stack
	delete temp;                   // Delete the old top node
	if (top) top->above = nullptr; // If the stack is not empty, update the new top's above pointer
	return ret;                    // Return the book that was popped off the stack
}

// Method to peek at the top book without removing it
bookInfo* stack::peep() {
	if (top) return top->val;      // If the stack is not empty, return the book at the top
	else return nullptr;           // If the stack is empty, return null
}
