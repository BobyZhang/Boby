
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
#include "linkqueue.h"
#include "graphsearch.h"

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

//int main() {
//	 // ������7���ڵ���� a
//	Graph1 a(6);
//	// �ֱ����ñߣ���һ������Ϊ�ڵ�v1���ڶ�������Ϊ�ڵ�v2������������Ϊ�ߵ�Ȩ��
//	a.setEdge(0, 2, 1);
//	a.setEdge(0, 4, 1);
//	a.setEdge(4, 5, 1);
//	a.setEdge(2, 1, 1);
//	a.setEdge(2, 3, 1);
//	a.setEdge(2, 5, 1);
//	a.setEdge(1, 5, 1);
//	a.setEdge(3, 5, 1);
//
//	cout << "DFS: ";
//	// ���� a �Ľڵ㣬���������������������	
//	DFS(&a, 0);
//	cout << endl << endl;
//
//	// �ö���ʵ�ֵĹ�������������������������
//	LQueue<int> Q;
//	cout << "BFS: ";
//	// ���� a �Ľڵ㣬���й����������������
//	// ��һ������Ϊ �������������ڶ�������Ϊ��Ϊ���Ľڵ㣬����������Ϊ���������Ķ���
//	BFS(&a, 0, &Q);
//	cout << endl << endl;
//
//	// ������7���ڵ���� b
//	Graph1 b(7);
//	// ���ɿα�ͼ11.14��ͼ
//	b.setEdge(0, 1, 1);
//	b.setEdge(0, 2, 1);
//	b.setEdge(1, 5, 1);
//	b.setEdge(1, 4, 1);
//	b.setEdge(1, 3, 1);
//	b.setEdge(2, 3, 1);
//	b.setEdge(3, 4, 1);
//	b.setEdge(4, 6, 1);
//
//	cout << "TS: ";
//	// ��ͼb���л��ڶ���ʵ�ֵģ���������
//	topsortQ(&b, &Q);
//	cout << endl << endl;
//	return 0;
//}

int main() {
	
    // ���ɿα�ͼ11.16��ͼ
    Graph1 g(5);
    g.setEdge(0, 1, 10);
    g.setEdge(0, 2, 3);
    g.setEdge(0, 3, 20);
    g.setEdge(1, 3, 5);
    g.setEdge(2, 1, 2);
    g.setEdge(2, 4, 15);
    g.setEdge(3, 4, 11);

    int* D = new int[5];
    D[0] = 0;
    for (int i = 1; i < 5; ++i) D[i] = INFINITY;

    //Dijkstra(&g, D, 0);
    Dijkstraheap(&g, D, 0);

    for (int i = 0; i < 5; ++i) {
        cout << D[i] << " ";
    }
    return 0;
}