#include "Dungeon.h"
#include "../InputManager/InputManager.h"
#include "../Action/ActionManager.h"
#include "../Render/RenderManager.h"
#include "../Resources/AllResourceManager.h"
#include "../DebugDraw.h"
#include "../Utility/CSVReader.h"

#include "TileField.h"
#include "Enemy.h"
#include "Monster.h"
#include "Obstacle.h"
#include "River.h"
#include "EnemysItem.h"
#include "Goal.h"
#include "TiledObjectMnager.h"
#include "StartPoint.h"

#include <assert.h>


Dungeon::Dungeon(std::string stageName)
    : _permitivePassedNum(2)
    , _stageName(stageName)
    , _goal(nullptr)
    , _start(nullptr)
    , _face("resourse/graph/devilGirlUsual.png", Vector2D(40, 545))
    , _messageUI("resourse/graph/ui/message_window.png", Vector2D(20, 520))
    , _mainsFrame("resourse/graph/ui/main_window.png", Vector2D(20, 20))
    , _background("resourse/graph/background/background.png", Vector2D(0, 0))
    , _windowBackground("resourse/graph/ui/main_window_background1.png", Vector2D(28, 28))
    , _waveInfomartionBoard("resourse/graph/ui/enemyinformation.png", Vector2D(754, 248))
{
    _face.SetScale(Vector2D(2, 2));

    _messageUI.SetPriority(Sprite::Priority::UI);
    _mainsFrame.SetPriority(Sprite::Priority::UI);
    _background.SetPriority(Sprite::Priority::BACKGROUND);
    _windowBackground.SetPriority(static_cast<int>(Sprite::Priority::BACKGROUND) + 1);
    _waveInfomartionBoard.SetPriority(Sprite::Priority::UI);
}


Dungeon::~Dungeon()
{
    Clear();
    OBJECT_MGR->Refresh();
}


void Dungeon::Init()
{
    _controller.Init();
    _infoDrawer.Init();
    
    //�X�e�[�W����
    std::vector<std::string> dataArray;
    CSVReader reader;
    
    //�E�F�[�u�̏���ǂݍ���
    std::string fileName = "csv/StageData/wave";
    fileName += (_stageName + ".csv");
    std::vector<std::string> waveInfoArray;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, waveInfoArray, 1);

    auto waveInterval = std::stoi(waveInfoArray[0]);
    _timer.InitWithSetup(waveInterval);
    _permitivePassedNum = std::stoi(waveInfoArray[1]);
    
    //�t�B�[���h�̃T�C�Y��ǂݍ���
    fileName = "csv/StageData/map";
    fileName += (_stageName + ".csv");
    auto fieldSizeH = reader.GetLineSize(fileName, 0);
    auto fieldSizeV = reader.GetLineNum(fileName);
    
    //�t�B�[���h�̃f�[�^��ǂݍ���
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, dataArray);
    int countX = 0;
    int countY = 0;
    FIELD->Init(fieldSizeH, fieldSizeV);
    
    //�I�u�W�F�N�g��ǂݍ���
    std::vector<TiledObject*>& _objs = OBJECT_MGR->_objects._objects;
    for (auto data : dataArray)
    {
        //�󂯎�����f�[�^��ϊ��\�����Ƃɕϊ�
        GenerateObject(data, countX, countY);
        
        //���̃}�b�v�ԍ��܂�
        countX++;
        if (countX == fieldSizeH)
        {
            countX = 0;
            countY++;
            
            if (countY == fieldSizeV)
                break;
        }
    }
    
    assert( (_goal != nullptr) && (_start != nullptr) && "Cannot Read Start and Goal");
    
    //�N���ʒu��ݒ�
    _intruderInformation.InitWithSetup(_start);

    //�L�������������[�h
    fileName = "csv/StageData/enemys";
    fileName += (_stageName + ".csv");
    Enemy::LoadEnemys(_objs, _start, _goal, _enemys, fileName);

    fileName = "csv/StageData/monsters";
    fileName += (_stageName + ".csv");
    Monster::LoadMonsters(_objs, _monsters, fileName);
    
    FIELD->Setup();

    _monsters.Update();
    _enemys.Update();
    OBJECT_MGR->Refresh();
    
    for (auto obj : _objs)
    {
        if (obj != nullptr)
            obj->Init();
    }
}


