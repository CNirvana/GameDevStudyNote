#pragma once

#include <vector>

#include "vertex.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<int> indices;
};