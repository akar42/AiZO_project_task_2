#pragma once
#include "Graph.h"

class VertexPriorityQueue
{
private:
	Vertex* min_heap = nullptr;
	int size = 0;
	void adjustForHeap(int node_id, int heap_length);
public:
	void add_vertex(Vertex v);
	Vertex get_min();
	void pop();
	void change_key(int vertex_index, int new_key);
	bool is_in_queue(int vertex_index);
	bool is_empty();
	~VertexPriorityQueue();
};

class DisjointSets {
public:
    int* parent;
    int* rank;
    int n;

    DisjointSets(int n);

    int find(int u);

    void merge(int x, int y);

    ~DisjointSets();
};

void mergeEdgeArrays(Edge* arr, int l, int m, int r);

void mergeSortEdges(Edge* arr, int l, int r);