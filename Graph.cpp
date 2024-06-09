#include "Graph.h"

Graph::Graph(int edge_amount, int vertex_amount, bool directed)
{
	std::cout << MAX_EDGE_WEIGHT << '\n';
	this->edge_amount = edge_amount;
	this->vertex_amount = vertex_amount;
	this->directed = directed;
}

int **Graph::get_incidence_matrix()
{
	if (this->incidence_matrix == nullptr)
	{
		return nullptr;
	}
	else
	{
		int **incidence_matrix_copy = new int *[this->vertex_amount];

		for (int i = 0; i < this->vertex_amount; i++)
		{
			incidence_matrix_copy[i] = new int[this->edge_amount];
			std::copy(this->incidence_matrix[i], this->incidence_matrix[i] + this->edge_amount, incidence_matrix_copy[i]);
		}

		return incidence_matrix_copy;
	}
}

Vertex **Graph::get_adjacency_list()
{
	if (this->adjacency_list == nullptr)
	{
		return nullptr;
	}
	else
	{
		Vertex **adjacency_list_copy = new Vertex *[this->vertex_amount];

		for (int i = 0; i < this->vertex_amount; i++)
		{
			int tmp_size = 0;
			while (adjacency_list[i][tmp_size].index != -1) tmp_size++;

			adjacency_list_copy[i] = new Vertex[tmp_size + 1];

			std::copy(this->adjacency_list[i], this->adjacency_list[i] + (tmp_size + 1), adjacency_list_copy[i]);
		}

		return adjacency_list_copy;
	}
}

void Graph::generate_random_graph(double dencity, int new_vertex_amount)
{
	srand(time(NULL));

	int max_edge_amount = new_vertex_amount * (new_vertex_amount - 1);

	if (!directed)
		max_edge_amount /= 2;

	int new_edge_amount = (int)(dencity * max_edge_amount);

	Edge *edge_list = nullptr;
	int edge_list_size = 0;

	int connected_verticies_size = 1;
	int *connected_vertices = new int[connected_verticies_size];

	connected_vertices[0] = 0;

	for (int i = 1; i < new_vertex_amount; i++)
	{
		int random_vertex = connected_vertices[rand() % connected_verticies_size];

		if (edge_list == nullptr)
		{
			edge_list_size++;
			edge_list = new Edge[edge_list_size];

			edge_list[edge_list_size - 1].u = random_vertex;
			edge_list[edge_list_size - 1].v = i;
			edge_list[edge_list_size - 1].weight = rand() % (MAX_EDGE_WEIGHT - 1) + 1;
		}
		else
		{
			edge_list_size++;
			Edge *tmp = new Edge[edge_list_size];

			for (int i = 0; i < edge_list_size - 1; i++)
			{
				tmp[i] = edge_list[i];
			}

			tmp[edge_list_size - 1].u = random_vertex;
			tmp[edge_list_size - 1].v = i;
			tmp[edge_list_size - 1].weight = rand() % (MAX_EDGE_WEIGHT - 1) + 1;

			delete[] edge_list;

			edge_list = tmp;
		}

		if (i != 0)
		{
			connected_verticies_size++;
			int *tmp_Vertices = new int[connected_verticies_size];

			for (int i = 0; i < connected_verticies_size - 1; i++)
			{
				tmp_Vertices[i] = connected_vertices[i];
			}

			tmp_Vertices[connected_verticies_size - 1] = i;

			delete[] connected_vertices;

			connected_vertices = tmp_Vertices;
		}
	}

	while (edge_list_size < new_edge_amount)
	{
		int u = rand() % new_vertex_amount;
		int v = rand() % new_vertex_amount;

		if (u != v)
		{
			bool exist;
			for (int i = 0; i < edge_list_size; i++)
			{
				exist = (edge_list[i].u == u && edge_list[i].v == v);

				if (!directed)
					exist = (edge_list[i].u == u && edge_list[i].v == v) || (edge_list[i].u == v && edge_list[i].v == u);

				if (exist)
					break;
			}

			if (!exist)
			{
				edge_list_size++;
				Edge *tmp = new Edge[edge_list_size];

				for (int i = 0; i < edge_list_size - 1; i++)
				{
					tmp[i] = edge_list[i];
				}

				tmp[edge_list_size - 1].u = u;
				tmp[edge_list_size - 1].v = v;
				tmp[edge_list_size - 1].weight = rand() % (MAX_EDGE_WEIGHT - 1) + 1;

				delete[] edge_list;

				edge_list = tmp;
			}
		}
	}

	for (int i = 0; i < new_edge_amount; i++)
	{
		std::cout << edge_list[i].u << '\t' << edge_list[i].v << '\t' << edge_list[i].weight << '\n';
	}

	this->write_graph_from_edge_list(edge_list, new_vertex_amount, new_edge_amount);

	delete[] edge_list;
	delete[] connected_vertices;
}

