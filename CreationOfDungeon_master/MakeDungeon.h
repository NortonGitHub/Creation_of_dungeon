#pragma once
#include "cd_666s\InputManager\MouseInput.h"
#include "cd_666s\TilebaseAI\MapTile.h"
#include "cd_666s/TilebaseAI/ColleagueNotifyer.h"

#include "cd_666s/TilebaseAI/Goal.h"
#include "cd_666s/TilebaseAI/StartPoint.h"

#include "UIManager.h"

class MakeDungeon
{
public:
    MakeDungeon();
    MakeDungeon(std::string stage_num);
    ~MakeDungeon();

    void Update();

    void Draw();

    void Init(std::string file_name);

    void PickupObject();

    void LoadTileSize(std::string stageName, std::vector<std::string>& rawData);

    std::shared_ptr<Goal> getGoal();
    std::shared_ptr<StartPoint> getStart();

    TiledObject* GenerateAddObject(std::string typeName, int countX, int countY, Vector2D mousePos);

    std::vector<TiledObject*> GenerateMonster(std::string fileName, TiledVector startPos, std::string* GenerateText);

private:

    std::string _stage_num;

    
    void GenerateObject(std::string typeName, int countX, int countY);


    //�J�n�_�ƏI���n�_�̓O���[�o���ȃ��x���ŃC���X�^���X�������Ă���
    std::shared_ptr<Goal> _goal;
    std::shared_ptr<StartPoint> _start;

    //�����Ԃ̏�񋤗L��

    ColleagueNotifyer _monsters,_enemys;

    //���ݑI�΂�Ă���I�u�W�F�N�g
    std::string _selectingObj;

    //���b�Z�[�W�E�B���h�E
    MessageReciever _messageReciever;

    Sprite _mainsFrame, _background, _windowBackground;
};

