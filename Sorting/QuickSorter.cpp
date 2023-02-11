#include "pch.h"
#include "QuickSorter.h"

#include <utility> // swap
#include <iostream>

namespace Sorting
{
	QuickSorter::QuickSorter(int size, bool random) :
		BaseSorter(size, random)
	{
	}


	QuickSorter::~QuickSorter()
	{
	}

	int* QuickSorter::Sort()
	{
        this->Quicksort_r(0, this->m_size - 1);
		return m_arrayToSort;
	}

    void QuickSorter::Quicksort_r(int from, int to)
    {
        // To not increase the stack size
        tailRecursion:
            if (from < to)
            {
                //Get pivot
                QuickSorter::PivotIndex pi = this->Partition(from, to);

                // First partition is smaller
                if (pi < (from + to) / 2)
                { 
                    // Sort first partition
                    this->Quicksort_r(from, pi - 1);
                
                    // Sort second partition
                    from = pi + 1;
                    goto tailRecursion;
                }
                // Second partition is smaller
                else
                {   
                    // Sort second partition
                    this->Quicksort_r(pi + 1, to);
                
                    // Sort first partition
                    to = pi - 1;
                    goto tailRecursion;
                }
            }
    }

    QuickSorter::PivotIndex QuickSorter::Partition(int from, int to)
    {
        int i = (from - 1);
        for (int j = from; j <= to - 1; j++)
            if (this->m_arrayToSort[j] <= this->m_arrayToSort[to]) {
                i++;
                std::swap(this->m_arrayToSort[i], this->m_arrayToSort[j]);
            }

        std::swap(this->m_arrayToSort[i + 1], this->m_arrayToSort[to]);
        return i + 1;
    }



}
