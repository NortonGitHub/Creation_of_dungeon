#pragma once
#include "SceneBase.h"
#include "MapProcessManager.h"
#include "CharaManager.h"
#include "cd_666s/TilebaseAI/Dungeon.h"

class Game :
    public SceneBase
{
public:
    Game();
    ~Game();

    SceneBase* Update(UIManager _ui);
    void Draw();

    std::string GetClassNameData() const {
        return class_name;
    };

private:
    std::string class_name;

    std::string stage_num;

    CharaManager chara_manager;

    MapProcessManager map_process_manager;

    MouseContent mouse_status;

    std::vector<std::string> _functions;

    Graph test;



    void Init();
    void Clear();

    //���Ƃ�pointer�ɂ����Ƃ��ςނ悤�ɂ���
    Dungeon* _dungeon;
    int _stageNumber;
};

