#include "../Headers/SortedSet.h"
#include "../Headers/SortedSetIterator.h"
#include <iostream>

SortedSet::SortedSet(Relation r) 
{
	this->numberOfElements = 0;
	this->relationBetweenElements = r;
	this->capacity = 2002;
	this->prime = 19;

	this->elements = new TComp[this->capacity];

	for (int i = 0; i < this->capacity; i++)
		this->elements[i] = NULL_TCOMP;
}

// For time complexity analysis, consider "alfa" the load factor (number of elements / capacity)

// Theta(1)
int SortedSet::firstHash(TComp elem) const
{
	int result = elem % this->capacity;

	if (result < 0)
		return result * (-1);

	return result;
}


// Theta(1)
int SortedSet::secondHash(TComp elem) const
{
	if (elem < 0)
		elem *= -1;

	return this->prime - (elem % this->prime);
}


// Theta(1)
int SortedSet::hash(TComp elem, int i) const
{
	return (this->firstHash(elem) + i * this->secondHash(elem)) % this->capacity;
}


// Theta(n)
void SortedSet::resize()
{
	int oldCapacity = this->capacity;
	this->capacity *= 2;
	TComp* newArray = new TComp[this->capacity];
	for (int i = 0; i < this->capacity; i++)
		newArray[i] = NULL_TCOMP;

	int movedValues = 0;
	for (int i = 0; i < oldCapacity; i++)
	{
		if (this->elements[i] != NULL_TCOMP && this->elements[i] != DELETED_TCOMP)
		{
			int index = this->hash(this->elements[i], 0);
			int j = 0;

			while (newArray[index] != NULL_TCOMP)
			{
				j++;
				index = this->hash(this->elements[i], j);
			}

			newArray[index] = this->elements[i];
			movedValues++;
		}

		if (movedValues == this->numberOfElements)
			break;
	}

	delete[] this->elements;
	this->elements = newArray;
}


// Worst case: The load factor is over 80% -> resizing => Theta(capacity)
// Best case: Empty array or no collisions => Theta(1)
// Average case, if elem is unique => O(1 / (1 - alfa)) (the complexity of the search)
// Average case, if elem already exists => O(1 / (alfa * log(1 / (1 - alfa)))) (the complexity of the search)
bool SortedSet::add(TComp elem) 
{
	if (this->numberOfElements * 1.0 / this->capacity > 0.8)
		this->resize();

	if (this->numberOfElements == 0)
	{
		int index = this->hash(elem, 0);
		this->elements[index] = elem;
		this->numberOfElements++;

		return true;
	}

	if (this->search(elem))
		return false;

	int index = this->hash(elem, 0);
	int i = 0;

	while (this->elements[index] != NULL_TCOMP)
	{
		i++;
		index = this->hash(elem, i);
	}

	this->elements[index] = elem;
	this->numberOfElements++;

	return true;
}


// Best case: No collisions => Theta(1)
// Worst case: The element is not found => O(1 / (1 - alfa))
// Average case: The element is found, but there are collisions => O(1 / (alfa * log(1 / (1 - alfa))))
bool SortedSet::remove(TComp elem) 
{
	int index = this->hash(elem, 0);
	int i = 0;

	while (this->elements[index] != NULL_TCOMP)
	{
		if (this->elements[index] == elem)
		{
			this->numberOfElements--;
			this->elements[index] = DELETED_TCOMP;
			return true;
		}

		i++;
		index = this->hash(elem, i);
	}
	return false;
}


// Best case: No collisions => Theta(1)
// Worst case: The element is not found => O(1 / (1 - alfa))
// Average case: The element is found, but there are collisions => O(1 / (alfa * log(1 / (1 - alfa))))
bool SortedSet::search(TComp elem) const 
{
	int i = 0;
	int index = this->hash(elem, i);

	while (this->elements[index] != NULL_TCOMP)
	{
		if (this->elements[index] == elem)
			return true;

		i++;
		index = this->hash(elem, i);
	}

	return false;
}


// Theta(1)
int SortedSet::size() const 
{
	//TODO - Implementation
	return this->numberOfElements;
}


// Theta(1)
bool SortedSet::isEmpty() const 
{
	//TODO - Implementation
	return this->numberOfElements == 0;
}

// Theta(n) - copying the elements in the iterator.
// O(n^2) - sorting the elements (worst case).
// Total time complexity: O(n^2)
SortedSetIterator SortedSet::iterator() const 
{
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() 
{
	delete[] this->elements;
}


