#pragma once
#include <random>

class RandomNumber
{
	static std::mt19937 random;
public:
	static int Number(int min, int max);
};

