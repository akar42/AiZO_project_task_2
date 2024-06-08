#pragma once
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>

#ifndef MAX_ENGE_WEIGHT

#define MAX_EDGE_WEIGHT 100

#endif

struct Vertex
{
	int index;
	int weight;
	// Vertex* next;
};

struct Edge
{
	int u;
	int v;
	int weight;
};

class Graph
{
public:
	int** incidence_matrix = nullptr;
	Vertex** adjacency_list = nullptr;

	int edge_amount = -1;
	int vertex_amount = -1;
	bool directed = false;

	Graph(int edge_amount, int vertex_amount, bool directed);

	int** get_incidence_matrix();

	Vertex** get_adjacency_list();

	void generate_random_graph(double dencity, int new_vertex_amount);

	void write_graph_from_edge_list(Edge* edge_list, int new_vertex_amount, int new_edge_amount);

	~Graph();
};