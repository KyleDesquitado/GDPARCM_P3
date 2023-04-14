#pragma once
#include "IWorkerAction.h"
#include "IExecutionEvent.h"
#include "Mesh.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <string>
class MeshLoaderThread :
    public IWorkerAction, public IExecutionEvent
{
public:
    //MeshLoaderThread(const wchar_t* file_path, std::string _name, std::unordered_map<std::string, Mesh* >* _meshMap);
    MeshLoaderThread(std::string file_path, std::string _name, std::unordered_map<std::string, std::vector<Mesh*>* >* _meshListMap);

    // Inherited via IWorkerAction
    virtual void onStartTask() override;

    // Inherited via IExecutionEvent
    virtual void onFinishedExecution() override;

private:
    Mesh* mesh;
    //const wchar_t* path;
    std::string path;
    std::string name;
    std::vector<Mesh*>* meshList;
    std::unordered_map<std::string, Mesh*>* meshMap;
    std::unordered_map<std::string, std::vector<Mesh*>*>* meshListMap;

    Mesh* TryCreateMesh(const wchar_t* mesh_path);
};

