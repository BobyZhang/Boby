#pragma once

#include "graph.h"
#include "linkqueue.h"

void DFS(Graph* G, int v) {
	G->setMark(v, VISITED);
	for (int w = G->first(v); w < G->n(); w = G->next(v, w)) {
		if (G->getMark(w) == UNVISITED) {
			DFS(G, w);
		}
	}
	// do something
}

void BFS(Graph* G, int start, Queue<int>* Q) {
	// v, w: The vertices
	int v, w;
	Q->enqueue(start);
	G->setMark(start, VISITED);
	while (Q->length() != 0) {
		v = Q->dequeue();
		// do something
		for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
			if (G->getMark(w) == UNVISITED) {
				G->setMark(w, VISITED);
				Q->enqueue(w);
			}
		}
	}
}

// Topological Sort: DFS
void topsort(Graph* G) {
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

void tophelp(Graph* G, int v) {  // Process vertex v
	G->setMark(v, VISITED);
	for (int w = G->first(v); w < G->n(); w = G->next(v, w)) {
		if (G->getMark(w) == UNVISITED) {
			tophelp(G, w);
		}
	}
	std::cout << v << "\n";
}

// Topological sort: Queue
void topsortQ(Graph* G, Queue<int>* Q) {
	int count[G->n()]; //TODO
	int v, w;
	for (v = 0; v < G->n(); ++v) count[v] = 0; // Init

	// Count prereq
	for (v = 0; v < G->n(); ++v) {
		for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
			++count[w];
		}
	}

	for (v = 0; v < G->n(); ++v) {
		if (count[v] == 0) {
			Q->enqueue(v);
		}
	}

	// Process the vertices
	while (Q->length() != 0) {
		v = Q->dequeue();
		// cout
		for (w = G->first(v); w < G->n(); w = G->next(v, w)) {
			--count[w];
			if (count[w] == 0) Q->enqueue(w);
		}
	}
}