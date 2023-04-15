#include "SceneManager.h"
#include "MeshUtils.h"
#include "GraphicsEngine.h"
#include "GameObjectManager.h"
#include "TransformComponent.h"

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

    for (int i = 0; i < 5; i++)
    {
        instance->mutex[i] = new IETSemaphore(1);
    }
    // Instantiate scene ID
    instance->sceneArray[0].id = A;
    instance->sceneArray[1].id = B;
    instance->sceneArray[2].id = C;
    instance->sceneArray[3].id = D;
    instance->sceneArray[4].id = E;

    // populate meshlist -> first: model path | second: model face vertices size
    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\teapot.obj", 8020));
    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\cube.obj", 12));
    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\bunny.obj", 4968));

    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\armadillo.obj", 212574));
    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\asteroid.obj", 768));
    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\monitor.obj", 12236));

    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\spaceship.obj", 1080));
    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\house.obj", 200000));
    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\statue.obj", 5670));

    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\suzanne.obj", 968));
    instance->availableMeshList.push_back(std::make_pair(L"Assets\\Meshes\\torus.obj", 2880));


    //populate the model list of id from the available mesh list
    instance->sceneArray[0].modelInfoList.push_back(std::make_pair(instance->availableMeshList[0].first, instance->availableMeshList[0].second));
    instance->sceneArray[1].modelInfoList.push_back(std::make_pair(instance->availableMeshList[1].first, instance->availableMeshList[1].second));
    instance->sceneArray[2].modelInfoList.push_back(std::make_pair(instance->availableMeshList[2].first, instance->availableMeshList[2].second));
    instance->sceneArray[3].modelInfoList.push_back(std::make_pair(instance->availableMeshList[3].first, instance->availableMeshList[3].second));
    //[4].modelInfoList.push_back(std::make_pair(availableMeshList[3].first, availableMeshList[3].second));
    //SceneA.modelInfoList.push_back(std::make_pair(availableMeshList[1].first, availableMeshList[1].second));

    instance->positions[0][0] = SimpleMath::Vector3(-1.5f, 2.0f, -1.0f);
    instance->positions[0][1] = SimpleMath::Vector3(-0.5f, 2.0f, -1.0f);
    instance->positions[0][2] = SimpleMath::Vector3(0.5f, 2.0f, -1.0f);
    instance->positions[0][3] = SimpleMath::Vector3(1.5f, 2.0f, -1.0f);

    instance->positions[1][0] = SimpleMath::Vector3(-1.5f, 1.0f, -2.0f);
    instance->positions[1][1] = SimpleMath::Vector3(-0.5f, 1.0f, -2.0f);
    instance->positions[1][2] = SimpleMath::Vector3(0.5f, 1.0f, -2.0f);
    instance->positions[1][3] = SimpleMath::Vector3(1.5f, 1.0f, -2.0f);

    instance->positions[2][0] = SimpleMath::Vector3(-1.5f, 0.0f, -3.0f);
    instance->positions[2][1] = SimpleMath::Vector3(-0.5f, 0.0f, -3.0f);
    instance->positions[2][2] = SimpleMath::Vector3(0.5f, 0.0f, -3.0f);
    instance->positions[2][3] = SimpleMath::Vector3(1.5f, 0.0f, -3.0f);

    instance->positions[3][0] = SimpleMath::Vector3(-1.5f, -1.0f, -4.0f);
    instance->positions[3][1] = SimpleMath::Vector3(-0.5f, -1.0f, -4.0f);
    instance->positions[3][2] = SimpleMath::Vector3(0.5f, -1.0f, -4.0f);
    instance->positions[3][3] = SimpleMath::Vector3(1.5f, -1.0f, -4.0f);

    instance->positions[4][0] = SimpleMath::Vector3(-1.5f, -1.0f, -5.0f);
    instance->positions[4][1] = SimpleMath::Vector3(-0.5f, -1.0f, -5.0f);
    instance->positions[4][2] = SimpleMath::Vector3(0.5f, -1.0f, -5.0f);
    instance->positions[4][3] = SimpleMath::Vector3(1.5f, -1.0f, -5.0f);
}

