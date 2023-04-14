#pragma once
#include "IWorkerAction.h"
#include "IExecutionEvent.h"
#include "Mesh.h"
#include <string>
#include <unordered_map>

class MeshLoaderThread : public IWorkerAction, public IExecutionEvent
{
public:
    MeshLoaderThread(const wchar_t* file_path, std::string _name, std::unordered_map<std::string, Mesh* >* _meshMap);
    // Inherited via IWorkerAction
    virtual void onStartTask() override;

    // Inherited via IExecutionEvent
    virtual void onFinishedExecution() override;

private:
    Mesh* mesh;
    const wchar_t* path;
    std::string name;
    std::unordered_map<std::string, Mesh*>* meshMap;

};

