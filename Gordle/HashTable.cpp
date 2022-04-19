#include "HashTable.h"
#include <algorithm>
#include <iostream>
#include <cmath>

//Initializes Hash table with default values
HashTable::HashTable()
{
	tableSize = 10;
	numItems = 0;
	maxLoadFactor = 0.75f;
	arr = new std::vector<std::list<std::string>>(tableSize);
}

//Deletes vector of lists when done
HashTable::~HashTable()
{
	delete arr;
}

//Uses power of 31 hashing for the strings
void HashTable::reHash()
{
	tableSize *= 2;
	std::vector<std::list<std::string>>* oldArr = arr;
	arr = new std::vector<std::list<std::string>>(tableSize);
	int index;


	for (auto i : *oldArr) {
		for (auto j : i) {
			index = hash(j);
			arr->at(index).push_back(j);
		}
	}
	
	delete oldArr;
}

//Converts string value into usable hash number
int HashTable::hash(std::string input)
{
	unsigned int power = 31, sum = 0, size = (unsigned int)input.size();
	//Uses power of 31 hashing for the strings
	for (int i = 0; i < size; i++) {
		sum += input.at(i) * (unsigned int) std::pow(31, size - 1 - i);
	}

	return sum % tableSize;
}

//Checks if the value already exists in hash, if not, then hash and push word into location
void HashTable::insert(std::string input)
{
	if (find(input))
		return;

	int index = hash(input);

	arr->at(index).push_back(input);
	numItems++;

	//if current load factor is >= to max, then rehash the table
	if (((float)numItems / (float)tableSize) >= maxLoadFactor)
		reHash();
}

//Returns a true or false if the input is currently in the hashtable
bool HashTable::find(std::string input)
{
	int index = hash(input);
	for (auto i : arr->at(index)) {
		if (i == input)
			return true;
	}
	return false;
}

//Returns a random word from the table depending on the given number
std::string HashTable::randomWord(int goTo)
{
	auto it = arr->begin();
	while (goTo > (int) it->size()) {
		goTo -= it->size();
		it++;
	}
	auto temp = it->begin();
	while (goTo > 0) {
		goTo--;
		temp++;
	}
	if (temp == it->end())
		temp--;
	return *temp;
}