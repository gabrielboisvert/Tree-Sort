#pragma once
#include "BaseSorter.h"



#define QUICKSORT_IMPLEMENTED 1


namespace Sorting
{

	class QuickSorter :
		public BaseSorter
	{
	public:
		QuickSorter(int size = 100, bool random = true);
		~QuickSorter();

		virtual	int* Sort() override;

	private:
		using PivotIndex = int;

		void	Quicksort_r(int from, int to);

		PivotIndex	Partition(int from, int to);
	};




}
