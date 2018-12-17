#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "vec3.hpp"

struct Model
{
	std::vector<Vec3f> vertices;
	std::vector<std::vector<int>> faces;

	Model(const std::string& filePath)
	{
		std::ifstream in;
		in.open(filePath, std::ifstream::in);

		if (in.fail())
		{
			return;
		}

		std::string line;
		while (!in.eof())
		{
			std::getline(in, line);
			std::istringstream iss(line);
			char trash;

			if (!line.compare(0, 2, "v "))
			{
				iss >> trash;
				Vec3f v;
				for (int i = 0; i < 3; i++)
				{
					iss >> v.raw[i];
				}
				vertices.push_back(v);
			}
			else if(!line.compare(0, 2, "f "))
			{
				std::vector<int> f;
				int itrash;
				int idx;
				iss >> trash;
				while (iss >> idx >> trash >> itrash >> trash >> itrash)
				{
					idx--;
					f.push_back(idx);
				}

				faces.push_back(f);
			}
		}
	}
};