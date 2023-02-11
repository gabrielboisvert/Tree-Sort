#include "pch.h"
#include "Timer.h"
#include <iostream>

void Timer::start()
{
	this->t = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	this->m = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

size_t Timer::stop()
{
	size_t res = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - this->t;
	size_t mil = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - this->m;
	this->t = 0;
	this->m = 0;

	std::cout << "Time taked: " << res << " nanoseconds" << std::endl;
	std::cout << "Time taked: " << mil << " milliseconds" << std::endl;

	return res;
}