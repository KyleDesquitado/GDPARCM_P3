#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "GameObject.h"
#include "SimpleMath.h"
#include <reactphysics3d/reactphysics3d.h>
#include "SceneManager.h"
#include "MeshManager.h"

using namespace reactphysics3d;
using namespace DirectX;

class GameObject;
class GameObjectManager
{
private:
	static GameObjectManager* instance;

public:
	GameObjectManager();

public:
	static void Initialize();
	static GameObjectManager* Get();

public:
	void Update();

public:
	void CreateGameObject();
	GameObject* CreateCube();
	void CreateCubes(int amount);
	void CreatePhysicsCubes(int amount);
	GameObject* CreatePlane();
	void CreateTeapot();
	void CreateBunny();
	void CreateArmadillo();
	void CreateLucy();
	GameObject* CreateSphere();
	GameObject* CreateCapsule();
	GameObject* CreateCylinder();

public:
	GameObject* FindObjectByName(std::string name);
	void ApplyEditorAction(class EditorAction* action);

public:
	void CreateMesh(Mesh* mesh, SceneManager::SceneID id);
	void CreateScene1ObjSet();
	void CreateScene2ObjSet();
	void CreateScene3ObjSet();
	void CreateScene4ObjSet();
	void CreateScene5ObjSet();
	void CreateObjectFromFile(std::string name, PrimitiveType type, SimpleMath::Vector3 position, SimpleMath::Vector3 rotation, SimpleMath::Vector3 scale, bool hasPhysics);

public:
	void SaveEditStates();
	void RestoreEditStates();

public:
	void SelectGameObject(GameObject* inObj);
	GameObject* GetSelectedGameObject() const;

public:
	const std::vector<GameObject*>& GetGameObjectList() const;
	const std::vector<GameObject*> GetRoots() const;

private:
	std::vector<GameObject*> gameObjectList;
	std::unordered_map<std::string, GameObject*> gameObjectMap;
	GameObject* selectedObj;

public:
	PhysicsWorld* GetPhysicsWorld();
	PhysicsCommon* GetPhysicsCommon();

	
private:
	PhysicsCommon* physicsCommon;
	PhysicsWorld* physicsWorld;
};

