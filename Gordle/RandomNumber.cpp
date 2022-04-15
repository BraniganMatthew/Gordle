#include "RandomNumber.h"
#include <ctime>

std::mt19937 RandomNumber::random((unsigned int)time(0));

int RandomNumber::Number(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}