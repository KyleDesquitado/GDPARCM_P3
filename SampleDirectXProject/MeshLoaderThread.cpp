#include "MeshLoaderThread.h"
#include <iostream>
MeshLoaderThread::MeshLoaderThread(const wchar_t* file_path, std::string _name, std::unordered_map<std::string, Mesh*>* _meshMap)
{
	path = file_path;
	name = _name;
	meshMap = _meshMap;
	mesh = nullptr;
}

void MeshLoaderThread::onStartTask()
{
	try
	{
		mesh = new Mesh(path);
	}
	catch (...) {}

	onFinishedExecution();
	delete this;
}

void MeshLoaderThread::onFinishedExecution()
{
	if (mesh != nullptr)
	{
		(*meshMap)[name] = mesh;
		//std::cout << "Loaded mesh: " << sizeof(mesh) << " " << sizeof((*meshMap)[name]) << std::endl;
		//memcpy((*meshMap)[name], mesh, sizeof(mesh));
	}
}
