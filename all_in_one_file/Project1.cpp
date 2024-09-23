#include <iostream>            // For standard I/O operations
#include <random>              // For random number generation
#include <vector>              // For using vectors
#include <cmath>               // For mathematical functions (e.g., sqrt)
#include <cstring>             // For string comparison (strcmp)
#include <algorithm>           // For algorithms like std::max
#include <fstream>             // For file handling
#include <sstream>             // For string stream operations
using namespace std;           // Standard namespace

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

// Helper function to check if a number is prime using smaller primes
bool is_prime(int num, const std::vector<int>* primes) {
	if (num <= 1) return false;    // Numbers less than or equal to 1 are not prime
	if (num == 2) return true;     // 2 is prime
	if (num % 2 == 0) return false; // Even numbers greater than 2 are not prime

	// Check divisibility by smaller primes up to sqrt(num)
	int limit = std::sqrt(num);    // Calculate the square root of the number
	for (int prime : *primes) {    // Iterate through the list of smaller primes
		if (prime > limit) break;  // If the prime exceeds the limit, stop
		if (num % prime == 0) {    // If the number is divisible by any prime, it's not prime
			return false;
		}
	}
	return true;                   // Return true if no divisor was found (prime number)
}

// Function to generate a list of small prime numbers up to a limit
std::vector<int>* generate_small_primes(int limit) {
	std::vector<int>* primes = new vector<int>;  // Dynamically allocate a vector of integers
	primes->push_back(2);          // Add 2 as the first prime number

	for (int i = 3; i <= limit; i += 2) {  // Check only odd numbers
		bool is_prime = true;      // Assume the number is prime
		for (int prime : *primes) { // Check divisibility by smaller primes
			if (prime * prime > i) break; // Stop if the prime exceeds the square root of the number
			if (i % prime == 0) {  // If divisible, it's not a prime
				is_prime = false;
				break;
			}
		}
		if (is_prime) {            // If still prime, add it to the list
			primes->push_back(i);
		}
	}
	return primes;                 // Return the list of primes
}

// Function to find the next prime number greater than or equal to `n`
int next_prime(int n) {
	if (n <= 2) return 2;          // Return 2 if the input is less than or equal to 2

	if (n % 2 == 0) n++;           // If the number is even, start with the next odd number

	std::vector<int>* small_primes = generate_small_primes(std::sqrt(n) + 1); // Pre-generate small primes

	while (!is_prime(n, small_primes)) { // Check if the current number is prime
		n += 2;                  // Increment by 2 to skip even numbers
	}

	delete small_primes;           // Free the memory used by the small primes vector

	return n;                      // Return the next prime number
}

// Class definition for integer hashing
class intHash {
private:
	const uint64_t prime_modulus;   // A large prime modulus (uint64_t = 64-bit unsigned integer)
	uint64_t large_prime_constant;  // A large random prime constant (uint64_t)

public:
	intHash(uint64_t prime_modulus = (1ULL << 41) - 1); // Constructor with prime modulus default value
	uint64_t generate_random_prime_constant();         // Method to generate a large random prime constant
	uint64_t hash(int64_t x) const;                    // Method to hash a 10-digit integer (int64_t = 64-bit signed integer)
};

// Constructor definition
intHash::intHash(uint64_t prime_modulus) : prime_modulus(prime_modulus) {
	large_prime_constant = generate_random_prime_constant(); // Generate and assign a random prime constant
}

// Method to generate a random large prime constant
uint64_t intHash::generate_random_prime_constant() {
	random_device rd;                 // Random device for seeding
	mt19937_64 gen(rd());             // 64-bit Mersenne Twister generator
	uniform_int_distribution<uint64_t> dist(1e9, 1e11); // Distribution range [1e9, 1e11]

	return dist(gen);                 // Generate and return a random number within the range
}

// Hash function for 10-digit integer values
uint64_t intHash::hash(int64_t x) const {
	uint64_t hash_value = x * large_prime_constant; // Multiply the input by the large prime constant
	hash_value ^= (hash_value >> 29);               // XOR with a shifted version to spread bits
	hash_value = hash_value % prime_modulus;        // Apply modulus operation with the prime modulus

	return hash_value;                              // Return the final hash value
}
class hashTable {                  // Class for a hash table implementation
private:
	intHash h;                      // An instance of the intHash class for hashing
	sortedList* table;              // Pointer to an array of sortedList for collision resolution
	int tableLen;                   // Length of the hash table (number of slots)

public:
	hashTable(int expNumBooks);     // Constructor to initialize the hash table
	~hashTable();                   // Destructor to clean up the hash table
	void insert(bookInfo* v);       // Method to insert a book into the hash table
	bookInfo* get(int ISBN);        // Method to retrieve a book by ISBN
	void remove(int ISBN);          // Method to remove a book by ISBN
};

// Constructor definition for the hash table
hashTable::hashTable(int expNumBooks) {
	// Set tableLen to the next prime greater than expected number of books divided by 0.75
	tableLen = next_prime(expNumBooks / 0.75 + 1);
	table = new sortedList[tableLen];  // Dynamically allocate an array of sortedList for collision handling
}

