#pragma once
#include "DataStructures.h"

class AlgorithmsAL
{
public:
	Vertex* PrimsMST(Vertex** adjacency_list, int vertex_amount, int edge_amount, int start_vertex);
	Vertex* KruskalMST(Vertex** adjacency_list, int vertex_amount, int edge_amount);
	Vertex* DijkstraPath(Vertex** adjacency_list, int vertex_amount, int edge_amount, int start_vertex);
	Vertex* BellmanFordPath(Vertex** adjacency_list, int vertex_amount, int edge_amount, int start_vertex);
};