void Graph::write_graph_from_edge_list(Edge *edge_list, int new_vertex_amount, int new_edge_amount)
{
	if (this->incidence_matrix != nullptr)
	{
		for (int i = 0; i < this->vertex_amount; i++)
			delete[] this->incidence_matrix[i];
		delete[] this->incidence_matrix;
	}

	if (this->adjacency_list != nullptr)
	{
		for (int i = 0; i < this->vertex_amount; i++)
			delete[] this->adjacency_list[i];
		delete[] this->adjacency_list;
	}

	this->vertex_amount = new_vertex_amount;
	this->edge_amount = new_edge_amount;

	this->incidence_matrix = new int *[this->vertex_amount];

	for (int i = 0; i < this->vertex_amount; i++)
	{
		this->incidence_matrix[i] = new int[this->edge_amount];
		for (int j = 0; j < this->edge_amount; j++)
		{
			this->incidence_matrix[i][j] = 0;
		}
	}

	this->adjacency_list = new Vertex *[this->vertex_amount];

	for (int i = 0; i < this->vertex_amount; i++)
	{
		this->adjacency_list[i] = new Vertex[1];
		this->adjacency_list[i][0].index = -1;
	}

	// 1 - Incidence Matrix
	for (int i = 0; i < this->edge_amount; i++)
	{
		incidence_matrix[edge_list[i].u][i] = edge_list[i].weight;
		if (this->directed)
		{
			incidence_matrix[edge_list[i].v][i] = -edge_list[i].weight;
		}
		else
		{
			incidence_matrix[edge_list[i].v][i] = edge_list[i].weight;
		}
	}

	// 2 - Adjacency list

	for (int i = 0; i < this->edge_amount; i++)
	{
		int tmp_size = 0;
		while (adjacency_list[edge_list[i].u][tmp_size].index != -1)
			tmp_size++;

		Vertex *tmp_adj = new Vertex[tmp_size + 2];

		for (int j = 0; j < tmp_size; j++)
		{
			tmp_adj[j] = adjacency_list[edge_list[i].u][j];
		}

		tmp_adj[tmp_size].index = edge_list[i].v;
		tmp_adj[tmp_size].weight = edge_list[i].weight;

		tmp_adj[tmp_size + 1].index = -1;

		delete[] adjacency_list[edge_list[i].u];

		adjacency_list[edge_list[i].u] = tmp_adj;

		if (!directed)
		{
			int tmp_size = 0;
			while (adjacency_list[edge_list[i].v][tmp_size].index != -1)
				tmp_size++;

			Vertex *tmp_adj = new Vertex[tmp_size + 2];

			for (int j = 0; j < tmp_size; j++)
			{
				tmp_adj[j] = adjacency_list[edge_list[i].v][j];
			}

			tmp_adj[tmp_size].index = edge_list[i].u;
			tmp_adj[tmp_size].weight = edge_list[i].weight;

			tmp_adj[tmp_size + 1].index = -1;

			delete[] adjacency_list[edge_list[i].v];

			adjacency_list[edge_list[i].v] = tmp_adj;
		}
	}
}

Graph::~Graph()
{
	if (this->incidence_matrix != nullptr)
	{
		for (int i = 0; i < this->vertex_amount; i++)
			delete[] this->incidence_matrix[i];
		delete[] this->incidence_matrix;
	}

	if (this->adjacency_list != nullptr)
	{
		for (int i = 0; i < this->vertex_amount; i++)
			delete[] this->adjacency_list[i];
		delete[] this->adjacency_list;
	}
}
