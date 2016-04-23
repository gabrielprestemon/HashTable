#include "HashTable.h"

// constructor
HashTable::HashTable() {
	// default size of 17
	size = 17;
	// default no nodes in table
	count = 0;
	// allocate the table
	table = new HashNode*[size];
	// default the table to NULL
	for (int i = 0; i < size; i++) {
		table[i] = NULL;
	}
}

// destructor
HashTable::~HashTable() {
	// clear the hashtable of nodes
	clear();
	// deallocate the table
	delete[] table;
}

// insert an entry into the table based on the key
void HashTable::insert(std::vector<std::string> entry, std::string key) {
	// create a hashnode
	HashNode* n = new HashNode;
	n->fields = entry;
	n->key = key;
	// get an index for the node
	int index = getHashValue(key);
	// if there is something there, linear probe until a free space
	// count how many probes are needed
	int grouping = 0;
	while (table[index] != NULL) {
		index++;
		index %= size;
		grouping++;
	}
	// insert the node at the index
	table[index] = n;

	// increment count
	count++;

	// check if a rehash is needed
	// rehashing conditions are:
	//  table is 2/3 or more full
	//  group of 5 or more is encountered
	if (checkRehash() || grouping >= 5) {
		rehash();
	}

}

// if a node related to the key exists, return a copy of the node
HashNode HashTable::find(std::string key) {
	// create an object to return
	HashNode n;
	// find the index related to the key
	int index = getHashValue(key);
	// if there are nodes at the key index
	if (table[index] != NULL) {
		// linear probe if needed
		while (table[index]->key != key) {
			index++;
			index %= size;
			// if an empty node is reached, stop probing
			if (table[index] == NULL) {
				break;
			}
		}
		// if there is a node at the index, set the returning node to it
		if (table[index] != NULL) {
			n.key = table[index]->key;
			n.fields = table[index]->fields;
		}
	}
	return n;
}

// display the hash table
void HashTable::display() {
	for (int i = 0; i < size; i++) {
		if (table[i] != NULL) {
			table[i]->display();
			std::cout << std::endl;
		}
	}
}

// clear the hashtable
void HashTable::clear() {
	for (int i = 0; i < size; i++) {
		// if there is something at the index, deallocate
		if (table[i] != NULL) {
			delete table[i];
		}
	}
	// set count to 0
	count = 0;
}

// resize and rehash the table
void HashTable::rehash() {
	//create a temporary table
	HashNode** temp = new HashNode*[count];

	// move the nodes into the temporary table
	int tempIt = 0;
	for (int i = 0; i < size; i++) {
		if (table[i] != NULL) {
			temp[tempIt++] = table[i];
		}
	}

	// deallocate and reallocate the table
	delete[] table;
	table = new HashNode*[size = nextTableSize(size)];
	// default the table to NULL
	for (int i = 0; i < size; i++) {
		table[i] = NULL;
	}

	// reinsert all the nodes
	for (int i = 0; i < count; i++) {
		// get a new index
		int index = getHashValue(temp[i]->key);
		// if there is a collision, linear probe
		while (table[index] != NULL) {
			index++;
			index %= size;
		}
		// insert the node
		table[index] = temp[i];
	}

	// deallocate the temporary table
	delete[] temp;
}

// get the next largest table size larger than the current
int HashTable::nextTableSize(int current) {
	// current * 2 < nextPrime < current * 3
	// start at current * 2 + 1, which will be odd
	// only check odd numbers, even is never prime (except 2)
	for (int next = (current * 2) + 1; next < current * 3; next += 2) {
		// assume this cycle will produce a prime number
		bool prime = true;
		// cycle through to check all possible divisors
		for (int i = 3; i < next / 2; i += 2) {
			// if it is found to not be prime, stop checking
			if (next % i == 0) {
				prime = false;
				break;
			}
		}
		// if it made it through the check, it's prime
		if (prime) {
			return next;
		}
	}
	// if it made it through all that just return current * 3 - 1
	// this will be close enough to prime for us
	return (current * 3) - 1;
}

// get the hashvalue table index related to the key
int HashTable::getHashValue(std::string key) {
	int val = 0;
	// sum ascii values, bound to table size
	for (int i = 0; i < key.size(); i++) {
		val += key[i];
		val %= size;
	}
	// resulting value is the table index for this key
	return val;
}
