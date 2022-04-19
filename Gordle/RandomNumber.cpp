#include "RandomNumber.h"
#include <ctime>

std::mt19937 RandomNumber::random((unsigned int)time(0));

//Uses mt19937 to get a random number
int RandomNumber::Number(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}

//Uses the user's current date to get a determined number
int RandomNumber::DailyNumber(int min, int max)
{
	std::time_t currTime = time(0);
	std::tm date;
	localtime_s(&date, &currTime);
	std::srand(date.tm_year + date.tm_mon + date.tm_mday);
	return rand() % max;
}