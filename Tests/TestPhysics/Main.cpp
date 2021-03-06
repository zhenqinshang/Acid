#include <iostream>
#include <Files/Files.hpp>
#include <Helpers/FileSystem.hpp>
#include <Inputs/Mouse.hpp>
#include <Renderer/Renderer.hpp>
#include <Scenes/Scenes.hpp>
#include "Configs/ConfigManager.hpp"
#include "MainRenderer.hpp"
#include "MainUpdater.hpp"
#include "Scenes/FpsPlayer.hpp"
#include "Scenes/Scene1.hpp"
#include "Skybox/CelestialBody.hpp"
#include "Skybox/SkyboxCycle.hpp"
#include "World/World.hpp"

using namespace test;
using namespace acid;

//#if (ACID_BUILD_RELEASE && ACID_BUILD_WINDOWS)
//int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
//#else
int main(int argc, char **argv)
//#endif
{
	// Registers file search paths.
//	Files::AddSearchPath("Resources/Game");
	Files::AddSearchPath("Resources/Engine");

	// Creates the engine and updater objects.
	auto engine = new Engine();
	engine->SetUpdater(new MainUpdater());

	// auto configManager = std::make_shared<ConfigManager>();
	fprintf(stdout, "Working Directory: %s\n", FileSystem::GetWorkingDirectory().c_str());

	// Registers modules.
	Engine::Get()->RegisterModule<World>(UPDATE_NORMAL);
//	Engine::Get()->DeregisterModule<Shadows>();

	// Registers components.
	Scenes::Get()->RegisterComponent<FpsPlayer>("FpsPlayer");
	Scenes::Get()->RegisterComponent<CelestialBody>("CelestialBody");
	Scenes::Get()->RegisterComponent<SkyboxCycle>("SkyboxCycle");

	// Initializes modules.
	Display::Get()->SetTitle("Test Physics");
	Display::Get()->SetIcon("Logos/Flask.png");
	Mouse::Get()->SetCustomMouse("Guis/Cursor.png");
	Renderer::Get()->SetManager(new MainRenderer());
	Scenes::Get()->SetScene(new Scene1());

	// Runs the game loop.
	auto exitCode = engine->Run();
	delete engine;

	// Pauses the console.
	std::cin.get();
	return exitCode;
}