SceneManager* SceneManager::Get()
{
	return instance;
}

void SceneManager::LoadAllScenes()
{
    //for (int i = 0; i < 5; i++)
    //{
    //    // add all total vertices of listed model in [SECOND]
    //    for (int j = 0; j < sceneArray[i].modelInfoList.size(); j++)
    //    {
    //        if (sceneArray[i].loadState == LoadState::isUnloaded);
    //            sceneArray[i].TOTAL_VERTICES +=sceneArray[i].modelInfoList[j].second;
    //    }
    //}    

    //for (int i = 0; i < 5; i++)
    //{
    //    if (instance->sceneArray[i].loadState == isUnloaded)
    //    {
    //        instance->InitializeScene((SceneID)i);
    //        // create mesh from the path of the models [FIRST]
    //        for (int j = 0; j < sceneArray[i].modelInfoList.size(); j++)
    //        {
    //            if (sceneArray[i].loadState == LoadState::isUnloaded);
    //                GraphicsEngine::get()->getMeshManager()->CreateMesh(sceneArray[i].modelInfoList[j].first, " ", sceneArray[i].id);
    //        }
    //    }
    //    
    //}

    for (int i = 0; i < 5; i++)
    {
        LoadScene((SceneID)i);
    }    
}

void SceneManager::LoadScene(SceneID scene)
{
    if (instance->getScene(scene).loadState == SceneManager::LoadState::isUnloaded)
    {
        instance->InitializeScene(scene);
        instance->SetSceneState(scene, SceneManager::LoadState::isLoading);
        // add all total vertices of listed model in [SECOND]
        for (int j = 0; j < sceneArray[(int)scene].modelInfoList.size(); j++)
        {
            sceneArray[(int)scene].TOTAL_VERTICES += sceneArray[(int)scene].modelInfoList[j].second;
        }



        // create mesh from the path of the models [FIRST]
        for (int j = 0; j < sceneArray[(int)scene].modelInfoList.size(); j++)
        {
            GraphicsEngine::get()->getMeshManager()->CreateMesh(sceneArray[(int)scene].modelInfoList[j].first, " ", sceneArray[(int)scene].id);
        }
    }
    

    
}

