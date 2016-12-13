#include "SceneManager.h"
#include "Title.h"


SceneManager::SceneManager() : now_scene(new Title())
{
    auto class_name = now_scene->GetClassName();
    now_scene->Init(class_name);
}


SceneManager::~SceneManager()
{
}

void SceneManager::SceneManagement()
{
    SceneBase* next_scene = now_scene->MainUpdate();
    
    if (next_scene != now_scene) {
        delete(now_scene);
        now_scene = next_scene;
    }

    now_scene->Draw();


}
