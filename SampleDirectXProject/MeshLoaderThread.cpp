#include "MeshLoaderThread.h"
#include <iostream>
#include "IExecutionEvent.h"
#include "Mesh.h"
#include <string>
MeshLoaderThread::MeshLoaderThread(const wchar_t* file_path, std::string _name, std::unordered_map<std::string, Mesh*>* _meshMap, SceneManager::SceneID scene)
{
	// updated attributes necessary for loading
	path = file_path;
	name = _name;
	meshMap = _meshMap;
	mesh = nullptr;
	this->sceneType = scene;
}

void MeshLoaderThread::onStartTask()
{
	std:: cout << "StartThread"<< std::to_string(sceneType)<< std::endl;
	isRunning = true;
	try
	{
		mesh = new Mesh(path,this); // pass this thread as listerner for the mesh class to retriver (nloadedVertices, totalVertices)
	}
	catch (...) {}

	onFinishedExecution();
	isRunning = false;
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

void MeshLoaderThread::StopLoading()
{
	
}
