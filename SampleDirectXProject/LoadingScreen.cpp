#include "LoadingScreen.h"
#include "SceneManager.h"
#include <string>
#include "EngineTime.h"

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

	ImGui::Begin("Loading Menu", &isActive, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
	ImGui::Text("Summary Loading Progress");
	progressSummary = ((float)(SceneManager::Get()->SCENES_LOADED_VERTICES)) / ((float)(SceneManager::Get()->SCENES_TOTAL_VERTICES));
	if (std::isnan(progressSummary))
		progressSummary = 0;

	progressSummary *= 100;

	ImGui::SliderFloat("Loading Summary", &progressSummary, 0, 100);
	ImGui::SameLine();
	if (ImGui::Button("Load All"))
	{
		SceneManager::Get()->LoadAllScenes();
	}
	ImGui::SameLine();
	if (ImGui::Button("Unload All"))
	{
		SceneManager::Get()->ResetAll();
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("Enable All", &isAllEnabled))
	{
		for (int i = 0; i < 5; i++)
		{
			SceneManager::Get()->EnableScene(isAllEnabled, (SceneManager::SceneID)i);
			isEnabled[i] = isAllEnabled;
		}
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
		std::cout << "Loaded: " << ((float)(SceneManager::Get()->sceneArray[i].LOADED_VERTICES)) << " | " << "Total: " << (SceneManager::Get()->sceneArray[i].TOTAL_VERTICES) << std::endl;
		progress[i] = ((float)(SceneManager::Get()->sceneArray[i].LOADED_VERTICES)) / ((float)(SceneManager::Get()->sceneArray[i].TOTAL_VERTICES));
		if (std::isnan(progress[i]))
			progress[i] = 0;

		progress[i] *= 100;

		ImGui::SliderFloat((name + id + loading).c_str(), &progress[i], 0, 100);
		ImGui::SameLine();

		string Toggle = "Enable ";
		string unload = "Unload ";
		string load = "Load ";
		if (ImGui::Button((load + name + id).c_str()))
		{
			// load
			SceneManager::Get()->LoadScene((SceneManager::SceneID)i);
		}
		ImGui::SameLine();
		if (ImGui::Button((unload + name + id).c_str()))
		{
			SceneManager::Get()->ResetScene((SceneManager::SceneID)i);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox((Toggle + name + id).c_str(),&isEnabled[i]))
		{
			if (!isEnabled[i])
			{
				isAllEnabled = false;
			}
			cout << "Imgui: " << isEnabled << std::endl;
			SceneManager::Get()->EnableScene(isEnabled[i], (SceneManager::SceneID)i);
		}
	}
	string FPS = std::to_string(EngineTime::getFPS());
	ImGui::Text(("FPS: " + FPS).c_str());
	ImGui::End();

	
}
