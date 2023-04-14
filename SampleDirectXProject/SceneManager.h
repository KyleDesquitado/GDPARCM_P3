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
public:
	struct Scene
	{
        SceneID id = SceneID::NOT_SET;
        int TOTAL_VERTICES = 0;
        int LOADED_VERTICES = 0;
        bool isLoaded = false;
        std::vector<ModelInfoPair> modelList;
	};


public:
    Scene sceneArray[5];
    Scene SceneA;
    Scene SceneB;
    Scene SceneC;
    Scene SceneD;
    Scene SceneE;
public:

    void LoadAllScenes();
    void UpdateSceneState(SceneID scene);
    void initializeScene(SceneID scene);
};