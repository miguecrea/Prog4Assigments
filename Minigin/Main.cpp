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
#include"Input/Command.h"
#include"Input/SetPositionCommand.h"
#include"Input/UpdatePositionCommand.h"
#include"Input/InputManager.h"
#include"Input/Keyboard.h"
#include"Input/Controller.h"

namespace fs = std::filesystem;


void CreationOfGameObjectsAndComponents(dae::Scene& scene);

static void load()
{


	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& input = dae::InputManager::GetInstance();


	float setSpeed{ 100.f };
	float updateSpeed{ 150.f };

	auto pPlayer1 = std::make_shared<dae::GameObject>();

	auto pPlayer1Renderer = std::make_shared<dae::RenderComponent>();
	pPlayer1Renderer->SetTexture("Balloom.png");
	pPlayer1->AddComponent(pPlayer1Renderer);
	pPlayer1->SetPosition(100, 100);
	scene.Add(pPlayer1);

	auto controller{ input.AddController() };



	glm::vec3 direction{ 0.f,-setSpeed,0.f };
	std::unique_ptr<dae::Command> pMoveCommand{ std::make_unique<dae::SetPositionCommand>(pPlayer1.get(), direction) };  //player 1 and direction
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonY, std::move(pMoveCommand), dae::ButtonState::Down);


	direction = { 0.f,setSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::move(pMoveCommand), dae::ButtonState::Down);



	direction = { -setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonX, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonB, std::move(pMoveCommand), dae::ButtonState::Down);



	direction = { 0.f,-updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadUp, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadDown, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadLeft, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer1.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadRight, std::move(pMoveCommand), dae::ButtonState::Pressed);




	setSpeed *= 0.5f;
	updateSpeed *= 0.5f;

	auto pPlayer2 = std::make_shared<dae::GameObject>();  //PLAYER 2  

	auto pPlayer2Renderer = std::make_shared<dae::RenderComponent>();
	pPlayer2Renderer->SetTexture("Oneal.png");
	pPlayer2->AddComponent(pPlayer2Renderer);
	pPlayer2->SetPosition(200, 200);
	scene.Add(pPlayer2);


	auto keyboard{ input.GetKeyboard() };

	direction = { 0.f,-setSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_UP, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { 0.f,setSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_DOWN, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { -setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_LEFT, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_RIGHT, std::move(pMoveCommand), dae::ButtonState::Down);




	direction = { 0.f,-updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_W, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_S, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_A, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	keyboard->MapCommandToButton(SDL_SCANCODE_D, std::move(pMoveCommand), dae::ButtonState::Pressed);

	controller = { input.AddController() };

	direction = { 0.f,-setSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonY, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { 0.f,setSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonA, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { -setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonX, std::move(pMoveCommand), dae::ButtonState::Down);

	direction = { setSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::SetPositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::ButtonB, std::move(pMoveCommand), dae::ButtonState::Down);

	//Button pressed
	direction = { 0.f,-updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadUp, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { 0.f,updateSpeed,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadDown, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { -updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadLeft, std::move(pMoveCommand), dae::ButtonState::Pressed);

	direction = { updateSpeed,0.f,0.f };
	pMoveCommand = { std::make_unique<dae::UpdatePositionCommand>(pPlayer2.get(), direction) };
	controller->MapCommandToButton(dae::Controller::ControllerButtons::DPadRight, std::move(pMoveCommand), dae::ButtonState::Pressed);





	auto pTextImage = std::make_shared<dae::GameObject>();
	auto pTextRenderer = std::make_shared<dae::RenderComponent>();
	auto pProgTextComponent = std::make_shared<dae::TextComponent>(pTextRenderer, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	pProgTextComponent->SetTextToTexture("Use the D-Pad to move Pacman");
	pTextImage->AddComponent(pTextRenderer);
	pTextImage->SetPosition(80, 90);

	auto pTextImage2 = std::make_shared<dae::GameObject>();
	auto pTextRenderer2 = std::make_shared<dae::RenderComponent>();
	auto pProgTextComponent2 = std::make_shared<dae::TextComponent>(pTextRenderer2, dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	pProgTextComponent2->SetTextToTexture("Use the WASD to move MRS Pacman");
	pTextImage2->AddComponent(pTextRenderer2);
	pTextImage2->SetPosition(80, 140);


	scene.Add(pTextImage);
	scene.Add(pTextImage2);
	CreationOfGameObjectsAndComponents(scene);
}

void CreationOfGameObjectsAndComponents(dae::Scene& scene)
{
	auto pLogoImage = std::make_shared<dae::GameObject>();
	auto pLogoRender = std::make_shared<dae::RenderComponent>();
	pLogoRender->SetTexture("logo.png");
	pLogoImage->AddComponent(pLogoRender);
	pLogoImage->SetPosition(390, 200);

	scene.Add(pLogoImage);



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
