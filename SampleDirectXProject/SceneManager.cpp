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
    //SceneA.modelList.push_back(std::make_pair(availableMeshList[3].first, availableMeshList[3].second));
    ////SceneA.modelList.push_back(std::make_pair(availableMeshList[1].first, availableMeshList[1].second));

    //// add all total vertices of listed model in id [SECOND]
    //for (int i = 0; i < SceneA.modelList.size(); i++)
    //{
    //    SceneA.TOTAL_VERTICES += SceneA.modelList[i].second;
    //}

    //// create mesh from the path of the models [FIRST]
    //for (int i = 0; i < SceneA.modelList.size(); i++)
    //{
    //    GraphicsEngine::get()->getMeshManager()->CreateMesh(SceneA.modelList[i].first, " ", SceneA.id);
    //}
#pragma endregion


    //populate the model list of id from the available mesh list
    sceneArray[0].modelList.push_back(std::make_pair(availableMeshList[3].first, availableMeshList[3].second));
    sceneArray[1].modelList.push_back(std::make_pair(availableMeshList[3].first, availableMeshList[3].second));
    sceneArray[2].modelList.push_back(std::make_pair(availableMeshList[3].first, availableMeshList[3].second));
    sceneArray[3].modelList.push_back(std::make_pair(availableMeshList[3].first, availableMeshList[3].second));
    sceneArray[4].modelList.push_back(std::make_pair(availableMeshList[3].first, availableMeshList[3].second));
    //SceneA.modelList.push_back(std::make_pair(availableMeshList[1].first, availableMeshList[1].second));

    for (int i = 0; i < 5; i++)
    {
        // add all total vertices of listed model in [SECOND]
        for (int j = 0; j < sceneArray[i].modelList.size(); j++)
        {
            sceneArray[i].TOTAL_VERTICES +=sceneArray[i].modelList[j].second;
        }
    }    

    for (int i = 0; i < 5; i++)
    {
        // create mesh from the path of the models [FIRST]
        for (int j = 0; j < sceneArray[i].modelList.size(); j++)
        {
            GraphicsEngine::get()->getMeshManager()->CreateMesh(sceneArray[i].modelList[j].first, " ", sceneArray[i].id);
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

void SceneManager::initializeScene(SceneID scene)
{
}

