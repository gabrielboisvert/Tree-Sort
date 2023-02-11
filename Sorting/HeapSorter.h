#pragma once


#include "BaseSorter.h"


#define HEAPSORT_IMPLEMENTED 1


namespace Sorting
{


	class HeapSorter : public BaseSorter
	{
	public:
		HeapSorter(int size = 100, bool random = true);
		~HeapSorter();

		virtual	int* Sort() override;

		void MaxHeapify(int n, int i);

	};




}