void SceneManager::SetSceneObjPosition(SceneID scene, GameObject* obj, SimpleMath::Vector3 position)
{
    for (int i = 0; i < sceneArray[(int)scene].sceneGameObjectList.size(); i++)
    {
        if (obj == sceneArray[(int)scene].sceneGameObjectList[i])
        {
            sceneArray[(int)scene].sceneGameObjectList[i]->GetTransform()->SetPosition(position);
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

void SceneManager::InitializeScene(SceneID scene)
{
    switch (scene)
    {
    case A:
    {
        sceneArray[0].isLoaded = false;
        sceneArray[0].loadState = LoadState::isUnloaded;
        sceneArray[0].id = SceneID::A;
        sceneArray[0].TOTAL_VERTICES = 0;
        sceneArray[0].LOADED_VERTICES = 0;
        sceneArray[0].isLoaded = false;
        sceneArray[0].isUnloading = false;
    }

    break;
    case B:
    {
        sceneArray[1].isLoaded = false;
        sceneArray[1].loadState = LoadState::isUnloaded;
        sceneArray[1].id = SceneID:: B;
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
        sceneArray[2].id = SceneID::C;
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
        sceneArray[3].id = SceneID::D;
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
        sceneArray[4].id = SceneID::E;
        sceneArray[4].TOTAL_VERTICES = 0;
        sceneArray[4].LOADED_VERTICES = 0;
        sceneArray[4].isLoaded = false;
        sceneArray[4].isUnloading = false;
    }

    break;
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

void SceneManager::EnableSceneModels(bool isEnabled, SceneID scene)
{
  
    Scene* sceneInstance = nullptr;
    switch (scene)
    {
    case A:sceneInstance = &(instance->sceneArray[0]); break;
    case B:sceneInstance = &(instance->sceneArray[1]); break;
    case C:sceneInstance = &(instance->sceneArray[2]); break;
    case D:sceneInstance = &(instance->sceneArray[3]); break;
    case E:sceneInstance = &(instance->sceneArray[4]); break;
    }
    
    for (int i = 0; i < sceneInstance->sceneGameObjectList.size(); i++)
    {
        std::cout << "isEnabled" << (int)isEnabled << std::endl;
        sceneInstance->sceneGameObjectList[i]->SetEnable(isEnabled);
    }
}

void SceneManager::AddModelToScene(SceneID scene, GameObject* obj)
{
    Scene* sceneInstance = nullptr;
    switch (scene)
    {
    case A:sceneInstance = &(instance->sceneArray[0]); break;
    case B:sceneInstance = &(instance->sceneArray[1]); break;
    case C:sceneInstance = &(instance->sceneArray[2]); break;
    case D:sceneInstance = &(instance->sceneArray[3]); break;
    case E:sceneInstance = &(instance->sceneArray[4]); break;
    }

    sceneInstance->sceneGameObjectList.push_back(obj);
}

void SceneManager::SetSceneState(SceneID scene, LoadState state)
{
    Scene* sceneInstance = nullptr;
    switch (scene)
    {
    case A:sceneInstance = &(instance->sceneArray[0]); break;
    case B:sceneInstance = &(instance->sceneArray[1]); break;
    case C:sceneInstance = &(instance->sceneArray[2]); break;
    case D:sceneInstance = &(instance->sceneArray[3]); break;
    case E:sceneInstance = &(instance->sceneArray[4]); break;
    }

    sceneInstance->loadState = state;
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
        sceneArray[0].isUnloading = true;
        for (int i = 0; i < sceneArray[0].sceneGameObjectList.size(); i++)
        {
            GameObjectManager::Get()->DestroyObject(sceneArray[0].sceneGameObjectList[i]);
        }
        sceneArray[0].sceneGameObjectList.clear();

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
        sceneArray[1].isUnloading = true;
        for (int i = 0; i < sceneArray[0].sceneGameObjectList.size(); i++)
        {
            GameObjectManager::Get()->DestroyObject(sceneArray[1].sceneGameObjectList[i]);
        }
        sceneArray[1].sceneGameObjectList.clear();
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
        sceneArray[2].isUnloading = true;

        for (int i = 0; i < sceneArray[2].sceneGameObjectList.size(); i++)
        {
            GameObjectManager::Get()->DestroyObject(sceneArray[2].sceneGameObjectList[i]);
        }
        sceneArray[2].sceneGameObjectList.clear();
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
        sceneArray[3].isUnloading = true;

        for (int i = 0; i < sceneArray[3].sceneGameObjectList.size(); i++)
        {
            GameObjectManager::Get()->DestroyObject(sceneArray[3].sceneGameObjectList[i]);
        }
        sceneArray[3].sceneGameObjectList.clear();
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
        sceneArray[4].isUnloading = true;

        for (int i = 0; i < sceneArray[4].sceneGameObjectList.size(); i++)
        {
            GameObjectManager::Get()->DestroyObject(sceneArray[4].sceneGameObjectList[i]);
        }
        sceneArray[4].sceneGameObjectList.clear();
    }
    break;
    }
}

void SceneManager::ResetAll()
{
    for (int i = 0; i < 5; i++)
    {
        ResetScene((SceneID)i);
    }
}

void SceneManager::EnableScene(bool flag, SceneID id)
{
    Scene* sceneInstance = nullptr;
    switch (id)
    {
    case A:sceneInstance = &(instance->sceneArray[0]); break;
    case B:sceneInstance = &(instance->sceneArray[1]); break;
    case C:sceneInstance = &(instance->sceneArray[2]); break;
    case D:sceneInstance = &(instance->sceneArray[3]); break;
    case E:sceneInstance = &(instance->sceneArray[4]); break;
    }

    sceneInstance->isActive = flag;
    EnableSceneModels(flag, id);
}





