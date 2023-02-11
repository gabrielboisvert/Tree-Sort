#include "pch.h"
#include "HeapSorter.h"
#include <utility>
#include <iostream>

namespace Sorting
{

	HeapSorter::HeapSorter(int size, bool random) :
		BaseSorter(size, random)
	{
	}


	HeapSorter::~HeapSorter()
	{
	}

	int * HeapSorter::Sort()
	{
        /*
        Il est inutile de lancer l'algorithme sur les leaf, puisque ce sont des leaf (rien en dessous).
        Par conséquent, la première étape est de faire commencer l'algo de Heapify au dernier
        nœud qui n'est pas une leaf.
        */
        for (int i = this->m_size / 2 - 1; i >= 0; i--)
            this->MaxHeapify(this->m_size, i);

        /*
        Le tableau sera donc trié sous forme de MAX Heap (du plus
        grand au plus petit).
        Il faudra ensuite le "retrier" dans le bon ordre, du plus petit au plus grand 
        */
        for (int i = this->m_size - 1; i >= 0; i--) {
            // Move current root to end
            std::swap(this->m_arrayToSort[0], this->m_arrayToSort[i]);
            // call max heapify on the reduced heap
            this->MaxHeapify(i, 0);
        }
		return m_arrayToSort;
	}

    void HeapSorter::MaxHeapify(int size, int rootIdx)
    {
        // La root de l'arbre sera toujours à l'index 0
        int root = rootIdx;
        // Index du fils gauche = (2i + 1)
        int left = 2 * rootIdx + 1;
        // Index du fils droit = (2i + 2)
        int right = 2 * rootIdx + 2;

        // On sélectionne l'index du plus grand de ses fils, et on récupère sa valeur
        if (left < size && this->m_arrayToSort[left] > this->m_arrayToSort[root])
            root = left;

        //  On sélectionne l'index du plus grand de ses fils, et on récupère sa valeur
        if (right < size && this->m_arrayToSort[right] > this->m_arrayToSort[root])
            root = right;

        // Si cette valeur est plus grande que celle de la root, on swap la root avec ce fils
        if (root != rootIdx) {
            std::swap(this->m_arrayToSort[rootIdx], this->m_arrayToSort[root]);
            this->MaxHeapify(size, root);
        }
    }

}
