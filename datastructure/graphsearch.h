#pragma once

#include "graph.h"
#include "linkqueue.h"
#include "heap.h"

// G�� ������������
// v�� ��ǰ�ڵ�
void DFS(Graph1* G, int v) {
	// ���������Ľڵ㣬��һ�����
	G->setMark(v, VISITED);
	// �����ǰ���
	std::cout << v << ' ';
	// ������ǰ�����ӽڵ�
	for (int w = G->first(v); w < G->n(); w = G->next(v, w)) {
		// ����ýڵ�δ�����ʹ������еݹ�
		if (G->getMark(w) == UNVISITED) {
			DFS(G, w);
		}
	}
}

// ���ڶ���ʵ�ֵĹ����������
// G: ������������
// start: ��������ʼ�Ľڵ�
// Q: ���������������ʵ��ʱ�õĶ���
void BFS(Graph1* G, int start, LQueue<int>* Q) {
	// ���������нڵ���Ϊδ����
	for (int i = 0; i < G->n(); ++i) {
		G->setMark(i, UNVISITED);  // Init
	}
	// v, w �ֱ������������������ڵ�
	int v, w;
	// ����ʼ�Ľڵ�����������
	Q->enqueue(start);
	// ��ǿ�ʼ�ڵ�Ϊ�ѷ��ʹ�
	G->setMark(start, VISITED);
	// �����в�Ϊ��ʱ��һֱѭ��
	while (Q->length() != 0) {
		// �������еĵ�һ���ڵ��ó����������ڽڵ� v �С�
		v = Q->dequeue();
		// �������ڵ�
		std::cout << v << ' ';
		// �����ڵ� v �������ӽڵ�
		for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
			// �������ӽڵ�û�б����ʹ���������Ƶ����е�ĩβ
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

// ���ڶ���ʵ�ֵ���������
// G: �������
// Q: ����ʵ����������Ķ���
void topsortQ(Graph1* G, Queue<int>* Q) {
	// ����һ����СΪ�����ܽ���������������ָ�룬��������
	int *count;
	count = new int[G->n()];

	// ���� v, w ��������ڵ�
	int v, w;

	// ��ʼ������������
	for (v = 0; v < G->n(); ++v) count[v] = 0; // Init

	// ͳ��ÿ���ڵ��ǰ��������
	for (v = 0; v < G->n(); ++v) {
		for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
			++count[w];
		}
	}

	// ��û��ǰ���ڵ�Ľڵ㣬Ҳ�����׽ڵ��������
	for (v = 0; v < G->n(); ++v) {
		if (count[v] == 0) {
			Q->enqueue(v);
		}
	}

	// �����в�Ϊ����һ�½��д�ѭ��
	while (Q->length() != 0) {
		// �������еĵ�һ���ڵ�Ӷ�����ȡ��
		v = Q->dequeue();
		// ����˽ڵ�
		cout << v << ' ';
		// �����˽ڵ�������ӽڵ�
		for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
			// ����Щ�ӽڵ��ǰ���ڵ�����һ
			--count[w];
			// �������ӽڵ����㣬��������ǰ���ڵ㶼�����ʹ����򽫴��ӽڵ�������е�β��
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
  ����A������������  A            B           B    U            U    G             G                           
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