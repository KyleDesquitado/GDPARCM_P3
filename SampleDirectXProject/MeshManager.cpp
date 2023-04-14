#include "MeshManager.h"
#include "Mesh.h"
#include "MeshLoaderThread.h"

MeshManager::MeshManager()
{
	mesh = nullptr;

	this->threadPool = new ThreadPool("ThreadPool", 8);
	this->threadPool->startScheduler();
	this->meshMap = new std::unordered_map<std::string, Mesh*>();

}


MeshManager::~MeshManager()
{
}

Mesh* MeshManager::CreateMeshFromFile(const wchar_t* file_path)
{
	return static_cast<Mesh*>(CreateResourceFromFile(file_path));
}

void MeshManager::CreateMesh(const wchar_t* file_path, std::string name, SceneManager::SceneID scene)
{
	// create and schedule mesh loader
	MeshLoaderThread* meshLoader = new MeshLoaderThread(file_path, name, meshMap, scene);
	// save all
	threadPool->scheduleTask(meshLoader);

}

Resource* MeshManager::CreateResourceFromFileConcerete(const wchar_t* file_path)
{
	/*Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(file_path, );
	}
	catch (...) {}

	return mesh;*/

	return nullptr;
}
