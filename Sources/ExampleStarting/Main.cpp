#include <iostream>
#include <Files/Json/FileJson.hpp>
#include <Helpers/FileSystem.hpp>
#include <Inputs/Mouse.hpp>
#include <Renderer/Renderer.hpp>
#include <Scenes/Scenes.hpp>
#include <Terrains/LodBehaviour.hpp>
#include "Configs/ConfigManager.hpp"
#include "MainUpdater.hpp"
#include "MainRenderer.hpp"
#include "Scenes/FpsPlayer.hpp"
#include "Scenes/Scene1.hpp"

using namespace Demo;
using namespace fl;

//#if (FL_BUILD_RELEASE && FL_BUILD_WINDOWS)
//int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
//#else
int main(int argc, char **argv)
//#endif
{
	// Testing.
	{
		printf("Vector2 Size: %i\n", (int) sizeof(Vector2));
		printf("Vector3 Size: %i\n", (int) sizeof(Vector3));
		printf("Vector4 Size: %i\n", (int) sizeof(Vector4));
		printf("\n");
	}
	{
		printf("Vector2:\n");
		Vector2 a{3.0f, -7.2f};
		Vector2 b{-1.74f, 15.4f};
		printf("  %s + %s = %s\n", a.ToString().c_str(), b.ToString().c_str(), Vector2(a + b).ToString().c_str());
		printf("  %s - %s = %s\n", a.ToString().c_str(), b.ToString().c_str(), Vector2(a - b).ToString().c_str());
		printf("  %s * %s = %s\n", a.ToString().c_str(), b.ToString().c_str(), Vector2(a * b).ToString().c_str());
		printf("  %s / %s = %s\n", a.ToString().c_str(), b.ToString().c_str(), Vector2(a / b).ToString().c_str());
		printf("  %s ang %s = %f\n", a.ToString().c_str(), b.ToString().c_str(), a.Angle(b));
		printf("  %s dot %s = %f\n", a.ToString().c_str(), b.ToString().c_str(), a.Dot(b));
		printf("  %s sca %f = %s\n", a.ToString().c_str(), 10.0f, a.Scale(10.0f).ToString().c_str());
		printf("  %s rot %f = %s\n", a.ToString().c_str(), 90.0f, a.Rotate(90.0f).ToString().c_str());
		printf("  -%s = %s\n", a.ToString().c_str(), (-a).ToString().c_str());
		printf("  nor %s = %s\n", a.ToString().c_str(), a.Normalize().ToString().c_str());
		printf("  len %s = %f\n", a.ToString().c_str(), a.Length());
		printf("  %s dist %s = %f\n", a.ToString().c_str(), b.ToString().c_str(), a.Distance(b));
		printf("\n");
	}
	{
		printf("Vector3:\n");
		Vector3 a{12.9f, -2.0f, 6.7f};
		Vector3 b{-9.7f, 15.9f, -13.8f};
		printf("  %s + %s = %s\n", a.ToString().c_str(), b.ToString().c_str(), Vector2(a + b).ToString().c_str());
		printf("  %s - %s = %s\n", a.ToString().c_str(), b.ToString().c_str(), Vector2(a - b).ToString().c_str());
		printf("  %s * %s = %s\n", a.ToString().c_str(), b.ToString().c_str(), Vector2(a * b).ToString().c_str());
		printf("  %s / %s = %s\n", a.ToString().c_str(), b.ToString().c_str(), Vector2(a / b).ToString().c_str());
		printf("  %s ang %s = %f\n", a.ToString().c_str(), b.ToString().c_str(), a.Angle(b));
		printf("  %s dot %s = %f\n", a.ToString().c_str(), b.ToString().c_str(), a.Dot(b));
		printf("  %s sca %f = %s\n", a.ToString().c_str(), 10.0f, a.Scale(10.0f).ToString().c_str());
		//	printf("  %s rot %f = %s\n", a.ToString().c_str(), 90.0f, a.Rotate(90.0f).ToString().c_str());
		printf("  -%s = %s\n", a.ToString().c_str(), (-a).ToString().c_str());
		printf("  nor %s = %s\n", a.ToString().c_str(), a.Normalize().ToString().c_str());
		printf("  len %s = %f\n", a.ToString().c_str(), a.Length());
		printf("  %s dist %s = %f\n", a.ToString().c_str(), b.ToString().c_str(), a.Distance(b));
		printf("\n");
	}

////	return 0;

	// Creates the engine and updater objects.
	auto engine = new Engine();
	engine->SetUpdater(new MainUpdater());

	auto configManager = new ConfigManager();
	printf("Working Directory: %s\n", FileSystem::GetWorkingDirectory().c_str());

	// Registers modules.
//	Engine::Get()->RegisterModule<Example>("Example");
//	Engine::Get()->DeregisterModule("shadows");

	// Registers components.
	Scenes::Get()->RegisterComponent<FpsPlayer>("FpsPlayer");
	Scenes::Get()->RegisterComponent<LodBehaviour>("LodBehaviour");

	// Initializes modules.
	Display::Get()->SetTitle("Example Starting");
	Display::Get()->SetIcon("Resources/Logos/Tail.png");
	Mouse::Get()->SetCustomMouse("Resources/Guis/Cursor.png");
	Renderer::Get()->SetManager(new MainRenderer());
	Scenes::Get()->SetScene(new Scene1());

	// Runs the game loop.
	const int exitCode = engine->Run();

	// Deletes the engine.
	delete configManager;
	delete engine;

	// Pauses the console.
	std::cin.get();
	return exitCode;
}
