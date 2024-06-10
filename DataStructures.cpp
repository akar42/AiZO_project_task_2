#include "DataStructures.h"

void VertexPriorityQueue::add_vertex(Vertex v)
{
	if (this->size == 0)
	{
		this->size++;
		this->min_heap = new Vertex[1];
		min_heap[0] = v;
	}
	else
	{
		this->size++;
		Vertex* tmp = new Vertex[size];

		for(int i = 0; i < this->size - 1; i++)
		{
			tmp[i] = this->min_heap[i];
		}

		tmp[size - 1] = v;

		delete[] this->min_heap;

		this->min_heap = tmp;

		for (int i = this->size - 1; i >= 0; i--)
		{
			this->adjustForHeap(i, this->size);
		}

	}
}

Vertex VertexPriorityQueue::get_min()
{
	return this->min_heap[0];
}

void VertexPriorityQueue::adjustForHeap(int node_id, int heap_length)
{
	int leftChild = 2 * node_id + 1;
	int rightChild = leftChild + 1;

	if (leftChild >= heap_length)
	{
		// No children
		return;
	}

	if (rightChild >= heap_length)
	{
		// Only one child (from left side)
		if (this->min_heap[node_id].weight > this->min_heap[leftChild].weight)
		{
			// Adjustment to heap and there is NO invocation recurrently
			// adjustForheap() becuase of it's properties
			Vertex tmp = this->min_heap[node_id];
			this->min_heap[node_id] = this->min_heap[leftChild];
			this->min_heap[leftChild] = tmp;
		}
		else
		{
			return;
		}
	}
	else
	{
		// Both of children are present
		if (this->min_heap[leftChild].weight < this->min_heap[rightChild].weight)
		{
			// Left child is candidate to swap with his ancestor
			if (this->min_heap[node_id].weight > this->min_heap[leftChild].weight)
			{
				// Adjustment to heap and invocation recurrently adjustForheap()
				Vertex tmp = this->min_heap[node_id];
				this->min_heap[node_id] = this->min_heap[leftChild];
				this->min_heap[leftChild] = tmp;

				adjustForHeap(leftChild, heap_length);
			}
		}
		else
		{
			// Right child is candidate to swap with his ancestor
			if (this->min_heap[node_id].weight > this->min_heap[rightChild].weight)
			{
				// Adjustment to heap and invocation recurrently adjustForheap()
				Vertex tmp = this->min_heap[node_id];
				this->min_heap[node_id] = this->min_heap[rightChild];
				this->min_heap[rightChild] = tmp;

				adjustForHeap(rightChild, heap_length);
			}
		}
	}
}

void VertexPriorityQueue::pop()
{
	if (this->size == 1)
	{
		delete[] this->min_heap;
		this->min_heap = nullptr;
		size--;
	}
	else
	{
		Vertex output = this->min_heap[0];
		this->min_heap[0] = this->min_heap[this->size - 1];
		this->min_heap[this->size - 1] = output;

		this->size--;
		Vertex* tmp = new Vertex[size];

		for(int i = 0; i < this->size; i++)
		{
			tmp[i] = this->min_heap[i];
			// std::cout << tmp[i].index << '\t' << tmp[i].weight << '\n';
		}

		delete[] this->min_heap;

		this->min_heap = tmp;

		adjustForHeap(0, this->size);

		// std::cout << "Queue after pop" << '\n';
		// for (int i = 0; i < this->size; i++)
		// {
		// 	std::cout << this->min_heap[i].index << '\t' << this->min_heap[i].weight << '\n';
		// }
		

	}
}

void VertexPriorityQueue::change_key(int vertex_index, int new_key)
{
	for (int i = 0; i < this->size; i++)
	{
		if (this->min_heap[i].index == vertex_index)
			this->min_heap[i].weight = new_key;
	}

	for (int i = size - 1; i >= 0; i--)
	{
		adjustForHeap(i, this->size);
	}
}

bool VertexPriorityQueue::is_in_queue(int vertex_index)
{
	for (int i = 0; i < this->size; i++)
	{
		if (this->min_heap[i].index == vertex_index)
			return true;
	}
	return false;
}

bool VertexPriorityQueue::is_empty()
{
	if (this->min_heap == nullptr && this->size == 0)
	{
		return true;
	}
	return false;
}

VertexPriorityQueue::~VertexPriorityQueue()
{
	if (this->min_heap != nullptr)
		delete[] this->min_heap;
}

DisjointSets::DisjointSets(int n)
{
	this->n = n;
	parent = new int[n + 1];
	rank = new int[n + 1];

	for (int i = 0; i <= n; i++)
	{
		rank[i] = 0;
		parent[i] = i;
	}
}

int DisjointSets::find(int u)
{
	if (u != parent[u])
	{
		parent[u] = find(parent[u]);
	}
	return parent[u];
}

void DisjointSets::merge(int x, int y)
{
	x = find(x);
	y = find(y);

	if (rank[x] > rank[y])
		parent[y] = x;
	else
		parent[x] = y;

	if (rank[x] == rank[y])
		rank[y]++;
}

DisjointSets::~DisjointSets()
{
	delete[] parent;
	delete[] rank;
}

void mergeEdgeArrays(Edge *arr, int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	Edge *L = new Edge[n1];
	Edge *R = new Edge[n2];

	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int i = 0; i < n2; i++)
		R[i] = arr[m + 1 + i];

	int i = 0, j = 0, k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].weight <= R[j].weight)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
}

void mergeSortEdges(Edge *arr, int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergeSortEdges(arr, l, m);
		mergeSortEdges(arr, m + 1, r);
		mergeEdgeArrays(arr, l, m, r);
	}
}
