#include <iostream>
#include "Graph.h"
#include "ReadGraphFile.h"

#define MAX_EDGE_WEIGHT 50

using namespace std;

int main()
{
	Graph test_graph(5, 10, false);

	test_graph.generate_random_graph(1, 10);

	// ReadGraphFile rgf;

	// Edge* edge_list = rgf.read_graph("graph1.txt");
	// int edge_amount = rgf.get_edges_amount();
	// int vertex_amount = rgf.get_vertex_amount();

	// test_graph.write_graph_from_edge_list(edge_list, vertex_amount, edge_amount);

	// delete[] edge_list;

	cout << "V = " << test_graph.vertex_amount << " E = " << test_graph.edge_amount << '\n';

	int** incidence_matrix = test_graph.get_incidence_matrix();

	for (int i = 0; i < test_graph.vertex_amount; i++)
	{
		cout << i << ":\t";

		for (int j = 0; j < test_graph.edge_amount; j++)
		{
			cout << incidence_matrix[i][j] << '\t';
		}
		
		cout << '\n';
	}

	Vertex** adjacency_list = test_graph.get_adjacency_list();

	for (int i = 0; i < test_graph.vertex_amount; i++)
	{
		cout << i << ':' << '\t';

		int adj_size = 0;

		while (adjacency_list[i][adj_size].index != -1)
			adj_size++;

		for (int j = 0; j < adj_size; j++)
		{
			cout << adjacency_list[i][j].index << "(" << adjacency_list[i][j].weight << ")" <<'\t';
		}

		cout << '\n';
	}

	return 0;
}