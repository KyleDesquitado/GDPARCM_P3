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

	ImGui::Begin("Loading Menu", &isActive, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Summary Loading Progress");
	ImGui::SliderFloat(("Selected Scene"), &progress[0], 0, 100);
	ImGui::SameLine();
	if (ImGui::Button("Load All"))
	{
		SceneManager::Get()->LoadAllScenes();
	}
	ImGui::SameLine();
	if (ImGui::Button("Unload All"))
	{
		
	}

	ImGui::Separator();
	ImGui::Text("Scenes Loading Progress");
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
		ImGui::SameLine();

		string Toggle = "Toggle ";
		string unload = "Unload ";
		string load = "Load ";
		if (ImGui::Button((load + name + id).c_str()))
		{

		}
		ImGui::SameLine();
		if (ImGui::Button((unload + name + id).c_str()))
		{

		}
		ImGui::SameLine();
		if (ImGui::Checkbox((Toggle + name + id).c_str(),&isEnabled))
		{
			cout << "Imgui: " << isEnabled << std::endl;
			SceneManager::Get()->EnableSceneModels(isEnabled, (SceneManager::SceneID)i);
		}
	}
	

	ImGui::End();
}
