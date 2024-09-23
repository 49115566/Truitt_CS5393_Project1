#ifndef _AVL_H_
#define _AVL_H_
#include <cstring>  // for strcmp
#include <algorithm> // for std::max
#include "bookInfo.h"

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

#endif