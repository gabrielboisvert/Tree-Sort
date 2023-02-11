// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"

#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

#include "Timer.h"
#include "BubbleSort.h"
int main(int argc, char* argv[])
{
	// global setup...

	int result = Catch::Session().run(argc, argv);

	// global clean-up...

	return result;
}

