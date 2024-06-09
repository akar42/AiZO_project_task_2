#pragma once
#include "Graph.h"
#include <string>
#include <iostream>
#include <fstream>

class ReadGraphFile
{
private:
	int vertex_amount = -1;
	int edges_amount = -1;

public:
	Edge* read_graph(std::string filename);
	int get_vertex_amount();
	int get_edges_amount();
};