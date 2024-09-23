#pragma once
#include <random>
#include "List.h"
#include <vector>
#include <cmath>

// Helper function to check if a number is prime using a list of smaller prime numbers
//Will not work properly if not all primes < sqrt(num) are on primes list
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
