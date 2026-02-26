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
#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>
#include"CombinedGraphComponent.h"

namespace fs = std::filesystem;

void CreationOfGameObjectsAndComponents(dae::Scene & scene);
float CalculateAverage(std::vector<float>& testResults);
float CalculateAverage(std::vector<float>& testResults)
{
	const int tenPercent{ static_cast<int>(testResults.size() * 0.1f) };

	std::sort(testResults.begin(), testResults.end());

	const float totalTime{ std::accumulate(testResults.begin() + tenPercent, testResults.end() - tenPercent, 0.f) };
	const float averageTime{ totalTime / (testResults.size() - 2 * tenPercent) };

	return averageTime;
}

struct TransformX
{
	float matrix[16] =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class GameObject3D
{
public:
	TransformX transform{};
	int ID{};
};

class GameObject3DAlt
{
public:
	TransformX* transform{};
	int ID{};
};







static void load()
{

	auto & scene = dae::SceneManager::GetInstance().CreateScene("Scene1");

	//
	auto pRotatingBallParent = std::make_shared<dae::GameObject>();  //make a game object

	auto pParentRenderer = std::make_shared<dae::RenderComponent>();
	pParentRenderer->SetTexture("Balloom.png");
	pRotatingBallParent->AddComponent(pParentRenderer);  //add renderer to r
	pRotatingBallParent->SetPosition(200, 230);

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







	 auto pTrashTheCasheObject_01{ std::make_shared<dae::GameObject>() }; 

	 pTrashTheCasheObject_01->SetPosition(700.f, 200.f);
		//////////////////
	auto testFunction_01 = [&](std::vector<float>& xValues, std::vector<float>& yValues, int nrTests, int nrTestValues)
		{
			xValues.clear();
			yValues.clear();

			int* values{ new int[nrTestValues] {} };
			std::vector<float> testResults{};

			for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
			{
				for (int testIndex{ 0 }; testIndex < nrTests; ++testIndex)
				{
					const auto start{ std::chrono::high_resolution_clock::now() };
					for (int index{}; index < nrTestValues; index += stepsize)
					{
						values[index] *= 2;
					}
					const auto end{ std::chrono::high_resolution_clock::now() };
					const auto elapsedTime{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
					testResults.push_back(elapsedTime / 1000.f);
				}

				xValues.push_back(static_cast<float>(stepsize));
				yValues.push_back(CalculateAverage(testResults));

				testResults.clear();
			}
			delete[] values;
		};

	auto pGraphComponent_01{ std::make_shared<dae::GraphComponent>(testFunction_01, "Excercise 01") };
	pTrashTheCasheObject_01->AddComponent(pGraphComponent_01);

	scene.Add(pTrashTheCasheObject_01);


	///


	auto pTrashTheCasheObject_02{ std::make_shared<dae::GameObject>() };

	auto testFunction_02 = [&](std::vector<float>& xValues, std::vector<float>& yValues, int nrTests, int nrTestValues)
		{
			xValues.clear();
			yValues.clear();

			GameObject3D * values{ new GameObject3D[nrTestValues] {} };
			std::vector<float> testResults{};

			for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
			{
				for (int testIndex{ 0 }; testIndex < nrTests; ++testIndex)
				{
					const auto start{ std::chrono::high_resolution_clock::now() };
					for (int index{}; index < nrTestValues; index += stepsize)
					{
						values[index].ID *= 2;
					}
					const auto end{ std::chrono::high_resolution_clock::now() };
					const auto elapsedTime{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
					testResults.push_back(elapsedTime / 1000.f);
				}

				xValues.push_back(static_cast<float>(stepsize));
				yValues.push_back(CalculateAverage(testResults));

				testResults.clear();
			}
			delete[] values;
		};

	auto testFunction_03 = [&](std::vector<float>& xValues, std::vector<float>& yValues, int nrTests, int nrTestValues)
		{
			xValues.clear();
			yValues.clear();

			GameObject3DAlt * values{ new GameObject3DAlt[nrTestValues] {} };
			std::vector<float> testResults{};

			for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
			{
				for (int testIndex{ 0 }; testIndex < nrTests; ++testIndex)
				{
					const auto start{ std::chrono::high_resolution_clock::now() };
					for (int index{}; index < nrTestValues; index += stepsize)
					{
						values[index].ID *= 2;
					}
					const auto end{ std::chrono::high_resolution_clock::now() };
					const auto elapsedTime{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
					testResults.push_back(elapsedTime / 1000.f);

					std::cout << "Step size: " << stepsize
						<< ", Test Index: " << testIndex
						<< ", Time (ms): " << elapsedTime / 1000.f
						<< std::endl;
				}

				xValues.push_back(static_cast<float>(stepsize));
				yValues.push_back(CalculateAverage(testResults));


				//std::cout << xValues[stepsize] << "\n";

				testResults.clear();
			}
			delete[] values;
		};

	auto pGraphComponent_02{ std::make_shared<dae::CombinedGraphComponent>(testFunction_02,testFunction_03, "Excercise 02") };
	pTrashTheCasheObject_02->AddComponent(pGraphComponent_02);

	scene.Add(pTrashTheCasheObject_02);



	CreationOfGameObjectsAndComponents(scene);
}

void CreationOfGameObjectsAndComponents(dae::Scene& scene)
{
	auto pLogoImage = std::make_shared<dae::GameObject>();
	auto pLogoRender = std::make_shared<dae::RenderComponent>();
	pLogoRender->SetTexture("logo.png");
	pLogoImage->AddComponent(pLogoRender);
	pLogoImage->SetPosition(400, 200);

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
