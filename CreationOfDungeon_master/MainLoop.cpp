#include "MainLoop.h"
#include "SceneManager.h"

MainLoop::MainLoop()
{
}


MainLoop::~MainLoop()
{
}

void MainLoop::GameLoop()
{
	SceneManager scene_manager;
	while (1) {
		scene_manager.SceneManagement();
	}
}
