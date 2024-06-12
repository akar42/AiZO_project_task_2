#include "AlgorithmsIM.h"

Vertex* AlgorithmsIM::PrimsMST(int **incidence_matrix, int vertex_amount, int edge_amount, int start_vertex)
{
	Vertex* result = new Vertex[vertex_amount];

	VertexPriorityQueue q;

	for (int i = 0; i < vertex_amount; i++)
	{
		Vertex v = {i, 2 * MAX_EDGE_WEIGHT};
		result[i] = v;
		q.add_vertex(v);
	}

	result[start_vertex] = {-1, 0};

	q.change_key(start_vertex, 0);

	while(!q.is_empty())
	{
		Vertex u = q.get_min();
		q.pop();

		for (int v_id = 0; v_id < vertex_amount; v_id++)
		{
			if (v_id == u.index)
				continue;
			
			for (int e = 0; e < edge_amount; e++)
			{
				if (incidence_matrix[u.index][e] > 0 && incidence_matrix[v_id][e] > 0)
				{
					int weight = incidence_matrix[u.index][e];
					if (q.is_in_queue(v_id) && weight < result[v_id].weight)
					{
						result[v_id] = {u.index, weight};
						q.change_key(v_id, weight);
					}
				}
			}
		}
	}

	return result;
}

Vertex* AlgorithmsIM::KruskalMST(int **incidence_matrix, int vertex_amount, int edge_amount)
{
	Vertex* result = new Vertex[vertex_amount];

	for (int i = 0; i < vertex_amount; i++)
	{
		result[i] = {-1, 0};
	}

	Edge* edge_list = new Edge[edge_amount];

	for (int e_id = 0; e_id < edge_amount; e_id++)
	{
		Edge tmp;
		bool start = true;
		int u = -1;
		int v = -1;
		int weight = 0;

		for (int v_id = 0; v_id < vertex_amount; v_id++)
		{
			if (incidence_matrix[v_id][e_id] > 0)
			{
				if (start)
				{
					u = v_id;
					weight = incidence_matrix[v_id][e_id];
					start = !start;
				}
				else
				{
					v = v_id;
				}
			}
			
		}

		tmp = {u, v, weight};

		edge_list[e_id] = tmp;		
	}

	mergeSortEdges(edge_list, 0, edge_amount - 1);

	DisjointSets disjoint_sets(vertex_amount);

	for (int i = 0; i < edge_amount; i++)
	{
		int u = edge_list[i].u;
		int v = edge_list[i].v;

		int set_u = disjoint_sets.find(u);
		int set_v = disjoint_sets.find(v);

		if (set_u != set_v)
		{
			if (result[v].index == -1)
			{
				result[v].index = u;
				result[v].weight = edge_list[i].weight;
			} else {
				result[u].index = v;
				result[u].weight = edge_list[i].weight;
			}
			disjoint_sets.merge(set_u, set_v);
		}
	}

	delete[] edge_list;

	return result;
}

Vertex* AlgorithmsIM::DijkstraPath(int **incidence_matrix, int vertex_amount, int edge_amount, int start_vertex)
{
	Vertex* result = new Vertex[vertex_amount];

	VertexPriorityQueue q;

	for (int i = 0; i < vertex_amount; i++)
	{
		Vertex v = {i, 2 * MAX_EDGE_WEIGHT};
		result[i] = v;
		q.add_vertex(v);
	}

	result[start_vertex] = {-1, 0};
	q.change_key(start_vertex, 0);

	while(!q.is_empty())
	{
		Vertex u = q.get_min();
		q.pop();

		for (int v_id = 0; v_id < vertex_amount; v_id++)
		{
			if (v_id == u.index)
				continue;
			
			for (int e = 0; e < edge_amount; e++)
			{
				if (incidence_matrix[u.index][e] > 0 && incidence_matrix[v_id][e] < 0)
				{
					int weight = incidence_matrix[u.index][e];
					if ((weight + result[u.index].weight) < result[v_id].weight)
					{
						result[v_id].index = u.index;
						result[v_id].weight = weight + result[u.index].weight;
						q.change_key(v_id, result[v_id].weight);
					}
				}
			}
		}
	}

	return result;
}

Vertex *AlgorithmsIM::BellmanFordPath(int **incidence_matrix, int vertex_amount, int edge_amount, int start_vertex)
{
	Vertex* result = new Vertex[vertex_amount];

	for (int i = 0; i < vertex_amount; i++)
	{
		result[i] = {-1, 2 * MAX_EDGE_WEIGHT};
	}

	result[start_vertex] = {-1, 0};

	bool no_changes = false;

	for (int i = 1; i < vertex_amount; i++)
	{
		no_changes = true;

		for (int edge = 0; edge < edge_amount; edge++)
		{
			int u_id = -1;
			int v_id = -1;
			int weight = 0;

			for (int j = 0; j < vertex_amount; j++)
			{
				if (incidence_matrix[j][edge] > 0){
					u_id = j;
					weight = incidence_matrix[j][edge];
				}

				if (incidence_matrix[j][edge] < 0)
					v_id = j;
			}

			if (result[v_id].weight > result[u_id].weight + weight)
			{
				no_changes = false;
				result[v_id].index = u_id;
				result[v_id].weight = result[u_id].weight + weight;
			}
		}

		if (no_changes)
			return result;
	}

	// Check for negative cycle
	for (int edge = 0; edge < edge_amount; edge++)
	{
		int u_id = -1;
		int v_id = -1;
		int weight = 0;

		for (int j = 0; j < vertex_amount; j++)
		{
			if (incidence_matrix[j][edge] > 0)
			{
				u_id = j;
				weight = incidence_matrix[j][edge];
			}

			if (incidence_matrix[j][edge] < 0)
				v_id = j;
		}

		if (result[v_id].weight > result[u_id].weight + weight)
		{
			delete[] result;
			return nullptr;
		}
	}

	return result;
}
