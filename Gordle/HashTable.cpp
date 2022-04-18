#include "HashTable.h"
#include <algorithm>
#include <iostream>
#include <cmath>

HashTable::HashTable()
{
	tableSize = 10;
	numItems = 0;
	maxLoadFactor = 0.75f;
	arr = new std::vector<std::list<std::string>>(tableSize);
}

HashTable::~HashTable()
{
	delete arr;
}

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

int HashTable::hash(std::string input)
{
	int power = 31, sum = 0, size = input.size();

	for (int i = 0; i < size; i++) {
		sum += input.at(i) * std::pow(31, size - 1 - i);
	}

	return sum % tableSize;
}

int HashTable::twoLetterHash(std::string input)
{
	input = input.substr(0, 2);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	int firstL = input.at(0) - 'a', secondL = input.at(1) - 'a';
	return firstL * 26 + secondL;
}

int HashTable::threeLetterHash(std::string input)
{
	input = input.substr(2, 3);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	int firstL = input.at(0) - 'a', secondL = input.at(1) - 'a', thirdL = input.at(2) - 'a';
	return firstL * 26 * 26 + secondL * 26 + thirdL;
}

void HashTable::insert(std::string input)
{
	if (find(input))
		return;

	int index = hash(input);

	arr->at(index).push_back(input);
	numItems++;

	if (((float)numItems / (float)tableSize) >= maxLoadFactor)
		reHash();
}

bool HashTable::find(std::string input)
{
	int index = hash(input);
	for (auto i : arr->at(index)) {
		if (i == input)
			return true;
	}
	return false;
}

std::string HashTable::randomWord(int goTo)
{
	auto it = arr->begin();
	while (goTo > it->size()) {
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