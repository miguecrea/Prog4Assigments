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

#include <filesystem>
namespace fs = std::filesystem;


void CreationOfGameObjectsAndComponents(dae::Scene & scene);

static void load()
{


	// Logo and BackGround 

	auto & scene = dae::SceneManager::GetInstance().CreateScene("Scene1");

	CreationOfGameObjectsAndComponents(scene);



	//auto go = std::make_unique<dae::GameObject>();
	//go->SetTexture("background.png");
	//scene.Add(std::move(go));

	//go = std::make_unique<dae::GameObject>();
	//go->SetTexture("logo.png");
	//go->SetPosition(358, 180);
	//scene.Add(std::move(go));

	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_unique<dae::TextObject>("Programming 4 Assignment", font);
	//to->SetColor({ 255, 255, 0, 255 });
	//to->SetPosition(292, 20);
	//scene.Add(std::move(to));
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


int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
