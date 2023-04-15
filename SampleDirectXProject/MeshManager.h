#pragma once
#include "ResourceManager.h"
#include "IETThread.h"
#include <unordered_map>
#include <string>
#include "ThreadPool.h"
#include <string>
#include <unordered_map>
#include "SceneManager.h"
#include "IETSemaphore.h"

class Mesh;
class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	Mesh* CreateMeshFromFile(const wchar_t* file_path);
	void CreateMesh(const wchar_t* file_path, std::string name, SceneManager::SceneID scene);
	std::unordered_map<const wchar_t*, Mesh*>* meshMap;

	IETSemaphore* mutex[5];

protected:
	Mesh* mesh;

protected:
	// Inherited via ResourceManager
	virtual Resource* CreateResourceFromFileConcerete(const wchar_t* file_path) override;
	ThreadPool* threadPool;
};