void Dungeon::GenerateObject(std::string typeName, int countX, int countY)
{
    FIELD->SetRawNumber(TiledVector(countX, countY), stoi(typeName));

    std::vector<TiledObject*>& _objs = OBJECT_MGR->_objects._objects;
    switch(stoi(typeName))
    {
        case 0:
            return;
            
        case 1:
            _objs.push_back(new Obstacle(TiledVector(countX, countY)));
            return;
            
        case 2:
            _objs.push_back(new EnemysItem(TiledVector(countX, countY)));
            return;

        case 6:
            _objs.push_back(new River(TiledVector(countX, countY)));
            return;

        case 100:
            if (_goal == nullptr)
            {
                _goal = new Goal(TiledVector(countX, countY), _monsters);
                _objs.push_back(_goal);
            }
            return;
            
        case 200:
            if (_start == nullptr)
            {
                _start = new StartPoint(TiledVector(countX, countY));
                _objs.push_back(_start);
            }
            return;
    }
}


void Dungeon::Clear()
{
    _infoDrawer.Clear();

    FIELD->Clear();
    OBJECT_MGR->_objects.Clear();
    
    _start = nullptr;
    _goal = nullptr;

    RESOURCE_TABLE->Refresh();
}


bool Dungeon::HasClear()
{
    //WAVE��ς���������N���A
    if (_timer.HasTimeUp())
        return true;
    
    //WAVE���̓G��S�ł�������N���A
    if (Enemy::HasWipeOuted())
        return true;
    
    //�Ō�̓G��|������N���A
    if (_start->GetTimeUnitlNext() == StartPoint::NobodyIntruder()
        && _enemys.GetColleagues() == 0
        && !HasGameOver())
        return true;

    return false;
}


bool Dungeon::HasGameOver()
{
    auto passedNum = _goal->GetPassedNum();
    if (_permitivePassedNum < passedNum)
        return true;
        
    return false;
}


void Dungeon::Update()
{
    _timer.Update();

    //���ԍX�V
    _monsters.Update();
    _enemys.Update();
    
    //�{�����X�V
    _controller.Update();
    
    for (auto obj : OBJECT_MGR->_objects._objects)
    {
        if (obj != nullptr)
            obj->Update();
    }
}


void Dungeon::Draw()
{
    //���ԂɂȂ����珉����
    if (_timer.HasTimeUp())
        return;

    FIELD->Draw();
    for (auto obj : OBJECT_MGR->_objects._objects)
    {
        if (obj != nullptr)
            obj->Draw();
    }
    
    _infoDrawer.Update();
    _infoDrawer.Draw();
    _controller.Draw();
    
    OBJECT_MGR->Refresh();

    //���b�Z�[�W�E�B���h�E���\��
    Debug::DrawString(Vector2D(300, 600), "�N���G�C�V�����I�u�_���W�����̌��łɂ悤����");

    //�X�e�[�W���\��
    Debug::DrawRectWithSize(Vector2D(970, 40), Vector2D(250, 60), Color4(0.5, 0.65, 0.85, 1.0), true);
    Debug::DrawRectWithSize(Vector2D(970, 40), Vector2D(250, 60), ColorPalette::WHITE4, false);
    Debug::DrawString(Vector2D(1010, 64), "���A�_���W���� ����" + _stageName);

    //�c�莞�ԕ\��
    _timer.Draw();

    //�m���}�\��
    std::string passed = "MISS:";
    Debug::DrawString(_waveInfomartionBoard.GetPosition() + Vector2D(20, 85), passed);
    passed = std::to_string(_goal->GetPassedNum());
    passed += "/";
    passed += std::to_string(_permitivePassedNum);
    Debug::DrawString(_waveInfomartionBoard.GetPosition() + Vector2D(50, 105), passed);

    //�N���ҏ��\��
    _intruderInformation.Draw();
}
