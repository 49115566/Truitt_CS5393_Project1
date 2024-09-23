/*
Library Management System
- Implement a library management system that utilizes various data structures:
	- Use a hash table to store books by ISBN
	- Use a BST to store books by title
	- Implement a queue for book reservations
- Reserve 10 books, display
- Reserve 2 of the same books and display next availability
	- Use a stack for tracking recently borrowed books
- Return the above book reserved by 2 people and lend it out again
	- Implement search functionality using appropriate algorithms
- Any one search mechanism and state it (e.g. binary search, linear search)

Learning Outcome: Understanding how different data structures may be used
*/
#include "LMS.h"

int main() {
	LMS SMU_CS_Library;	//Open a library
	SMU_CS_Library.interface();	//Interact with the library

	return 0;
}