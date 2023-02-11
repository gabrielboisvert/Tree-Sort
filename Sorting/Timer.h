#pragma once
#include <chrono>

class Timer
{
private:
	size_t t;
	size_t m;

public:
	void start();

	size_t stop();
};