// Destructor to clean up the hash table
hashTable::~hashTable() {
	h.~intHash();                    // Explicitly call the intHash destructor
	delete[] table;                  // Free the dynamically allocated sortedList array
}

// Insert a book into the hash table
void hashTable::insert(bookInfo* v) {
	// Hash the ISBN and mod by table length to find the correct slot, then insert the book into the sorted list at that slot
	table[h.hash(v->ISBN) % tableLen].insert(v);
}

// Retrieve a book from the hash table by ISBN
bookInfo* hashTable::get(int ISBN) {
	// Hash the ISBN, mod by table length, then retrieve the book from the sorted list at that slot
	return table[h.hash(ISBN) % tableLen].get(ISBN);
}

// Remove a book from the hash table by ISBN
void hashTable::remove(int ISBN) {
	// Hash the ISBN, mod by table length, then remove the book from the sorted list at that slot
	table[h.hash(ISBN) % tableLen].remove(ISBN);
}


// Node structure for an AVL tree
struct tNode {
	tNode* left;                    // Pointer to the left child of the node
	tNode* right;                   // Pointer to the right child of the node
	bookInfo* val;                  // Pointer to the book information stored in the node
	int height;                     // Integer representing the height of the node

	// Constructor to initialize a tree node with bookInfo
	tNode(bookInfo* b) : left(nullptr), right(nullptr), val(b), height(1) {}
};

// AVL tree class definition (self-balancing binary search tree)
class AVL {
private:
	tNode* head;                    // Pointer to the root node of the AVL tree

	tNode* insertRec(tNode* node, bookInfo* v);  // Recursive method to insert and balance the tree
	bookInfo* retrieveRec(tNode* node, char* t); // Recursive method to retrieve a book by title
	tNode* removeRec(tNode* node, char* t);      // Recursive method to remove a book and balance the tree
	tNode* rotateRight(tNode* y);    // Method to perform a right rotation
	tNode* rotateLeft(tNode* x);     // Method to perform a left rotation
	tNode* balance(tNode* node);     // Method to balance the AVL tree
	int height(tNode* node);         // Method to return the height of a node
	int getBalance(tNode* node);     // Method to get the balance factor of a node
	tNode* findMin(tNode* node);     // Method to find the minimum value node in the tree
	void deleteTree(tNode* node);    // Recursive method to delete the entire tree

public:
	AVL();                          // Constructor to initialize the AVL tree
	~AVL();                         // Destructor to clean up the AVL tree
	void insert(bookInfo* v);        // Method to insert a book into the AVL tree
	bookInfo* retrieve(char* t);     // Method to retrieve a book by title
	void remove(char* t);            // Method to remove a book by title
};

// Constructor for the AVL tree
AVL::AVL() : head(nullptr) {}       // Initialize the head of the tree to nullptr

// Destructor for the AVL tree
AVL::~AVL() {
	deleteTree(head);               // Call the recursive deleteTree method to clean up
}

// Recursive method to delete the entire AVL tree
void AVL::deleteTree(tNode* node) {
	if (node) {                     // If the node is not null
		deleteTree(node->left);      // Recursively delete the left subtree
		deleteTree(node->right);     // Recursively delete the right subtree
		delete node;                 // Delete the current node
	}
}

// Public method to insert a book into the AVL tree
void AVL::insert(bookInfo* v) {
	head = insertRec(head, v);      // Call the recursive insert method, starting from the root
}

// Recursive method to insert a node into the AVL tree and balance it
tNode* AVL::insertRec(tNode* node, bookInfo* v) {
	if (!node) return new tNode(v); // If the node is null, create a new node with the book info

	int cmp = strcmp(v->title, node->val->title); // Compare the titles of the books
	if (cmp < 0) {                  // If the new book's title is less than the current node's
		node->left = insertRec(node->left, v); // Insert into the left subtree
	}
	else if (cmp > 0) {             // If the new book's title is greater than the current node's
		node->right = insertRec(node->right, v); // Insert into the right subtree
	}
	else {                          // If the book already exists, do nothing
		return node;
	}

	// Update the height of the current node
	node->height = 1 + max(height(node->left), height(node->right));

	// Balance the tree and return the new root of the subtree
	return balance(node);
}

// Public method to retrieve a book by title
bookInfo* AVL::retrieve(char* t) {
	return retrieveRec(head, t);    // Call the recursive retrieve method, starting from the root
}

// Recursive method to retrieve a book by title
bookInfo* AVL::retrieveRec(tNode* node, char* t) {
	if (!node) return nullptr;      // If the node is null, return nullptr (book not found)

	int cmp = strcmp(t, node->val->title); // Compare the target title with the current node's title
	if (cmp == 0) {                // If the titles match, return the book info
		return node->val;
	}
	else if (cmp < 0) {            // If the target title is less, search the left subtree
		return retrieveRec(node->left, t);
	}
	else {                         // If the target title is greater, search the right subtree
		return retrieveRec(node->right, t);
	}
}

