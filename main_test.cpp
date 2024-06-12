#include <iostream>
#include "Graph.h"
#include "ReadGraphFile.h"
#include "AlgorithmsIM.h"
#include "AlgorithmsAL.h"
#include <chrono>
#include <fstream>

using namespace std;

int main()
{
	Graph graph(0, 0, true);

	AlgorithmsAL alg_al;
	AlgorithmsIM alg_im;

	ofstream fout;

	Vertex **adjacency_list = nullptr;
	int **incidencde_matrix = nullptr;
	int edge_amount = 0;
	int vertex_amount = 0;

	Vertex* output = nullptr;

	int vertecies[] = {10, 15, 30, 60, 125, 250, 500};
	int vertecies_length = 7;

	double dencities[] = {0.25, 0.5, 0.99};
	int dencities_length = 3;

	int number_of_iterations = 25;

	fout.open("results2.csv");

	if (fout.is_open())
	{
		fout << "All in milliseconds, ";
		fout << "DijkstraPATH - AL, BellmanFordPATH - AL, DijkstraPATH - IM, BellmanFordPATH - IM, PrimsMST - AL, KruskalMST - AL, PrimMST - IM, KruskalMST - IM" << '\n';

		for (int i = 0; i < dencities_length; i++)
		{
			fout << "Dencity:," << dencities[i] << "\n";

			for (int j = 0; j < vertecies_length; j++)
			{
				fout << "Vertecies:," << vertecies[j] << '\n';

				for (int k = 0; k < number_of_iterations; k++)
				{
					cout << "Graph - generation" << '\n';
					graph.set_is_directed(true);
					graph.generate_random_graph(dencities[i], vertecies[j]);

					adjacency_list = graph.get_adjacency_list();
					incidencde_matrix = graph.get_incidence_matrix();
					vertex_amount = graph.get_vertex_amount();
					edge_amount = graph.get_edge_amount();

					// Shortest path
					cout << "Shortest path" << '\n';
					std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
					output = alg_al.DijkstraPath(adjacency_list, vertex_amount, edge_amount, 0);
					std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();

					std::chrono::duration<double, std::milli> delta = end - start;
					fout << ',' <<delta.count() << ',';

					delete[] output;

					start = std::chrono::high_resolution_clock::now();
					output = alg_al.BellmanFordPath(adjacency_list, vertex_amount, edge_amount, 0);
					end = std::chrono::high_resolution_clock::now();

					delta = end - start;
					fout << delta.count() << ',';

					delete[] output;
					
					start = std::chrono::high_resolution_clock::now();
					output = alg_im.DijkstraPath(incidencde_matrix, vertex_amount, edge_amount, 0);
					end = std::chrono::high_resolution_clock::now();

					delta = end - start;
					fout << delta.count() << ',';

					delete[] output;
					
					start = std::chrono::high_resolution_clock::now();
					output = alg_im.BellmanFordPath(incidencde_matrix, vertex_amount, edge_amount, 0);
					end = std::chrono::high_resolution_clock::now();

					delta = end - start;
					fout << delta.count() << ',';

					delete[] output;
					
					// MST
					cout << "MST" << '\n';
					graph.set_is_directed(false);
					// graph.generate_random_graph(dencities[i], vertecies[j]);

					delete[] adjacency_list;
					delete[] incidencde_matrix;

					adjacency_list = graph.get_adjacency_list();
					incidencde_matrix = graph.get_incidence_matrix();
					vertex_amount = graph.get_vertex_amount();
					edge_amount = graph.get_edge_amount();

					start = std::chrono::high_resolution_clock::now();
					output = alg_al.PrimsMST(adjacency_list, vertex_amount, edge_amount, 0);
					end = std::chrono::high_resolution_clock::now();

					delta = end - start;
					fout << delta.count() << ',';

					delete[] output;

					start = std::chrono::high_resolution_clock::now();
					output = alg_al.KruskalMST(adjacency_list, vertex_amount, edge_amount);
					end = std::chrono::high_resolution_clock::now();

					delta = end - start;
					fout << delta.count() << ',';

					delete[] output;

					start = std::chrono::high_resolution_clock::now();
					output = alg_im.PrimsMST(incidencde_matrix, vertex_amount, edge_amount, 0);
					end = std::chrono::high_resolution_clock::now();

					delta = end - start;
					fout << delta.count() << ',';

					delete[] output;

					start = std::chrono::high_resolution_clock::now();
					output = alg_im.KruskalMST(incidencde_matrix, vertex_amount, edge_amount);
					end = std::chrono::high_resolution_clock::now();

					delta = end - start;
					fout << delta.count() << '\n';

					delete[] output;
					delete[] adjacency_list;
					delete[] incidencde_matrix;
				}
			}

		}
	}

	fout.close();

	return 0;
}