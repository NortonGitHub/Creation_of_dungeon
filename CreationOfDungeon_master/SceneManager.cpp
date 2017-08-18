#include "SceneManager.h"
#include "Title.h"
#include "EditMap.h"

SceneManager::SceneManager() : now_scene(new EditMap("1"))
{
    auto class_name = now_scene->GetClassNameData();
    now_scene->Init(class_name);
}


SceneManager::~SceneManager()
{
}

bool SceneManager::SceneManagement()
{
    SceneBase* next_scene = now_scene->MainUpdate();
    
    if(next_scene == nullptr){
        return false;
    }
    else if (next_scene != now_scene) {
        delete(now_scene);
        now_scene = next_scene;
        now_scene->Init(now_scene->GetClassNameData());
    }


    //test.Draw();
    now_scene->MainDraw();

    return true;
}
