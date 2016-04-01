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
	else return a > b;
}

// get array's length
template <typename E>
int getArrayLen(E& array) {
	return (sizeof(array) / sizeof(array[0]));
}

// insert sort
//
//
template <typename E>
void inssort(E A[], int _length) {
	for (int i = 1; i < _length; ++i) {
		for (int j = i; (j > 0) && compare<E>(A[j - 1, A[j]]); --j) {
			std::swap(A[j], A[j - 1]);
		}
	}
}

// bubble sort
//
//
template <typename E>
void bubblesort(E A[], int _length) {
	for (int i = _length - 1; i > -1; --i) {
		for (int j = 0; j < i; ++j) {
			if (compare(A[j], A[j + 1])) std::swap(A[j], A[j + 1]);
		}
	}
}

// select sort
//
//
template <typename E>
void selectsort(E A[], int _length) {
	for (int i = 0; i < _length; ++i) {
		int minindex = i;
		for (int j = i; (j < _length); ++j) {
			if (compare(A[minindex], A[j])) {
				minindex = j;
			}
		}
		std::swap(A[i], A[minindex]);
	}
}

template <typename E>
void selectsort_iprv(E A[], int _length) {
	for (int i = 0; i < _length; ++i) {
		int minindex = i;
		for (int j = i; (j < _length); ++j) {
			if (compare(A[minindex], A[j])) {
				minindex = j;
			}
		}
		// avoid unnecessarily swap
		if (minindex != i) {
			std::swap(A[i], A[minindex]);
		}
	}
}

// shell sort
//
//
template <typename E>
void shellsort(E A[], int _length) {
	for (int i = _length / 2; i > 1; i /= 2) {
		for (int j = 0; j < i; ++j) {
			insersort2(&A[j], _length - j, i);
		}
	}
	insersort2(A, _length, 1);
}

template <typename E>
void insersort2(E A[], int _length, int _incr) {
	for (int i = _incr; i < _length; i += _incr) {
		for (int j = i; (j >= _incr) && compare(A[j - _incr], A[j]); j -= _incr) {
			std::swap(A[j], A[j - _incr]);
		}
	}
}

// Binary search with recurrence
//
//
template <typename E>
int binary_search_rec(const E arr[], int low, int hight, E key) {
	if (low > hight) {
		return -1;
	}

	int mid = low + (hight - low) / 2; // incase overflow
	if (arr[mid] == key) {
		return mid;
	}
	else if (arr[mid] < key) {
		return binary_search(arr, mid + 1, hight, key);
	}
	else if (arr[mid] > key) {
		return binary_search(arr, low, mid - 1, key);
	}
}
// Binary search
//
//
template <typename E>
int binary_search(const E arr[], int low, int hight, E key) {
	while (low <= hight) {
		int mid = low + (hight - low) / 2;
		if (arr[mid] == key) {
			return mid;
		}
		else if (arr[mid] < key) {
			low = mid + 1;
			continue;
		}
		else if (arr[mid] > key) {
			hight = mid - 1;
			continue;
		}
	}
	// not found
	return -1;
}

// Sequence search
//
//
template <typename E>
int squ_search(const E arr[], int length, const E key) {
	for (int i = 0; i < length; ++i) {
		if (arr[i] == key) {
			return i;
		}
	}
	// not found
	return -1;
}

// Quik sort
template <typename E>
void qsort(E A[], int i, int j) {
	// Don't sort 0 or 1 element
	if (j <= i) return;

	int pivotindex = findpivot(A, i, j);

	int k = partition<E>(A, i - 1, j, A[j]);
	std::swap(A[k], A[j]);

	qsort<E>(A, i, k - 1);
	qsort<E>(A, k + 1, j);
}

template <typename E>
int findpivot(E A[], int i, int j) {
	return (i + j) / 2;
}

template <typename E>
int partition(E A[], int l, int r, E& pivot) {
	do {
		while (compare(A[++l], pivot));   // Move l right and
		while ((l < r) && compare(pivot, A[--r]));  // r left
		std::swap(A[l], A[r]);
	} while (l < r);
	return l;  // Return first position in right partition
}