#include "SceneManager.h"
#include "MeshUtils.h"
#include "GraphicsEngine.h"

SceneManager* SceneManager::instance = nullptr;
const std::string NAME_TEAPOT = "Teapot";
const std::string NAME_CUBE = "Cube";
const std::string NAME_PLANE = "Plane";
const std::string NAME_SPHERE = "Sphere";
const std::string NAME_CAPSULE = "Capsule";
const std::string NAME_CYLINDER = "Cylinder";
const std::string NAME_BUNNY = "Bunny";
const std::string NAME_ARMADILLO = "Armadillo";
const std::string NAME_LUCY = "Lucy";

SceneManager::SceneManager()
{
}

void SceneManager::Initialize()
{
	instance = new SceneManager();
    // Instantiate scene ID
    instance->sceneArray[0].id = A;
    instance->sceneArray[1].id = B;
    instance->sceneArray[2].id = C;
    instance->sceneArray[3].id = D;
    instance->sceneArray[4].id = E;

    
    // populate meshlist -> first: model path | second: model face vertices size
    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\teapot.obj", 8020));

    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\cube.obj", 12));

    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\bunny.obj",4968) );

    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\armadillo.obj", 212574));


    
}

SceneManager* SceneManager::Get()
{
	return instance;
}

void SceneManager::LoadAllScenes()
{

#pragma region Manual
    //populate the model list of id from the available mesh list
    //SceneA.modelInfoList.push_back(std::make_pair(availableMeshList[3].first, availableMeshList[3].second));
    ////SceneA.modelInfoList.push_back(std::make_pair(availableMeshList[1].first, availableMeshList[1].second));

    //// add all total vertices of listed model in id [SECOND]
    //for (int i = 0; i < SceneA.modelInfoList.size(); i++)
    //{
    //    SceneA.TOTAL_VERTICES += SceneA.modelInfoList[i].second;
    //}

    //// create mesh from the path of the models [FIRST]
    //for (int i = 0; i < SceneA.modelInfoList.size(); i++)
    //{
    //    GraphicsEngine::get()->getMeshManager()->CreateMesh(SceneA.modelInfoList[i].first, " ", SceneA.id);
    //}
#pragma endregion


    //populate the model list of id from the available mesh list
    sceneArray[0].modelInfoList.push_back(std::make_pair(availableMeshList[0].first, availableMeshList[0].second));
    sceneArray[1].modelInfoList.push_back(std::make_pair(availableMeshList[1].first, availableMeshList[1].second));
    sceneArray[2].modelInfoList.push_back(std::make_pair(availableMeshList[2].first, availableMeshList[2].second));
    sceneArray[3].modelInfoList.push_back(std::make_pair(availableMeshList[3].first, availableMeshList[3].second));
    sceneArray[4].modelInfoList.push_back(std::make_pair(availableMeshList[3].first, availableMeshList[3].second));
    //SceneA.modelInfoList.push_back(std::make_pair(availableMeshList[1].first, availableMeshList[1].second));

    for (int i = 0; i < 5; i++)
    {
        // add all total vertices of listed model in [SECOND]
        for (int j = 0; j < sceneArray[i].modelInfoList.size(); j++)
        {
            sceneArray[i].TOTAL_VERTICES +=sceneArray[i].modelInfoList[j].second;
        }
    }    

    for (int i = 0; i < 5; i++)
    {
        instance->LoadScene((SceneID)i);
        // create mesh from the path of the models [FIRST]
        for (int j = 0; j < sceneArray[i].modelInfoList.size(); j++)
        {
            GraphicsEngine::get()->getMeshManager()->CreateMesh(sceneArray[i].modelInfoList[j].first, " ", sceneArray[i].id);
        }
    }

   
    
    

    
}

void SceneManager::UpdateSceneState(SceneID scene)
{
	switch (scene)
	{
    case A:instance->sceneArray[0].LOADED_VERTICES += 1; break;
    case B:instance->sceneArray[1].LOADED_VERTICES += 1; break;
    case C:instance->sceneArray[2].LOADED_VERTICES += 1; break;
    case D:instance->sceneArray[3].LOADED_VERTICES += 1; break;
    case E:instance->sceneArray[4].LOADED_VERTICES += 1; break;
	}
}

