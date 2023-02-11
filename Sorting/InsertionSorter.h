#pragma once


#include "BaseSorter.h"

#define INSERTION_IMPLEMENTED 1

namespace Sorting
{

	class InsertionSorter :
		public BaseSorter
	{
	public:
		InsertionSorter(int size = 100, bool random = true);
		~InsertionSorter();


		virtual	int* Sort() override;

	};


}

