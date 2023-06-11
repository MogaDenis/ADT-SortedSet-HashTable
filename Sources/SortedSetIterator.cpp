#include "../Headers/SortedSetIterator.h"
#include <exception>

using namespace std;


// Theta(n) - copying the elements in the iterator.
// O(n^2) - sorting the elements (worst case).
// Total time complexity: O(n^2)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->currentIndex = 0;
	this->numberOfElements = m.numberOfElements;
	this->relationBetweenElements = m.relationBetweenElements;

	this->sortedElements = new TComp[this->numberOfElements];

	int j = 0;

	for (int i = 0; i < m.capacity; i++)
	{
		if (m.elements[i] != NULL_TCOMP && m.elements[i] != DELETED_TCOMP)
			this->sortedElements[j++] = m.elements[i];

		if (j == this->numberOfElements)
			break;
	}

	this->quickSort(this->sortedElements, 0, this->numberOfElements - 1);
}


void SortedSetIterator::quickSort(TComp* elements, int left, int right)
{
	if (left < right)
	{
		int middle = left + (right - left) / 2;
		TComp aux = elements[left];
		elements[left] = elements[middle];
		elements[middle] = aux;

		int i = left, j = right, d = 0;

		while (i < j)
		{
			if (!this->relationBetweenElements(elements[i], elements[j]))
			{
				aux = elements[i];
				elements[i] = elements[j];
				elements[j] = aux;
				d = 1 - d;
			}

			i += d;
			j -= 1 - d;
		}

		this->quickSort(elements, left, i - 1);
		this->quickSort(elements, i + 1, right);
	}
}


// Theta(1)
void SortedSetIterator::first() 
{
	this->currentIndex = 0;
}


// Theta(1)
void SortedSetIterator::next() 
{
	if (!this->valid())
		throw std::exception();

	this->currentIndex++;
}


// Theta(1)
void SortedSetIterator::previous()
{
	if (!this->valid())
		throw std::exception();

	this->currentIndex--;
}


// Theta(1)
TElem SortedSetIterator::getCurrent()
{
	if (!this->valid())
		throw std::exception();

	return this->sortedElements[this->currentIndex];
}


// Theta(1)
bool SortedSetIterator::valid() const 
{
	return this->currentIndex < this->numberOfElements && this->currentIndex >= 0;
}


SortedSetIterator::~SortedSetIterator()
{
	delete[] this->sortedElements;
}

