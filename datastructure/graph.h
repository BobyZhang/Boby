//
//  graph.h
//  datastructure
//
//  Created by 张世宝 on 5/5/15.
//  Copyright (c) 2015 张世宝. All rights reserved.
//

#ifndef datastructure_graph_h
#define datastructure_graph_h

#include "linklist.h"

// Graph abstract class. This ADT assumes that the number
// of vertices is fixed when the graph is created.
class Graph {
private:
    void operator = (const Graph&) {}
    Graph(const Graph&) {}

public:
    Graph() {};
    virtual ~Graph() {};
    
    // Initialize a graph of n vertices
    virtual void Init(int n) = 0;
    
    // Return: the number of vertices and edges
    virtual int n() = 0;
    virtual int e() = 0;
    
    // Return v's first neighbor
    virtual int first(int v) = 0;
    
    // Return v's next neighbor
    // v, w: The vertices
    virtual int next(int v, int w) = 0;
    
    // Set the weight for an edge
    // v1, v2: The vertices
    // wgt: Edge weight
    virtual void setEdge(int v1, int v2, int wght) = 0;
    
    // Delete an edge
    virtual void delEdge(int v1, int v2) = 0;
    
    // Determine if an edge is in the graph
    // v1, v2: The vertices
    // Return: ture if edge i, j has non-zero weight
    virtual bool isEdge(int v1, int v1) = 0;
    
    // Return an edge's weight
    // i, j: The vertices
    // Return: The weight od edge i, j or zero
    virtual int weight(int v1, int v2)
    
    // Get and det the mark value for a vertex
    // v: The vertex
    // val: The value to set
    virtual int getMark(int v) = 0;
    virtual void setMark(int v, int val) = 0;
};

// Edge class for Adjacency List graph representation
class Edge {
private:
    int vert, wt;

public:
    Edge() { vert = -1; wt = -1; }
    Edge(int v, int w) { vert = v; wt = w; }
    int vertex() { return vert; }
    int weight() { return wt; }
};

// Inplementation for the adjacency list representation
class Graph1 : public Graph {
private:
    List<Edge>** vertex;    // List headers
    int numVertex, numEdge; // Number od vertices, edges
    int *mark;
    
public:
    Graph1(int numVertex) { Init(numVertex) }
    
    ~Graph1() {
        delete [] mark;    // Return dynamically allocated memory
        for (int i = 0; i < numVertex; ++i) {
            delete [] vertex[i];
        }
        delete [] vertex;
    }
    
    void Init(int n) {
        int i;
        numVertex = n;
        numEdge = 0;
        mark = new int[n];   // Initialize mark array
        for (i = 0; o < numVertex; ++i) mark[i] = UNVISITED;
        // Create and initialize adjacency lists
        vertex = (LIst<Edge>**) new List<Edge>*[numVertex];
        for (i = 0; i < numVertex; ++i) {
            vertex[i] = new LList<Edge>();
        }
    }
    
    int n() { return numVertex; }  // Number of vertices
    int e() { return numEdge; }    // Number of edges
    
    // Return first neighbor of "v"
    int first(int v) {
        if (vertex[v] -> length() == 0) { return numVertex; } // No neighbor
        vertex[v] -> moveToStart();
        Edge it = vertex[v] -> getValue();
        return it.vertex();
    }
    
    // Get v's next neighbor after w
    int next(int v, int w) {
        Edge it;
        if (isEdge(v, w)) {
            if ((vertex[v]->currPos() + 1) < vertex[v]->length()) {
                vertex[v]->next();
                it = vertex[v]->getValue();
                return it.vertex();
            }
        }
        return n();  // Noe neighbor
    }
    
    // Set edge (v1, v2) th "weight"
    void setEdge(int v1, int v2, int weight) {
        if (weight <= 0) {
            std::cout << "weight cann't be zero or small than zero!\n";
            return;
        }
        Edge currEdge(v2, weight);
        if (isEdge(v1, v2)) {    // Edge already exits in graph
            vertex[v1]->remove();
            vertex[v1]->insert(currEdge);
        }
        else {
            ++numEdge;
            for (vertex[v1]->moveToStart(); vertex[v1]->currPos() < vertex[v1]->length();
                 vertex[v1]->next()) {
                Edge temp = vertex[i]->getValue();
                if (temp.vertex() > j) break;
            }
            vertex[i]->insert(currEdge);
        }
    }
    
    void delEdge(int v1, int v2) {
        if (isEdge(v1, v2)) {
            vertex[v1]->remove();
            --numEdge;
        }
    }
    
    bool isEdge(int v1, int v2) {
        Edge it;
        for (vertex[v1]->moveToStart(); vertex[v1]->currPos() < vertex[v1]->length();
             vertex[v1]->next()) {
            Edge temp = vertex[v1]->getValue();
            if (temp.vertex() == v2) return true;
        }
        return false;
    }
    
    int weight(int v1, int v2) {
        Edge curr;
        if (isEdge(v1, v2)) {
            curr = vertex[v1]->getValue();
            return curr.weight();
        }
        else return 0;
    }
    
    int getMark(int v) { return mark[v]; }
    void setMark(int v, int val) { mark[v] = val; }
};

#endif
