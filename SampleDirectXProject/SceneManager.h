#pragma once
#include <vector>
#include <array>
#include <functional>
#include "GameObject.h"
#include "SimpleMath.h"
#include "IETSemaphore.h"
using namespace DirectX;
typedef std::pair<const wchar_t*, int> ModelInfoPair;
using namespace DirectX;

class SceneManager
{
private:
    static SceneManager* instance;
   /* std::vector <const wchar_t*> availableModelPathList;*/
    std::vector<ModelInfoPair> availableMeshList;
    
public:
    SceneManager();
    IETSemaphore* mutex[5];
    SimpleMath::Vector3 positions[5][4];
public:
    static void Initialize();
    static SceneManager* Get();

public :
    enum SceneID
    {
        NOT_SET = -1,
        A = 0,
        B = 1,
        C = 2,
        D = 3,
        E = 4,
    };

    enum LoadState
    {
        isLoading,
        isLoaded,
        isUnloaded
    };
public:
	struct Scene
	{
        bool isActive = false;
        LoadState loadState = LoadState::isUnloaded;
        SceneID id = SceneID::NOT_SET;
        int TOTAL_VERTICES = 0;
        int LOADED_VERTICES = 0;
        bool isLoaded = false;
        bool isUnloading = false;
        std::vector<ModelInfoPair> modelInfoList;
        std::vector <GameObject*>sceneGameObjectList;
        //std::unordered_map<ModelInfoPair, Mesh*> meshMap;
	};


public:
    Scene sceneArray[5];
public:

    void LoadAllScenes();
    void UpdateSceneState(SceneID scene);
    void InitializeScene(SceneID scene);
    void UnloadScene(SceneID scene);
    Scene getScene(SceneID scene);
    void EnableSceneModels(bool isEnabled, SceneID scene);
    void AddModelToScene(SceneID scene, GameObject* obj);
    void SetSceneObjPosition(SceneID scene, GameObject* obj, SimpleMath::Vector3 position);
    void SetSceneState(SceneID scene, LoadState state);

public:
    void LoadScene(SceneID scene);
    void ResetScene(SceneID scene);
    void ResetAll();
    void EnableScene(bool flag, SceneID id);

};