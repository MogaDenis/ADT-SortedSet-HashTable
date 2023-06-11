# ADT-SortedSet-HashTable

  Sorted Set abstract data type implemented on a hash table, using double hashing as collision resolution. The elements in the set are of a generic type
and are sorted based on a relation. Since in a hash table elements are stored "randomly" and elements are accessible outside the class only through 
the iterator, the sorting of the elements is done when the iterator is created.

The container provides the following mehods:
  - Add
  - Remove
  - Search
  - IsEmpty
  - Size

The iterator sorts the elements upon creation based on the given relation. It has the following methods:
  - IsValid
  - Next
  - First
  - GetCurrent
