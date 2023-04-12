#include "MeshManager.h"
#include "Mesh.h"

MeshManager::MeshManager()
{
	mesh = nullptr;
}


MeshManager::~MeshManager()
{
}

Mesh* MeshManager::CreateMeshFromFile(const wchar_t* file_path)
{
	return static_cast<Mesh*>(CreateResourceFromFile(file_path));
}

void MeshManager::run()
{

}

void MeshManager::SetMesh(const wchar_t* file_path, std::string name)
{
	try
	{
		mesh = new Mesh(file_path);
	}
	catch (...) {}

	if (mesh != nullptr)
	{
		meshMap[name] = mesh;
	}
}

Resource* MeshManager::CreateResourceFromFileConcerete(const wchar_t* file_path)
{

	try
	{
		mesh = new Mesh(file_path);
	}
	catch (...) {}

	return mesh;
}
