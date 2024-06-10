#include <iostream>
#include "Graph.h"
#include "ReadGraphFile.h"
#include "AlgorithmsIM.h"
#include "AlgorithmsAL.h"

#define MAX_EDGE_WEIGHT 50

using namespace std;

int main()
{
	Graph test_graph(5, 10, false);

	test_graph.generate_random_graph(0.5, 6);

	// ReadGraphFile rgf;

	// Edge* edge_list = rgf.read_graph("MSTgraph2.txt");
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

	// AlgorithmsIM algorithms_im;

	// test_graph.set_is_directed(false);

	// delete[] incidence_matrix;

	// incidence_matrix = test_graph.get_incidence_matrix();

	// for (int i = 0; i < test_graph.vertex_amount; i++)
	// {
	// 	cout << i << ":\t";

	// 	for (int j = 0; j < test_graph.edge_amount; j++)
	// 	{
	// 		cout << incidence_matrix[i][j] << '\t';
	// 	}
		
	// 	cout << '\n';
	// }
	// Vertex* p_mst = algorithms_im.PrimsMST(test_graph.get_incidence_matrix(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);

	// test_graph.set_is_directed(true);
	// Vertex* d_path = algorithms_im.DijkstryPath(test_graph.get_incidence_matrix(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);

	// Vertex* bm_path = algorithms_im.BellmanFordPath(test_graph.get_incidence_matrix(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);

	// for (int i = 0; i < test_graph.get_vertex_amount(); i++)
	// {
	// 	cout << bm_path[i].index << " - " << i << '\t' << bm_path[i].weight << '\n';
	// }

	// algorithms_im.KruskalMST(test_graph.get_incidence_matrix(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);

	// AlgorithmsAL algorithms_al;

	// Vertex* p_mst = algorithms_al.PrimsMST(test_graph.get_adjacency_list(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);

	// algorithms_al.KruskalMST(test_graph.get_adjacency_list(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);

	// test_graph.set_is_directed(true);
	// Vertex* d_path = algorithms_al.DijkstryPath(test_graph.get_adjacency_list(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);

	// Vertex* bm_path = algorithms_al.BellmanFordPath(test_graph.get_adjacency_list(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);

	// for (int i = 0; i < test_graph.get_vertex_amount(); i++)
	// {
	// 	cout << bm_path[i].index << " - " << i << '\t' << bm_path[i].weight << '\n';
	// }

	// delete[] incidence_matrix;
	// delete[] adjacency_list;

	// delete[] p_mst;
	// delete[] d_path;
	// delete[] bm_path;

	return 0;
}