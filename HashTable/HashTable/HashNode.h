#pragma once
#ifndef _HASHNODE_H
#define _HASHNODE_H

#include <iostream>
#include <vector>
#include <string>

class HashNode {
public:
	// key for hash index
	std::string key;
	// information fields
	std::vector<std::string> fields;

	// displays the fields
	void display() {
		for (int i = 0; i < fields.size() - 1; i++) {
			std::cout << fields[i] << " ";
		}
		std::cout << fields[fields.size() - 1];
	}
};

#endif