#include <iostream>
#include "Graph.h"
#include "ReadGraphFile.h"
#include "AlgorithmsIM.h"
#include "AlgorithmsAL.h"
#include <chrono>

using namespace std;

int main()
{
	Graph test_graph(5, 10, true);

	// cout << "Graph generation\n";

	// std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
	// test_graph.generate_random_graph(0.99, 5);
	// std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

	// std::chrono::duration<double, std::milli> delta = end - start;

	// cout << "Durations: " << delta.count() << " ms\n";

	// ReadGraphFile rgf;

	// Edge* edge_list = rgf.read_graph("PATHgraph2.txt");
	// int edge_amount = rgf.get_edges_amount();
	// int vertex_amount = rgf.get_vertex_amount();

	// test_graph.write_graph_from_edge_list(edge_list, vertex_amount, edge_amount);

	// delete[] edge_list;

	// cout << "V = " << test_graph.vertex_amount << " E = " << test_graph.edge_amount << '\n';

	// int** incidence_matrix = test_graph.get_incidence_matrix();

	// for (int i = 0; i < test_graph.vertex_amount; i++)
	// {
	// 	cout << i << ":\t";

	// 	for (int j = 0; j < test_graph.edge_amount; j++)
	// 	{
	// 		cout << incidence_matrix[i][j] << '\t';
	// 	}
		
	// 	cout << '\n';
	// }

	// Vertex** adjacency_list = test_graph.get_adjacency_list();

	// for (int i = 0; i < test_graph.vertex_amount; i++)
	// {
	// 	cout << i << ':' << '\t';

	// 	int adj_size = 0;

	// 	while (adjacency_list[i][adj_size].index != -1)
	// 		adj_size++;

	// 	for (int j = 0; j < adj_size; j++)
	// 	{
	// 		cout << adjacency_list[i][j].index << "(" << adjacency_list[i][j].weight << ")" <<'\t';
	// 	}

	// 	cout << '\n';
	// }

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
	// edge_list = test_graph.get_edge_list();
	// for (int i = 0; i < test_graph.get_edge_amount(); i++)
	// {
	// 	cout << edge_list[i].u << "->" << edge_list[i].v << " :\t" << edge_list[i].weight << '\n';
	// }
	// delete[] edge_list;

	// test_graph.set_is_directed(false);
	// cout << "Start\n";
	// start = std::chrono::high_resolution_clock::now();
	// Vertex* p_mst = algorithms_im.PrimsMST(test_graph.get_incidence_matrix(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);
	// Vertex* k_mst = algorithms_im.KruskalMST(test_graph.get_incidence_matrix(), test_graph.get_vertex_amount(), test_graph.get_edge_amount());
	// Vertex* d_path = algorithms_im.DijkstryPath(test_graph.get_incidence_matrix(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 2);
	// Vertex* bm_path = algorithms_im.BellmanFordPath(test_graph.get_incidence_matrix(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);
	
	// end = std::chrono::high_resolution_clock::now();

	// delta = end - start;

	// cout << "Durations: " << delta.count() << " ms\n";

	// test_graph.set_is_directed(true);


	// for (int i = 0; i < test_graph.get_vertex_amount(); i++)
	// {
	// 	cout << bm_path[i].index << " - " << i << '\t' << bm_path[i].weight << '\n';
	// }


	// AlgorithmsAL algorithms_al;

	// Vertex* p_mst = algorithms_al.PrimsMST(test_graph.get_adjacency_list(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);

	// Vertex* k_mst = algorithms_al.KruskalMST(test_graph.get_adjacency_list(), test_graph.get_vertex_amount(), test_graph.get_edge_amount());

	// test_graph.set_is_directed(true);
	// Vertex* d_path = algorithms_al.DijkstryPath(test_graph.get_adjacency_list(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);

	// Vertex* bm_path = algorithms_al.BellmanFordPath(test_graph.get_adjacency_list(), test_graph.get_vertex_amount(), test_graph.get_edge_amount(), 0);

	// for (int i = 0; i < test_graph.get_vertex_amount(); i++)
	// {
	// 	cout << d_path[i].index << " - " << i << '\t' << d_path[i].weight << '\n';
	// }

	// delete[] incidence_matrix;
	// delete[] adjacency_list;

	// delete[] p_mst;
	// delete[] k_mst;
	// delete[] d_path;
	// delete[] bm_path;

	return 0;
}