
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
int main() {
	 // 生成有7个节点的树 a
	Graph1 a(6);
	// 分别设置边，第一个参数为节点v1，第二个参数为节点v2，第三个参数为边的权重
	a.setEdge(0, 2, 1);
	a.setEdge(0, 4, 1);
	a.setEdge(4, 5, 1);
	a.setEdge(2, 1, 1);
	a.setEdge(2, 3, 1);
	a.setEdge(2, 5, 1);
	a.setEdge(1, 5, 1);
	a.setEdge(3, 5, 1);

	cout << "DFS: ";
	// 对树 a 的节点，进行深度优先搜索来遍历	
	DFS(&a, 0);
	cout << endl << endl;

	// 用队列实现的广度优先搜索，所以先申请队列
	LQueue<int> Q;
	cout << "BFS: ";
	// 对输 a 的节点，进行广度优先搜索来遍历
	// 第一个参数为 待遍历的树，第二个参数为作为起点的节点，第三个参数为辅助搜索的队列
	BFS(&a, 0, &Q);
	cout << endl << endl;

	// 生成有7个节点的书 b
	Graph1 b(7);
	// 生成课本图11.14的图
	b.setEdge(0, 1, 1);
	b.setEdge(0, 2, 1);
	b.setEdge(1, 5, 1);
	b.setEdge(1, 4, 1);
	b.setEdge(1, 3, 1);
	b.setEdge(2, 3, 1);
	b.setEdge(3, 4, 1);
	b.setEdge(4, 6, 1);

	cout << "TS: ";
	// 对图b进行基于队列实现的，拓扑排序
	topsortQ(&b, &Q);
	cout << endl << endl;
	return 0;
}
