#include "pch.h"
#include "InsertionSorter.h"
#include <algorithm> // swap

namespace Sorting
{
	InsertionSorter::InsertionSorter(int size, bool random) :
		BaseSorter(size, random)
	{}


	InsertionSorter::~InsertionSorter()
	{
	}

	int * InsertionSorter::Sort()
	{
		for (int i = 1; i < this->m_size; i++)
			for (int j = i; j > 0; j--)
				if (this->m_arrayToSort[j - 1] > this->m_arrayToSort[j])
					std::swap(this->m_arrayToSort[j], this->m_arrayToSort[j - 1]);
		return m_arrayToSort;
	}



}
