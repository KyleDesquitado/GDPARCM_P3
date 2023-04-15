#pragma once
#include <vector>
#include <array>

typedef std::pair<const wchar_t*, int> ModelInfoPair;
class SceneManager
{
private:
    static SceneManager* instance;
   /* std::vector <const wchar_t*> availableModelPathList;*/
    std::vector<ModelInfoPair> availableMeshList;

public:
    SceneManager();

public:
    static void Initialize();
    static SceneManager* Get();

public :
    enum SceneID
    {
        NOT_SET = 0,
        A = 1,
        B = 2,
        C = 3,
        D = 4,
        E = 5,
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
        LoadState loadState = LoadState::isUnloaded;
        SceneID id = SceneID::NOT_SET;
        int TOTAL_VERTICES = 0;
        int LOADED_VERTICES = 0;
        bool isLoaded = false;
        bool isUnloading = false;
        std::vector<ModelInfoPair> modelList;
	};


public:
    Scene sceneArray[5];
public:

    void LoadAllScenes();
    void UpdateSceneState(SceneID scene);
    void LoadScene(SceneID scene);
    void UnloadScene(SceneID scene);
    Scene getScene(SceneID scene);

public:
    void ResetScene(SceneID scene);
};