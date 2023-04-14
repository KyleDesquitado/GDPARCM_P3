#pragma once

#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>
#include <exception>


#include <iostream>
#include <cstddef>

static class MeshUtils
{
public: 
	static size_t CountTotalVertices(const wchar_t* full_path)
	{
		#pragma region MeshLoader
		tinyobj::attrib_t attribs;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		std::wstring w_inputfile = std::wstring(full_path);
		std::string inputfile = std::string(w_inputfile.begin(), w_inputfile.end());

		bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());
		
		size_t totalVertices = 0;
		for (size_t i = 0; i < shapes.size(); i++)
		{
			totalVertices += shapes[i].mesh.num_face_vertices.size();
		}
		return totalVertices;


		if (!err.empty())
		{
			throw std::exception("Mesh read successfully");
		}


		if (!res)
		{
			throw std::exception("Mesh not read successfully");
		}

		if (shapes.size() > 1)
			std::exception("Mesh not read successfully");
	}
};