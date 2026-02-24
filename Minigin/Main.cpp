#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include"RenderComponent.h"
#include"GameObject.h"
#include"TextComponent.h"
#include"FPSComponent.h"
#include"SineMovementComponent.h"
#include <filesystem>

namespace fs = std::filesystem;


void CreationOfGameObjectsAndComponents(dae::Scene& scene);

static void load()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Scene1");

	//
	auto pRotatingBallParent = std::make_shared<dae::GameObject>();  //make a game object

	auto pParentRenderer = std::make_shared<dae::RenderComponent>();
	pParentRenderer->SetTexture("Balloom.png");
	pRotatingBallParent->AddComponent(pParentRenderer);  //add renderer to r
	pRotatingBallParent->SetPosition(100, 230);

	const glm::vec3 origin{ 300.f,320.f,0.f };
	constexpr float length{ 50.f }, cycleTime{ 5.f };
	auto sineMovementParent = std::make_shared<dae::SineMovementComponent>(origin, length, cycleTime);
	pRotatingBallParent->AddComponent(sineMovementParent);


	auto pRotatingBallChild = std::make_shared<dae::GameObject>();
	auto pChildRenderer = std::make_shared<dae::RenderComponent>();
	pChildRenderer->SetTexture("Oneal.png");
	pRotatingBallChild->AddComponent(pChildRenderer);
	auto sineMovementChild = std::make_shared<dae::SineMovementComponent>(glm::vec3{ 0.f,0.f,0.f }, length * 2.f, cycleTime);
	pRotatingBallChild->AddComponent(sineMovementChild);

	pRotatingBallParent->AddChild(pRotatingBallChild, true); //set as child 

	//Only Add Parent to the scene 

	scene.Add(pRotatingBallParent);


	CreationOfGameObjectsAndComponents(scene);
}

void CreationOfGameObjectsAndComponents(dae::Scene& scene)
{
	auto pLogoImage = std::make_shared<dae::GameObject>();
	auto pLogoRender = std::make_shared<dae::RenderComponent>();
	pLogoRender->SetTexture("logo.png");
	pLogoImage->AddComponent(pLogoRender);
	pLogoImage->SetPosition(210, 200);

	scene.Add(pLogoImage);

	auto pTextImage = std::make_shared<dae::GameObject>();

	auto pTextRenderer = std::make_shared<dae::RenderComponent>();
	auto pProgTextComponent = std::make_shared<dae::TextComponent>(pTextRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	pProgTextComponent->SetTextToTexture("Programming 4 Assignment");

	pTextImage->AddComponent(pTextRenderer);
	pTextImage->SetPosition(80, 50);
	scene.Add(pTextImage);

	auto pBackgroundImage = std::make_shared<dae::GameObject>(100);

	auto pBackgroundRender = std::make_shared<dae::RenderComponent>(0);
	pBackgroundRender->SetTexture("background.png");

	pBackgroundImage->AddComponent(pBackgroundRender);
	scene.Add(pBackgroundImage);

	auto pCounterFPS = std::make_shared<dae::GameObject>();


	auto pFrameRateRenderer = std::make_shared<dae::RenderComponent>();
	auto pTextComponent = std::make_shared<dae::TextComponent>(pFrameRateRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
	pTextComponent->SetColor({ 200,200,0 });

	pCounterFPS->AddComponent(pTextComponent);

	auto pFPSComponent = std::make_shared<dae::FPSComponent>(pCounterFPS->GetComponent<dae::TextComponent>());

	pCounterFPS->AddComponent(pFrameRateRenderer);
	pCounterFPS->AddComponent(pFPSComponent);

	pCounterFPS->SetPosition(10.f, 10.f);
	scene.Add(pCounterFPS);

}


int main(int, char* []) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
	return 0;
}
