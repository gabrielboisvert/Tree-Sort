#pragma once

#include "BaseSorter.h"


#define BUBBLE_IMPLEMENTED 1


namespace Sorting
{
	class BubbleSorter : public BaseSorter
	{
	public:
		BubbleSorter(int size = 100, bool random = true) :
			BaseSorter(size, random)
		{}


		virtual	int* Sort() override;




	};

}