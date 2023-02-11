#include "pch.h"

#include <cstdlib>

#include "Generation.h"


namespace Generation
{
	unsigned int g_seed = 0x4242;


	int* GenerateRandomArray(int size, bool random)
	{
		srand(g_seed);

		int* arr = new int[size];
		if (random)
			for (int i = 0; i < size; i++)
				arr[i] = rand();

		return arr;
	}

}