#include "LoadingScreen.h"
#include "SceneManager.h"
#include <string>;

LoadingScreen::LoadingScreen(): UIScreen("LoadingScreen", true)
{
	for (int i = 0; i < 5; i++)
	{
		progress[i] = 0;
	}
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::DrawUI()
{

	ImGui::Begin("LoadingScreen", &isActive); 

	string name = "Scene ";
	string id = " ";
	string loading = " Loading Bar";
	
	for (int i = 0; i < 5; i++)
	{
		string id = std::to_string(i);
		// 0-100
		//progress[i] = ((float)SceneManager::Get()->sceneArray[1].LOADED_VERTICES / (float)SceneManager::Get()->sceneArray[i].TOTAL_VERTICES) * 100;
		//ImGui::SliderFloat("Scene 1 Loading Bar", &progress[i], 0, 100);

		// min to max vertices
		progress[i] = SceneManager::Get()->sceneArray[i].LOADED_VERTICES;
		ImGui::SliderFloat((name+id+loading).c_str(), &progress[i], 0, (float)SceneManager::Get()->sceneArray[i].TOTAL_VERTICES);
	}
	

	ImGui::End();
}
