#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <iostream>
using namespace std;

// Node structure definition for a doubly linked list
struct qNode {
	qNode* prev;              // Pointer to the previous node (qNode)
	qNode* next;              // Pointer to the next node (qNode)
	const char* val;          // Pointer to constant character string (C-style string)
};

// Queue class definition (Doubly linked list implementation)
class Q {
private:
	qNode* head;              // Pointer to the front (head) of the queue
	qNode* tail;              // Pointer to the end (tail) of the queue
	int len;                  // Integer representing the length of the queue

public:
	Q();                      // Constructor for initializing the queue
	~Q();                     // Destructor for cleaning up the queue

	void enqueue(char* v);     // Method to add a value (char*) to the queue
	const char* dequeue();     // Method to remove and return the front value
	const char* front();       // Method to get the front value without removing it
	bool isEmpty();            // Method to check if the queue is empty
	int length();              // Method to get the length of the queue
	void displayAll();         // Method to display all values in the queue
};

// Constructor definition to initialize the queue
Q::Q() {
	head = nullptr;            // Initially, head is null (empty queue)
	tail = nullptr;            // Initially, tail is also null (empty queue)
	len = 0;                   // Initial length of the queue is 0
}

// Destructor to clean up memory for the queue
Q::~Q() {
	while (head) {             // While the queue is not empty
		tail = head->next;     // Move tail to the next node
		delete head;           // Delete the current head node
		head = tail;           // Move head to the next node
	}
}

// Method to add a value to the end of the queue
void Q::enqueue(char* v) {
	qNode* newNode = new qNode;    // Dynamically allocate a new qNode
	newNode->val = v;              // Set the node's value to the input value
	newNode->next = nullptr;       // The next node is null (since it's the last node)
	newNode->prev = tail;          // The previous node is the current tail

	if (tail) tail->next = newNode; // If the queue is not empty, update the current tail's next
	else head = newNode;            // If the queue is empty, newNode becomes the head

	tail = newNode;                 // Update the tail to the new node
	len++;                          // Increment the length of the queue
}

// Method to remove and return the front value of the queue
const char* Q::dequeue() {
	if (!head) return nullptr;      // If the queue is empty, return null

	qNode* temp = head;             // Store the current head node
	const char* v = head->val;      // Get the value of the head node
	head = head->next;              // Move the head to the next node

	if (head) head->prev = nullptr; // If the queue is not empty, update the head's prev pointer
	else tail = nullptr;            // If the queue becomes empty, update tail to nullptr

	delete temp;                    // Delete the dequeued node
	len--;                          // Decrease the length of the queue
	return v;                       // Return the dequeued value
}

// Method to return the front value without removing it
const char* Q::front() {
	if (!head) {                    // If the queue is empty, throw an error
		throw runtime_error("Queue is empty, no front element.");
	}
	return head->val;               // Return the value at the head
}

// Method to check if the queue is empty
bool Q::isEmpty() {
	return len == 0;                // Return true if the length is 0 (queue is empty)
}

// Method to return the length of the queue
int Q::length() {
	return len;                     // Return the length of the queue
}

// Method to display all elements in the queue
void Q::displayAll() {
	qNode* temp = head;             // Start from the head node
	while (temp) {                  // While there are more nodes in the queue
		cout << temp->val;           // Print the value of the current node
		if (temp->next) cout << ", "; // Print a comma if there's a next node
		temp = temp->next;           // Move to the next node
	}
	cout << endl;                   // End the line after printing all values
}

#endif