// Public method to remove a book by title
void AVL::remove(char* t) {
	head = removeRec(head, t);     // Call the recursive remove method, starting from the root
}

// Recursive method to remove a node by title and balance the tree
tNode* AVL::removeRec(tNode* node, char* t) {
	if (!node) return nullptr;      // If the node is null, return null (book not found)

	int cmp = strcmp(t, node->val->title); // Compare the target title with the current node's title
	if (cmp < 0) {                 // If the target title is less, search the left subtree
		node->left = removeRec(node->left, t);
	}
	else if (cmp > 0) {            // If the target title is greater, search the right subtree
		node->right = removeRec(node->right, t);
	}
	else {                         // If the book is found
		if (!node->left || !node->right) { // If the node has one or no children
			tNode* temp = node->left ? node->left : node->right; // Choose the non-null child
			if (!temp) {             // If there are no children
				temp = node;         // Temporarily store the node
				node = nullptr;      // Set the node to null
			}
			else {
				*node = *temp;       // Copy the non-null child to the current node
			}
			delete temp->val;        // Delete the book info in the node
			delete temp;             // Delete the node
		}
		else {                      // If the node has two children
			tNode* temp = findMin(node->right); // Find the in-order successor
			node->val = temp->val;   // Replace the current node's value with the successor's value
			node->right = removeRec(node->right, temp->val->title); // Remove the successor
		}
	}

	if (!node) return node;         // If the tree is empty, return null

	// Update the height of the current node
	node->height = 1 + std::max(height(node->left), height(node->right));

	// Balance the tree and return the new root of the subtree
	return balance(node);
}

// Helper method to find the minimum value node in the tree (used in deletion)
tNode* AVL::findMin(tNode* node) {
	while (node->left) {            // Traverse the left subtree to find the minimum
		node = node->left;
	}
	return node;                    // Return the node with the minimum value
}

// Method to perform a right rotation to balance the tree
tNode* AVL::rotateRight(tNode* y) {
	tNode* x = y->left;             // Set x as the left child of y
	tNode* T2 = x->right;           // Store the right subtree of x

	x->right = y;                   // Perform the rotation (x becomes the new root)
	y->left = T2;                   // Move T2 to the left of y

	// Update heights of y and x
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;                       // Return the new root
}

// Method to perform a left rotation to balance the tree
tNode* AVL::rotateLeft(tNode* x) {
	tNode* y = x->right;            // Set y as the right child of x
	tNode* T2 = y->left;            // Store the left subtree of y

	y->left = x;                    // Perform the rotation (y becomes the new root)
	x->right = T2;                  // Move T2 to the right of x

	// Update heights of x and y
	x->height = std::max(height(x->left), height(x->right)) + 1;
	y->height = std::max(height(y->left), height(y->right)) + 1;

	return y;                       // Return the new root
}

// Method to balance the AVL tree after insertion or deletion
tNode* AVL::balance(tNode* node) {
	int balanceFactor = getBalance(node); // Get the balance factor of the current node

	// Left heavy case
	if (balanceFactor > 1) {
		if (getBalance(node->left) >= 0) {
			return rotateRight(node); // Left-left case, perform right rotation
		}
		else {
			node->left = rotateLeft(node->left); // Left-right case, perform left-right rotation
			return rotateRight(node);
		}
	}

	// Right heavy case
	if (balanceFactor < -1) {
		if (getBalance(node->right) <= 0) {
			return rotateLeft(node); // Right-right case, perform left rotation
		}
		else {
			node->right = rotateRight(node->right); // Right-left case, perform right-left rotation
			return rotateLeft(node);
		}
	}

	return node;                    // If balanced, return the node as is
}

// Method to get the height of a node (helper for balancing)
int AVL::height(tNode* node) {
	if (!node) return 0;            // If the node is null, return height 0
	return node->height;            // Otherwise, return the height of the node
}

// Method to get the balance factor of a node
int AVL::getBalance(tNode* node) {
	if (!node) return 0;            // If the node is null, return balance factor 0
	return height(node->left) - height(node->right); // Return the difference in heights
}
// Node structure for a stack (Doubly linked list structure)
struct sNode {
	sNode* above;                 // Pointer to the node above in the stack
	sNode* below;                 // Pointer to the node below in the stack
	bookInfo* val;                // Pointer to the book information stored in the node

	// Constructor to initialize the stack node with bookInfo
	sNode(bookInfo* v) : val(v), above(nullptr), below(nullptr) {}
};

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

// Helper function to append one string to the end of another
void addToEnd(char* beg, char* end) {
	int i;                        // Integer for indexing
	for (i = 0; beg[i]; i++);      // Move i to the end of the first string (beg)
	beg[i] = ',';					//This function gets called when a comma splits titles, so 
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


int main() {
	LMS SMU_CS_Library;	//Open a library
	SMU_CS_Library.interface();	//Interact with the library

	return 0;
}