#pragma once
#include "ResourceManager.h"
#include "IETThread.h"
#include <unordered_map>
#include <string>
#include "ThreadPool.h"
#include <string>
#include <unordered_map>
#include <vector>

class Mesh;
class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	Mesh* CreateMeshFromFile(const wchar_t* file_path);
	void CreateMesh(const wchar_t* file_path, std::string name);
	void LoadMeshesFromFile(std::string file_path, std::string name);

	std::unordered_map<std::string, Mesh*>* meshMap;
	std::unordered_map<std::string, std::vector<Mesh*>*>* meshListMap;
protected:
	Mesh* mesh;

protected:
	// Inherited via ResourceManager
	virtual Resource* CreateResourceFromFileConcerete(const wchar_t* file_path) override;
	ThreadPool* threadPool;
};

