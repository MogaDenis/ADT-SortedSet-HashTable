#include "../Headers/ShortTest.h"
#include "../Headers/ExtendedTest.h"
#include "../Headers/SortedSet.h"
#include "../Headers/SortedSetIterator.h"
#include <iostream>
#include <time.h>

using namespace std;

int main() {
	clock_t start = clock();

	testAll();
	testAllExtended();

	clock_t end = clock();

	double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;

	cout << "Test end, time spent: " << timeSpent << '\n';
	// system("pause");

	testPrevious();
	std::cout << "Bonus operation test passed!\n";
}