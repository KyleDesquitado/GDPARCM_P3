#pragma once
#include "ResourceManager.h"
#include "IETThread.h"
#include <unordered_map>
#include <string>
class Mesh;
class MeshManager : public ResourceManager, public IETThread
{
public:
	MeshManager();
	~MeshManager();
	Mesh* CreateMeshFromFile(const wchar_t* file_path);
	void run() override;
	void SetMesh(const wchar_t* file_path, std::string name);
	std::unordered_map<std::string, Mesh*> meshMap;
protected:
	// Inherited via ResourceManager
	virtual Resource* CreateResourceFromFileConcerete(const wchar_t* file_path) override;
	Mesh* mesh;
};

