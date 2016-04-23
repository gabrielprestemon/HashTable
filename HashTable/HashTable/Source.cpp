#include <iostream>
#include "HashTable.h"
#include <fstream>

using namespace std;

vector<vector<string>> readFromFile(string fname);

int main() {
	HashTable ht;
	// get a database from a file
	vector<vector<string>> db = readFromFile("USInfo.txt");
	// load the database into the hashtable based on the 3rd field
	for (int i = 0; i < db.size(); i++) {
		ht.insert(db[i], db[i][2]);
	}
	// display the hashtable
	ht.display();
	// find a node
	HashNode CA = ht.find("California");
	// display the node found
	cout << "\n\nSearched for \"California\":\n";
	CA.display();

	cout << "\n\n";
	system("pause");
	return 0;
}

vector<vector<string>> readFromFile(string fname) {
	// open the file
	ifstream in(fname);
	// create an empty database
	vector<vector<string>> db;
	// check if the file is open
	if (in.is_open()) {
		string line;
		// get a line from the file
		while (getline(in, line)) {
			vector<string> entry;
			// split the line into the tab-separated sections
			while (line.find('\t') != string::npos) {
				// push the first tab-seperated section into the entry
				entry.push_back(line.substr(0, line.find('\t')));
				// remove that section from the string
				line = line.substr(line.find('\t') + 1, line.size());
			}
			// push the final section into the entry
			entry.push_back(line);
			// push the entry into the database
			db.push_back(entry);
		}
	}
	return db;
}
