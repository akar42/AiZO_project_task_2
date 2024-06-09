#include "ReadGraphFile.h"

Edge *ReadGraphFile::read_graph(std::string filename)
{
	std::ifstream fin;

	fin.open(filename);

	if (!fin.is_open())
	{
		std::cout << "Cannot open specified file." << '\n';

		return nullptr;
	}
	else
	{
		std::cout << filename << " is opened succesfully." << '\n';

		fin >> this->edges_amount;
		fin >> this->vertex_amount;
		Edge* edge_list = new Edge[this->edges_amount];

		for (int i = 0; i < this->edges_amount; i++)
		{
			if (fin.eof())
			{
				std::cout << "Size missmatch in file - amount of edges is less then declared.\n";
				std::cout << "Data hasn't been readen\n";
				
				this->edges_amount = -1;
				this->vertex_amount = -1;
				delete[] edge_list;

				return nullptr;
			}

			fin >> edge_list[i].u;
			fin >> edge_list[i].v;
			fin >> edge_list[i].weight;

		}

		return edge_list;
	}
}

int ReadGraphFile::get_vertex_amount()
{
	return this->vertex_amount;
}

int ReadGraphFile::get_edges_amount()
{
	return this->edges_amount;
}
