#include "MeshLoaderThread.h"
#include <iostream>
#include <filesystem>
//MeshLoaderThread::MeshLoaderThread(const wchar_t* file_path, std::string _name, std::unordered_map<std::string, Mesh*>* _meshMap)
//{
//	path = file_path;
//	name = _name;
//	meshMap = _meshMap;
//	mesh = nullptr;
//	meshList = new std::vector<Mesh*>();
//}

MeshLoaderThread::MeshLoaderThread(std::string file_path, std::string _name, std::unordered_map<std::string, std::vector<Mesh*>*>* _meshListMap)
{
	path = file_path;
	name = _name;
	//meshMap = _meshMap;
	meshListMap = _meshListMap;
	mesh = nullptr;
	meshList = new std::vector<Mesh*>();
}

void MeshLoaderThread::onStartTask()
{
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		std::string path = entry.path().generic_string();
		std::wstring widestr = std::wstring(path.begin(), path.end());
		const wchar_t* widecstr = widestr.c_str();
		Mesh* newMesh = nullptr;
		newMesh = TryCreateMesh(widecstr);
		if (newMesh != nullptr)
		{
			meshList->push_back(newMesh);
		}
	}
	/*try
	{
		mesh = new Mesh(path);
	}
	catch (...) {}*/

	onFinishedExecution();
	delete this;
}

void MeshLoaderThread::onFinishedExecution()
{
	//if (mesh != nullptr)
	//{
	//	(*meshMap)[name] = mesh;
	//	//std::cout << "Loaded mesh: " << sizeof(mesh) << " " << sizeof((*meshMap)[name]) << std::endl;
	//	//memcpy((*meshMap)[name], mesh, sizeof(mesh));
	//}

	(*meshListMap)[name] = meshList;
}

Mesh* MeshLoaderThread::TryCreateMesh(const wchar_t* mesh_path)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(mesh_path);
	}
	catch (...) {}

	return mesh;
}
