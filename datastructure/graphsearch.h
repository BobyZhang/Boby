#pragma once

#include "graph.h"
#include "linkqueue.h"
#include "heap.h"

// G： 进行搜索的树
// v： 当前节点
void DFS(Graph1* G, int v) {
	// 将遍历到的节点，做一个标记
	G->setMark(v, VISITED);
	// 输出当前结点
	std::cout << v << ' ';
	// 遍历当前结点的子节点
	for (int w = G->first(v); w < G->n(); w = G->next(v, w)) {
		// 如果该节点未被访问过，进行递归
		if (G->getMark(w) == UNVISITED) {
			DFS(G, w);
		}
	}
}

// 基于队列实现的广度优先搜索
// G: 进行搜索的树
// start: 搜索树开始的节点
// Q: 辅助广度优先搜索实现时用的队列
void BFS(Graph1* G, int start, LQueue<int>* Q) {
	// 对树的所有节点标记为未访问
	for (int i = 0; i < G->n(); ++i) {
		G->setMark(i, UNVISITED);  // Init
	}
	// v, w 分别用来保存树的两个节点
	int v, w;
	// 将开始的节点塞到队列中
	Q->enqueue(start);
	// 标记开始节点为已访问过
	G->setMark(start, VISITED);
	// 当队列不为空时，一直循环
	while (Q->length() != 0) {
		// 将队列中的第一个节点拿出，并保存在节点 v 中。
		v = Q->dequeue();
		// 输出这个节点
		std::cout << v << ' ';
		// 遍历节点 v 的所有子节点
		for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
			// 如果这个子节点没有被访问过，则把它推到队列的末尾
			if (G->getMark(w) == UNVISITED) {
				G->setMark(w, VISITED);
				Q->enqueue(w);
			}
		}
	}
}

void tophelp(Graph1* G, int v);
// Topological Sort: DFS
void topsort(Graph1* G) {
	int i;
	for (i = 0; i < G->n(); ++i) {
		G->setMark(i, UNVISITED);  // Init
	}
	for (i = 0; i < G->n(); ++i) {
		if (G->getMark(i) == UNVISITED) {
			tophelp(G, i);
		}
	}
}

void tophelp(Graph1* G, int v) {  // Process vertex v
	G->setMark(v, VISITED);
	for (int w = G->first(v); w < G->n(); w = G->next(v, w)) {
		if (G->getMark(w) == UNVISITED) {
			tophelp(G, w);
		}
	}
	std::cout << v << "\n";
}

// 基于队列实现的拓扑排序
// G: 排序的树
// Q: 辅助实现拓扑排序的队列
void topsortQ(Graph1* G, Queue<int>* Q) {
	// 申明一个大小为树的总结点数的整型数组的指针，用来计数
	int *count;
	count = new int[G->n()];

	// 申明 v, w 用来保存节点
	int v, w;

	// 初始化技术的数组
	for (v = 0; v < G->n(); ++v) count[v] = 0; // Init

	// 统计每个节点的前驱结点个数
	for (v = 0; v < G->n(); ++v) {
		for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
			++count[w];
		}
	}

	// 将没有前驱节点的节点，也就是首节点推入队列
	for (v = 0; v < G->n(); ++v) {
		if (count[v] == 0) {
			Q->enqueue(v);
		}
	}

	// 当队列不为空是一致进行次循环
	while (Q->length() != 0) {
		// 将队列中的第一个节点从队列中取出
		v = Q->dequeue();
		// 输出此节点
		cout << v << ' ';
		// 遍历此节点的所有子节点
		for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
			// 将这些子节点的前驱节点数减一
			--count[w];
			// 如果这个子节点满足，它的所有前驱节点都被访问过，则将此子节点推入队列的尾部
			if (count[w] == 0) Q->enqueue(w);
		}
	}
}

int minVertex(Graph1* G, int* D);
// Compute shortest path distances from "s".
// Return these distances in "D".
void Dijkstra(Graph1* G, int* D, int s) {
    int i, v, w;
    // Process the vertices
    for (i = 0; i < G->n(); ++i) {
        v = minVertex(G, D);
        if (D[v] == INFINITY) return;  // Unreachable vertices
        G->setMark(v, VISITED);
        for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
            if (D[w] > (D[v] + G->weight(v, w))) {
                D[w] = D[v] + G->weight(v, w);
            }
        }
    }
}

int minVertex(Graph1* G, int* D) {
    int i, v = -1;
    // Initialize v to some unvisitied vertex
    for (i = 0; i < G->n(); ++i) {
        if (G->getMark(i) == UNVISITED) {
            v = i;
            break;
        }
    }
    // Now find smallest D value
    for (++i; i < G->n(); ++i) {
        if ((G->getMark(i) == UNVISITED) && (D[i] < D[v])) {
            v = i;
        }
    }
    return v;
}



/****************************************************************************************

             A                   B B B B B       U              U       G G G G G               
            A A                  B         B     U              U     G           G                
           A   A                 B          B    U              U    G                             
          A     A                B          B    U              U   G                       
         A       A               B B B B B B     U              U   G                
        A A A A A A              B          B    U              U   G         G G G G         
       A           A             B           B   U              U   G             G                                         
  　　A　　　　　　  A            B           B    U            U    G             G                           
     A               A           B          B      U         U       G           G             
    A                 A          B B B B B B         U U U U           G G G G G     

*****************************************************************************************/
class DijkElem {
public:
    int vertex, distance;
    DijkElem() { vertex = -1; distance = -1; }
    DijkElem(int v, int d) { vertex = v; distance = d; }
};
// Dijkstra's shortest paths algorithm with priority queue
void Dijkstraheap(Graph1* G, int* D, int s) {
    int i, v, w;         // v is current vertex
    DijkElem temp;       //
    int length = G->e();
    DijkElem* E = new DijkElem[length];  // Heap array with lots of space

    temp.distance = 0;
    temp.vertex = s;
    E[0] = temp;         // Initialize heap array
    heap<DijkElem> H(E, 1, G->e());

    // Now, get distances
    for (i = 0; i < G->n(); ++i) {
        do {
            if (H.size() == 0) return;     // Nothing to remove
            temp = H.removefirst();
            v = temp.vertex;
        } while (G->getMark(v) == VISITED);

        G->setMark(v, VISITED);
        if (D[v] == INFINITY) return;      // Unreachable vertices
        for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
            if (D[w] > D[v] + G->weight(v, w)) {
                D[w] = D[v] + G->weight(v, w);
                temp.distance = D[w];
                temp.vertex = w;
                H.insert(temp);          // Insert new distance in hea
            }
        }
    }
}