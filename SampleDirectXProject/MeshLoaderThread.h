#pragma once
#include "IWorkerAction.h"
#include "IExecutionEvent.h"
#include <string>
#include <unordered_map>
#include "SceneManager.h"
class Mesh;
class MeshLoaderThread : public IWorkerAction, public IExecutionEvent
{
public:
    MeshLoaderThread(const wchar_t* file_path, std::string _name, std::unordered_map<std::string, Mesh* >* _meshMap, SceneManager::SceneID scene);
    // Inherited via IWorkerAction
    virtual void onStartTask() override;


    // Inherited via IExecutionEvent
    virtual void onFinishedExecution() override;

    void StopLoading();

private:
    Mesh* mesh;
    const wchar_t* path;
    std::string name;
    std::unordered_map<std::string, Mesh*>* meshMap;

public:
    int nTotalVertices = 0;
    int nLoadedVertices = 0;
    SceneManager::SceneID sceneType = SceneManager::SceneID::NOT_SET;

    bool isRunning = false;

};

