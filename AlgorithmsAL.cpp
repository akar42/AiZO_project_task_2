#include "AlgorithmsAL.h"

Vertex *AlgorithmsAL::PrimsMST(Vertex **adjacency_list, int vertex_amount, int edge_amount, int start_vertex)
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

		for (int i = 0; adjacency_list[u.index][i].index != -1; i++)
		{
			int v_id = adjacency_list[u.index][i].index;
			int weight = adjacency_list[u.index][i].weight;
			if (q.is_in_queue(v_id) && weight < result[v_id].weight)
			{
				result[v_id] = {u.index, weight};
				q.change_key(v_id, weight);
			}
		}
	}

	return result;
}

Vertex* AlgorithmsAL::KruskalMST(Vertex **adjacency_list, int vertex_amount, int edge_amount)
{
	Vertex* result = new Vertex[vertex_amount];

	for (int i = 0; i < vertex_amount; i++)
	{
		result[i] = {-1, 0};
	}

	int edge_list_size = 0;
	Edge* edge_list = nullptr;

	for (int u_id = 0; u_id < vertex_amount; u_id++)
	{
		for (int j = 0; adjacency_list[u_id][j].index != -1; j++)
		{
			int v_id = adjacency_list[u_id][j].index;
			int weight = adjacency_list[u_id][j].weight;

			if (v_id < u_id)
				continue;

			Edge tmp = {u_id, v_id, weight};

			if (edge_list == nullptr)
			{
				edge_list_size++;
				edge_list = new Edge[edge_list_size];

				edge_list[edge_list_size - 1] = tmp;
			}
			else
			{
				edge_list_size++;
				Edge* tmp_edge_list = new Edge[edge_list_size];

				for (int i = 0; i < edge_list_size - 1; i++)
				{
					tmp_edge_list[i] = edge_list[i];
				}

				tmp_edge_list[edge_list_size - 1] = tmp;

				delete[] edge_list;
				edge_list = tmp_edge_list;
			}

		}
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

Vertex *AlgorithmsAL::DijkstraPath(Vertex **adjacency_list, int vertex_amount, int edge_amount, int start_vertex)
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

		for (int i = 0; adjacency_list[u.index][i].index != -1; i++)
		{
			int v_id = adjacency_list[u.index][i].index;
			int weight = adjacency_list[u.index][i].weight;
			if ((weight + result[u.index].weight) < result[v_id].weight)
			{
				result[v_id] = {u.index, weight + result[u.index].weight};
				q.change_key(v_id, weight);
			}
		}
	}

	return result;
}

Vertex *AlgorithmsAL::BellmanFordPath(Vertex **adjacency_list, int vertex_amount, int edge_amount, int start_vertex)
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

		for (int u_id = 0; u_id < vertex_amount; u_id++)
		{
			for (int j = 0; adjacency_list[u_id][j].index != -1; j++)
			{
				int v_id = adjacency_list[u_id][j].index;
				int weight = adjacency_list[u_id][j].weight;

				if (result[v_id].weight > result[u_id].weight + weight)
				{
					no_changes = false;
					result[v_id] = {u_id, weight + result[u_id].weight};
				}
			}
		}

		if (no_changes)
			return result;
	}

	// Check for negative cycle
	for (int u_id = 0; u_id < vertex_amount; u_id++)
	{
		for (int j = 0; adjacency_list[u_id][j].index != -1; j++)
		{
			int v_id = adjacency_list[u_id][j].index;
			int weight = adjacency_list[u_id][j].weight;

			if (result[v_id].weight > result[u_id].weight + weight)
			{
				delete[] result;
				return nullptr;
			}
		}
	}

	return result;
}
