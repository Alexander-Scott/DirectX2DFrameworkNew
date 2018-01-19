#pragma once

#include "FrameTimer.h"
#include "MainWindow.h"

#include "SceneBuilder.h"
#include "SceneManagement.h"
#include "ScenePersistentValues.h"

using namespace std;

class Engine
{
public:
	Engine(class MainWindow& wnd, int width, int height, std::string resourcesPath);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	shared_ptr<Scene> GetScene() { return mScene; }

	void Update();

	~Engine();

	MainWindow& wnd;

private:
	void DrawScene();
	void UpdateScene();

	void LoadScene(std::string sceneName);

	FrameTimer					mFrameTimer;
	shared_ptr<Scene>			mScene;
};