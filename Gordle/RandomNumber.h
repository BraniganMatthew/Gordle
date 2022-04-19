#pragma once
#include <random>

class RandomNumber
{
	static std::mt19937 random;
public:
	static int Number(int min, int max);
	static int DailyNumber(int min, int max);
};

