#pragma once
#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include "HashNode.h"

class HashTable {
public:
	// constructor
	HashTable();
	// destructor
	~HashTable();

	// insert an entry into the table based on the key
	void insert(std::vector<std::string>, std::string);
	// if a node related to the key exists, return a copy of the node
	HashNode find(std::string);

	// display the hash table
	void display();

	// clear the hashtable
	void clear();

private:
	HashNode** table;
	unsigned int count;
	unsigned int size;

	// check to see if the table needs to be rehashed
	bool checkRehash() { return (count / size > 0.66); }
	// resize and rehash the table
	void rehash();
	// get the next largest table size larger than the current
	int nextTableSize(int);
	// get the hashvalue table index related to the key
	int getHashValue(std::string);
};

#endif