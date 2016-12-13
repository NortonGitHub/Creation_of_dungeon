#include "Game.h"
#include "MouseManager.h"

Game::Game()
    :stage_num("1-1"),
    mouse_status(MouseContent())
{
    class_name = "game";

    chara_manager = CharaManager(stage_num);
}


Game::~Game()
{
}

SceneBase * Game::Update()
{

    mouse_status = MouseManager::GetMouseStatus(mouse_status);
    
    chara_manager.Update(mouse_status);

    map_process_manager.Update(mouse_status);
    
    return this;
}

void Game::Draw()
{
    chara_manager.Draw();

    map_process_manager.Draw();
}