void SceneManager::LoadScene(SceneID scene)
{
    switch (scene)
    {
    case A:instance->sceneArray[0].loadState = isLoading; break;
    case B:instance->sceneArray[1].loadState = isLoading; break;
    case C:instance->sceneArray[2].loadState = isLoading; break;
    case D:instance->sceneArray[3].loadState = isLoading; break;
    case E:instance->sceneArray[4].loadState = isLoading; break;
    }
}

void SceneManager::UnloadScene(SceneID scene)
{
    switch (scene)
    {
    case A:instance->sceneArray[0].LOADED_VERTICES = 0; instance->sceneArray[0].isUnloading = true; break;
    case B:instance->sceneArray[1].LOADED_VERTICES = 0; instance->sceneArray[1].isUnloading = true; break;
    case C:instance->sceneArray[2].LOADED_VERTICES = 0; instance->sceneArray[2].isUnloading = true; break;
    case D:instance->sceneArray[3].LOADED_VERTICES = 0; instance->sceneArray[3].isUnloading = true; break;
    case E:instance->sceneArray[4].LOADED_VERTICES = 0; instance->sceneArray[4].isUnloading = true; break;
    }
}

SceneManager::Scene SceneManager::getScene(SceneID scene)
{
    switch (scene)
    {
    case A:return instance->sceneArray[0]; break;
    case B:return instance->sceneArray[1]; break;
    case C:return instance->sceneArray[2]; break;
    case D:return instance->sceneArray[3]; break;
    case E:return instance->sceneArray[4]; break;
    }
}

void SceneManager::ResetScene(SceneID scene)
{
    switch (scene)
    {
    case A:
    {
        sceneArray[0].isLoaded = false;
        sceneArray[0].loadState = LoadState::isUnloaded;
        sceneArray[0].id = SceneID::NOT_SET;
        sceneArray[0].TOTAL_VERTICES = 0;
        sceneArray[0].LOADED_VERTICES = 0;
        sceneArray[0].isLoaded = false;
        sceneArray[0].isUnloading = false;
        //sceneArray[0].modelInfoList.clear();
    }
    break;
    case B:
    {
        sceneArray[1].isLoaded = false;
        sceneArray[1].loadState = LoadState::isUnloaded;
        sceneArray[1].id = SceneID::NOT_SET;
        sceneArray[1].TOTAL_VERTICES = 0;
        sceneArray[1].LOADED_VERTICES = 0;
        sceneArray[1].isLoaded = false;
        sceneArray[1].isUnloading = false;
    }
    break;
    case C:
    {
        sceneArray[2].isLoaded = false;
        sceneArray[2].loadState = LoadState::isUnloaded;
        sceneArray[2].id = SceneID::NOT_SET;
        sceneArray[2].TOTAL_VERTICES = 0;
        sceneArray[2].LOADED_VERTICES = 0;
        sceneArray[2].isLoaded = false;
        sceneArray[2].isUnloading = false;
    }
    break;
    case D:
    {
        sceneArray[3].isLoaded = false;
        sceneArray[3].loadState = LoadState::isUnloaded;
        sceneArray[3].id = SceneID::NOT_SET;
        sceneArray[3].TOTAL_VERTICES = 0;
        sceneArray[3].LOADED_VERTICES = 0;
        sceneArray[3].isLoaded = false;
        sceneArray[3].isUnloading = false;
    }
    break;
    case E:
    {
        sceneArray[4].isLoaded = false;
        sceneArray[4].loadState = LoadState::isUnloaded;
        sceneArray[4].id = SceneID::NOT_SET;
        sceneArray[4].TOTAL_VERTICES = 0;
        sceneArray[4].LOADED_VERTICES = 0;
        sceneArray[4].isLoaded = false;
        sceneArray[4].isUnloading = false;
    }
    break;
    }
}





