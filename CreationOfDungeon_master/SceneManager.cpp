#include "SceneManager.h"
#include "Title.h"


SceneManager::SceneManager() : now_scene(new Title()), test(Graph("resourse/test_666/omote"))
{
    auto class_name = now_scene->GetClassNameData();
    now_scene->Init(class_name);

    test.SetPosition(Vector2D(0, 64));
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
    }


    //test.Draw();
    now_scene->MainDraw();

    return true;
}
