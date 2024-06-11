#pragma once
#include "DataStructures.h"

class AlgorithmsIM
{
public:
	Vertex* PrimsMST(int** incidence_matrix, int vertex_amount, int edge_amount, int start_vertex);
	Vertex* KruskalMST(int** incidence_matrix, int vertex_amount, int edge_amount);
	Vertex* DijkstraPath(int** incidence_matrix, int vertex_amount, int edge_amount, int start_vertex);
	Vertex* BellmanFordPath(int** incidence_matrix, int vertex_amount, int edge_amount, int start_vertex);
};