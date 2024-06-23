#include <iostream>
#include "Graph.h"
#include "ReadGraphFile.h"
#include "AlgorithmsIM.h"
#include "AlgorithmsAL.h"
#include <chrono>

using namespace std;

int main()
{
	int main_menu = 1;
	int problem_chooser = 0;
	int representation_chooser = 1;
	string filename;
	ReadGraphFile rgf;

	Graph graph(0, 0, true);
	int edge_amount = 0;
	int vertex_amount = 0;
	Edge *edge_list = nullptr;
	int **incidence_matrix = nullptr;
	Vertex **adjacency_list = nullptr;
	double dencity;

	AlgorithmsAL alg_al;
	AlgorithmsIM  alg_im;

	while (main_menu != 0)
	{
		main_menu = 0;

		cout << "1. Read graph from file" << '\n';
		cout << "2. Generate random spanning graph" << '\n';
		cout << "3. Show graph (incidence matrix and adjacency lists)" << '\n';
		cout << "4. Choose problem to resolve" << '\n';
		cout << "0.(default) - Exit program" << '\n';

		cin >> main_menu;

		switch (main_menu)
		{
		case 1:
			cout << '\n' <<"Enter filename" << '\n';
			cout << "> ";

			cin >> filename;

			edge_list = rgf.read_graph(filename);
			edge_amount = rgf.get_edges_amount();
			vertex_amount = rgf.get_vertex_amount();

			graph.write_graph_from_edge_list(edge_list, vertex_amount, edge_amount);
			
			cout << '\n';

			delete[] edge_list;
			break;
		case 2:
			cout << '\n' << "Enter number of verticies" << '\n';
			cout << "> ";

			cin >> vertex_amount;

			cout << "Enter edges dencity" << '\n';
			cout << "> ";

			cin >> dencity;

			graph.generate_random_graph(dencity, vertex_amount);

			edge_amount = graph.get_edge_amount();
			
			cout << '\n';

			break;
		case 3:
			if (graph.get_adjacency_list() == nullptr || graph.get_incidence_matrix() == nullptr)
			{
				cout << '\n' << "There is no graph to show. Please provide it from file or generate" << "\n\n";
				break;
			}

			incidence_matrix = graph.get_incidence_matrix();
			adjacency_list = graph.get_adjacency_list();

			vertex_amount = graph.get_vertex_amount();
			edge_amount = graph.get_edge_amount();

			cout << '\n' << "Incidence matrix:" << '\n';

			cout << "v\\e\t|";

			for (int e = 0; e < edge_amount; e++)
			{
				cout << e << '\t';
			}

			cout << '\n';

			for (int i = 0; i < 8*(edge_amount + 1); i++)
			{
				cout << '-';
			}

			cout << '\n';

			for (int v = 0; v < vertex_amount; v++)
			{
				cout << v << "\t|";

				for (int e = 0; e < edge_amount; e++)
				{
					cout << incidence_matrix[v][e] << '\t';
				}

				cout << '\n';
			}

			cout << '\n' << "Adjacency lists:" << '\n';

			cout << "v\t|Adj[v]\n";

			for (int i = 0; i < 8*(vertex_amount + 1); i++)
			{
				cout << '-';
			}

			cout << '\n';

			for (int v = 0; v < vertex_amount; v++)
			{
				cout << v << "\t|";

				for(int e_id = 0; adjacency_list[v][e_id].index != -1; e_id++)
				{
					cout << adjacency_list[v][e_id].index << "(" << adjacency_list[v][e_id].weight << ")\t";
				}

				cout << '\n';
			}

			cout << '\n';
			break;
		case 4:
			problem_chooser = 1;
			cout << '\n' << "1. MST - Minimal spanning tree (Saved graph is interpreted as undirected)" << '\n';
			cout << "2. Shortest path (Saved graph is interpreted as directed)" << '\n';
			cout << "0. (default) - Go back" << '\n';

			cin >> problem_chooser;

			if (problem_chooser == 0) break;

			representation_chooser = 1;
			cout << '\n' << "Choose graph representation" << '\n';
			cout << "1.(default) Incidence matrix" << '\n';
			cout << "2. Adjacency lists" << '\n';

			cin >> representation_chooser;

			if (problem_chooser == 1)
			{
				graph.set_is_directed(false);
				incidence_matrix = graph.get_incidence_matrix();
				adjacency_list = graph.get_adjacency_list();
				Vertex* mst;
				int mst_weight = 0;

				int algorithm = 1;

				cout << '\n' << "Choose an algorithm" << '\n';
				cout << "1.(default) Prim's algorithm" << '\n';
				cout << "2. Kruskal's algorithm" << '\n';

				cin >> algorithm;

				if (algorithm == 1 && representation_chooser == 1)
				{
					mst = alg_im.PrimsMST(incidence_matrix, vertex_amount, edge_amount, 0);
				}
				else if (algorithm == 1 && representation_chooser == 2)
				{
					mst = alg_al.PrimsMST(adjacency_list, vertex_amount, edge_amount, 0);
				}
				else if (algorithm == 2 && representation_chooser == 1)
				{
					mst = alg_im.KruskalMST(incidence_matrix, vertex_amount, edge_amount);
				}
				else if (algorithm == 2 && representation_chooser == 2)
				{
					mst = alg_al.KruskalMST(adjacency_list, vertex_amount, edge_amount);
				}

				cout << "Edges of MST:" << '\n';

				for (int i = 0; i < vertex_amount; i++)
				{
					cout << mst[i].index << " - " << i << ": " << mst[i].weight << '\n';
					mst_weight += mst[i].weight;
				}

				cout << "Weight of MST is: " << mst_weight << '\n';
				delete[] mst;
			}
			else
			{
				graph.set_is_directed(true);
				incidence_matrix = graph.get_incidence_matrix();
				adjacency_list = graph.get_adjacency_list();
				Vertex* ancestor_list;

				int start_vertex = 0;
				int last_vertex = 0;
				int shortest_path_length = 1;
				int* shortest_path = new int[shortest_path_length];

				int algorithm = -1;

				cout << '\n' << "Choose an algorithm" << '\n';
				cout << "1.(default) Dijkstra's algorithm" << '\n';
				cout << "2. Bellman-Ford algorithm" << '\n';

				cin >> algorithm;

				cout << '\n' << "Start vertex: ";
				cin >> start_vertex;
				cout << "Last vertex: ";
				cin >> last_vertex;

				if (algorithm == 1 && representation_chooser == 1)
				{
					ancestor_list = alg_im.DijkstraPath(incidence_matrix, vertex_amount, edge_amount, start_vertex);
				}
				else if (algorithm == 1 && representation_chooser == 2)
				{
					ancestor_list = alg_al.DijkstraPath(adjacency_list, vertex_amount, edge_amount, start_vertex);
				}
				else if (algorithm == 2 && representation_chooser == 1)
				{
					ancestor_list = alg_im.BellmanFordPath(incidence_matrix, vertex_amount, edge_amount, start_vertex);
				}
				else if (algorithm == 2 && representation_chooser == 2)
				{
					ancestor_list = alg_al.BellmanFordPath(adjacency_list, vertex_amount, edge_amount, start_vertex);
				}

				for (int i = 0; i < vertex_amount; i++)
				{
					cout << ancestor_list[i].index << " - " << i << " : " << ancestor_list[i].weight << '\n';
				}

				
				int i = last_vertex;
				bool exist = true;
				while (i != start_vertex)
				{
					if (ancestor_list[i].weight == 200)
					{
						exist = false;
						break;
					}
					shortest_path[shortest_path_length - 1] = i;
					shortest_path_length++;
					int* tmp = new int[shortest_path_length];

					for (int j = 0; j < shortest_path_length - 1; j++)
					{
						tmp[j] = shortest_path[j];
					}

					delete[] shortest_path;
					shortest_path = tmp;

					i = ancestor_list[i].index;
				}
				shortest_path[shortest_path_length - 1] = start_vertex;

				if (exist) {
					cout << "Shortest path: ";
					for (int j = shortest_path_length - 1; j >= 0; j--)
					{
						cout << shortest_path[j] << '\t';
					}
					cout << '\n';

					cout << "Path's weight: " << ancestor_list[last_vertex].weight << '\n';
				}
				else
				{
					cout << "Path does not exist" << '\n';
				}
				delete[] ancestor_list;
				delete[] shortest_path;
			}

			cout << '\n';

			break;
		default:
			break;
		}
	}

	delete[] incidence_matrix;
	delete[] adjacency_list;
	return 0;
}