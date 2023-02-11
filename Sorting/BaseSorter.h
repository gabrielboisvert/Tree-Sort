#pragma once


#include "Generation.h"

namespace Sorting
{

	class BaseSorter
	{
	public:

		BaseSorter(int size = 100, bool random = true) :
			m_size(size)
		{
			m_arrayToSort = Generation::GenerateRandomArray(size, random);
		}

		virtual ~BaseSorter()
		{
			delete m_arrayToSort;
		}

		virtual	int* Sort() = 0;


		bool	IsSorted() const
		{
			if (m_arrayToSort == nullptr || m_size == 1)
			{
				return true;
			}

			for (int iNbr = 0; iNbr < m_size - 1; iNbr++)
			{
				if (m_arrayToSort[iNbr] > m_arrayToSort[iNbr + 1])
				{
					return false;
				}
			}

			return true;
		}


	protected:
		int*	m_arrayToSort = nullptr;
		int		m_size = 0;
	};

}