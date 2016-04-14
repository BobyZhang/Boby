#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// compare
template <typename E>
bool compare(E a, E b) {
	if (a == b) return false;
	else return a < b;
}

// Heap class
template <typename E> class heap {
private:
	E* Heap;      // Pointer to the heap array
	int maxsize;  // Maximum size of the heap
	int n;        // Number of elements now in the heap

	// Hepler function to put element in its correct place
	void siftdown(int pos) {
		while (!isLeaf(pos)) {
			int j = leftchild(pos);
			int rc = rightchild(pos);
			if ((rc < n) && compare(Heap[rc], Heap[j])) {
				j = rc;
			}
			if (compare(Heap[pos], Heap[j])) return;  // Done
			std::swap(Heap[pos], Heap[j]);
			pos = j;    //  Move down
		}
	}

public:
	// Constructor
	heap(E* h, int num, int max) {
		Heap = h;
		n = num;
		maxsize = max;
		buildHeap();
	}

	// Return current heap size
	int size() const { return n; }

	// True if pos is a leaf
	bool isLeaf(int pos) const { return (pos >= n / 2) && (pos < n); }

	// Return left child postion
	int leftchild(int pos) const { return 2 * pos + 1; }

	// Return right child postion
	int rightchild(int pos) const { return 2 * pos + 2; }

	// Return parent postion
	int parent(int pos) const { return (pos - 1) / 2; }

	// Heapify contents of head
	void buildHeap() {
		for (int i = n / 2 - 1; i >= 0; i--) {
			siftdown(i);
		}
	}

	// Insert "it" into the heap
	void insert(const E& it) {
		if (n >= maxsize) {
			// Heap is full
			cout << "Heap is full" << endl;
			return;
		}

		int curr = n++;
		Heap[curr] = it;      // Start at end of heap
		
		// Now sift up until curr's parent > curr
		while ((curr != 0) && compare(Heap[curr], Heap[parent(curr)])) {
			std::swap(Heap[curr], Heap[parent(curr)]);
			curr = parent[curr];
		}
	}

	// Remove first value
	E removefirst() {
		if (n <= 0) {
			cout << "Heap is empty" << endl;
			//return NULL;
		}

		std::swap(Heap[0], Heap[--n]);    // Swap first with last value
		if (n != 0) siftdown(0);     // Siftdown new root val
		return Heap[n];              // Return deleted value
	}

	// Remove and return element at specified postion
	E remove(int pos) {
		if (pos < 0 || pos >= n) {
			cout << "Bad postion" << endl;
			return;
		}

		// Last element, no work to do
		if (pos == (n - 1)) n--;
		else {
			std::swap(Heap[pos], Heap[--n]);
			while ((pos != 0) && compare(Heap[pos], Heap[parent(pos)])) {
				std::swap(Heap[pos], Heap[parent(pos)]);  // Push up large key
				pos = parent(pos);
			}
			if (n != 0) siftdown(pos);  // Push down small key
		}
		return Heap[n];
	}
};