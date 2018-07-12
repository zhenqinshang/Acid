#include <iostream>
#include <Animations/MaterialAnimated.hpp>
#include <Animations/MeshAnimated.hpp>
#include <Files/Files.hpp>
#include <Files/Json/FileJson.hpp>
#include <Helpers/FileSystem.hpp>
#include <Inputs/Mouse.hpp>
#include <Renderer/Renderer.hpp>
#include <Scenes/Scenes.hpp>
#include "World/World.hpp"
#include "Configs/ConfigManager.hpp"
#include "MainUpdater.hpp"
#include "MainRenderer.hpp"
#include "Scenes/FpsPlayer.hpp"
#include "Scenes/Scene1.hpp"

using namespace test;
using namespace fl;

//#if (FL_BUILD_RELEASE && FL_BUILD_WINDOWS)
//int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
//#else
int main(int argc, char **argv)
//#endif
{
	// Registers file search paths.
	Files::AddSearchPath("Resources/Engine");
	Files::AddSearchPath("Resources/Editor");

	// Creates the engine and updater objects.
	auto engine = std::make_shared<Engine>();
	engine->SetUpdater(std::make_shared<MainUpdater>());

//	auto modelAnimated = new MeshAnimated("Objects/Animated/Model.json");
//	return 0;

	auto configManager = std::make_shared<ConfigManager>();
	printf("Working Directory: %s\n", FileSystem::GetWorkingDirectory().c_str());

	// Registers modules.
//	Engine::Get()->RegisterModule<Example>(UPDATE_NORMAL);
	Engine::Get()->RegisterModule<World>(UPDATE_NORMAL);
//	Engine::Get()->DeregisterModule<Shadows>();

	// Registers components.
	Scenes::Get()->RegisterComponent<FpsPlayer>("FpsPlayer");
	Scenes::Get()->RegisterComponent<MaterialAnimated>("MaterialAnimated");

	// Initializes modules.
	Display::Get()->SetTitle("Flounder Editor");
	Display::Get()->SetIcon("Logos/Tail.png");
	Mouse::Get()->SetCustomMouse("Guis/Cursor.png");
	Renderer::Get()->SetManager(std::make_shared<MainRenderer>());
	Scenes::Get()->SetScene(std::make_shared<Scene1>());

	// Runs the game loop.
	auto exitCode = engine->Run();

	// Pauses the console.
//	std::cin.get();
	return exitCode;
}
