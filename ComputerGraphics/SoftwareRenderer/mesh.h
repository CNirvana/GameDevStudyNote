#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "vertex.h"
#include "OBJ_Loader.h"

class Mesh
{
public:
	Mesh() {}
	Mesh(const std::string& filePath)
	{
		objl::Loader loader;
		loader.LoadFile(filePath);

		if (loader.LoadedMeshes.size() == 0)
		{
			return;
		}

		auto m = loader.LoadedMeshes[0];
		for (int i = 0; i < m.Vertices.size(); i++)
		{
			auto mV = m.Vertices[i];
			Vertex v;
			v.position = Vec3f(mV.Position.X, mV.Position.Y, mV.Position.Z);
			v.uv = Vec2f(mV.TextureCoordinate.X, mV.TextureCoordinate.Y);
			v.normal = Vec3f(mV.Normal.X, mV.Normal.Y, mV.Normal.Z);
			vertices.push_back(v);
		}
		for (int i = 0; i < m.Indices.size(); i++)
		{
			indices.push_back(m.Indices[i]);
		}
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};