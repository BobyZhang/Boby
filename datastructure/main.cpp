
//#include <cmath>
//
//#include "linklist.h"
//#include "linkstack.h"
//#include "linkqueue.h"
//#include "binTree.h"
//#include "BST.h"

#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include "sort.h"

// For sort
//
//

//#define SORT_IPRV
//int main() {
//
//	int a[30000];
//	for (int i = 0; i < 30000; ++i) {
//		a[i] = (int)rand();
//	}
//
//	DWORD start_time, elapsed_time;
//	__asm {
//		RDTSC
//			mov start_time, eax
//	};
//	#ifdef SORT_IPRV 
//		selectsort_iprv<int>(a, getArrayLen(a));
//	#else 
//		selectsort<int>(a, getArrayLen(a));
//	#endif
//
//	__asm {
//		RDTSC
//			sub eax, start_time
//			mov elapsed_time, eax
//	};
//
//	cout << "Time in CPU block: "
//		<< elapsed_time << endl;
//	return 0;
//}
int main() {
	 int a[] = { 1, 1, 2, 3, 4, 5, 6};

	 cout << binary_search(a, 0, getArrayLen(a), 5) << endl;
	 cout << squ_search(a, getArrayLen(a), 5) << endl;
}
