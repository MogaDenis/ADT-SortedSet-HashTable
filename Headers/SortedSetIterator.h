#pragma once
#include "../Headers/SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	TComp* sortedElements;
	int currentIndex;
	int numberOfElements;
	Relation relationBetweenElements;

	void quickSort(TComp* elements, int left, int right);

public:
	~SortedSetIterator();

	void first();
	void next();
	TElem getCurrent();
	bool valid() const;

	void previous();
};

