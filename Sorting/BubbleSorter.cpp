#include "pch.h"

#include "BubbleSort.h"

#include <algorithm> // swap
namespace Sorting
{
	int* BubbleSorter::Sort()
	{
		bool finish = false;
		do
		{
			finish = true;
			for (int i = 0; i < m_size - 1; i++)
				if (this->m_arrayToSort[i] > this->m_arrayToSort[i + 1])
				{
					std::swap(this->m_arrayToSort[i], this->m_arrayToSort[i + 1]);
					finish = false;
				}
		} while (!finish);

		return this->m_arrayToSort;
	}

}