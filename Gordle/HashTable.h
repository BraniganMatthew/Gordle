#pragma once

#include <string>
#include <list>
#include <vector>

class HashTable
{
	private:
		std::vector<std::list<std::string>>* arr;
		unsigned int tableSize, numItems;
		float maxLoadFactor;

		int twoLetterHash(std::string input);
		int threeLetterHash(std::string input);
		int hash(std::string input);
		void reHash();
		

	public:
		void insert(std::string input);
		bool find(std::string input);
		std::string randomWord(int goTo);
		HashTable();
		~HashTable();

};

