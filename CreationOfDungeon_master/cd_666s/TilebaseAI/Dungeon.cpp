#include "Dungeon.h"
#include "../InputManager/KeyInput.h"
#include "../InputManager/InputManager.h"
#include "../Action/ActionManager.h"
#include "../Render/Sprite.h"
#include "../Resources/ResourceManager.h"
#include "../DebugDraw.h"
#include "../Utility/CSVReader.h"

#include "TileField.h"
#include "Player.h"
#include "Enemy.h"
#include "Monster.h"
#include "Obstacle.h"
#include "EnemysItem.h"
#include "Goal.h"
#include "TiledObjectMnager.h"
#include "StartPoint.h"

#include <assert.h>


Dungeon::Dungeon(std::string stageName)
    : _count(0)
    , _currentWaveInterval(120)
    , _permitivePassedNum(2)
    , _stageName(stageName)
    , _goal(nullptr)
    , _start(nullptr)
    , _face(RESOURCE_TABLE->GetFolderPath() + "graph/face.png")
    , _messageUI(RESOURCE_TABLE->GetFolderPath() + "graph/ui/message_window.png")
    , _mainsFrame(RESOURCE_TABLE->GetFolderPath() + "graph/ui/main_window.png")
    , _background(RESOURCE_TABLE->GetFolderPath() + "graph/ui/brick01.png", Vector2D(0, 280))
{
    _face.SetScale(Vector2D(2, 2));

    _messageUI.GetTexturePtr()->SetPriority(100);
    _mainsFrame.GetTexturePtr()->SetPriority(100);
    _background.GetTexturePtr()->SetPriority(-100);

    _mainsFrame.SetPosition(Vector2D(10, 220));
    _messageUI.SetPosition(Vector2D(20, 860));
}


Dungeon::~Dungeon()
{
//    Clear();
//    OBJECT_MGR->Refresh();
}


void Dungeon::Init()
{
    _count = 0;
    _controller.Init();
    _infoDrawer.Init();
    
    //�X�e�[�W����
    std::vector<std::string> dataArray;
    CSVReader reader;
    
    //�E�F�[�u�̏���ǂݍ���
    std::string fileName = RESOURCE_TABLE->GetFolderPath() + "data/wave";
    fileName += (_stageName + ".csv");
    std::vector<std::string> waveInfoArray;
    reader.Read(fileName, waveInfoArray, 1);
    
    _currentWaveInterval = std::stoi(waveInfoArray[0]);
    _permitivePassedNum = std::stoi(waveInfoArray[1]);
    
    //�Q�[�����Ԋ��Z�ŕb�P�ʂɕϊ�
    _currentWaveInterval *= 60;
    
    //�t�B�[���h�̃T�C�Y��ǂݍ���
    fileName = RESOURCE_TABLE->GetFolderPath() + "data/map";
    fileName += (_stageName + ".csv");
    auto fieldSizeH = reader.GetLineSize(fileName, 0);
    auto fieldSizeV = reader.GetLineNum(fileName);
    
    //�t�B�[���h�̃f�[�^��ǂݍ���
    reader.Read(fileName, dataArray);
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
    
    //�L�������������[�h
    fileName = RESOURCE_TABLE->GetFolderPath() + "data/enemys";
    fileName += (_stageName + ".csv");
    Enemy::LoadEnemys(_objs, _start, _goal, _enemys, fileName);

    fileName = RESOURCE_TABLE->GetFolderPath() + "data/monsters";
    fileName += (_stageName + ".csv");
    Monster::LoadMonsters(_objs, _monsters, fileName);
    
    _monsters.Update();
    _enemys.Update();
    OBJECT_MGR->Refresh();
    
    for (auto obj : OBJECT_MGR->_objects._objects)
    {
        if (obj != nullptr)
            obj->Init();
    }
}


void Dungeon::GenerateObject(std::string typeName, int countX, int countY)
{
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
    FIELD->Clear();
    OBJECT_MGR->_objects.Clear();
    
    _start = nullptr;
    _goal = nullptr;
}


bool Dungeon::HasClear()
{
    //WAVE��ς���������N���A
    if (_currentWaveInterval < _count)
        return true;
    
    //WAVE���̓G��S�ł�������N���A
    if (_enemys.HasWipeouted())
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
    //���ԂɂȂ����珉����
    if (_currentWaveInterval < _count)
    {
        Clear();
        Init();
        return;
    }
    else
    {
        _count++;
    }
    
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
    if (_currentWaveInterval < _count)
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

    //�X�e�[�W���\��
    Debug::DrawString(Vector2D(625, 0), _stageName);
    
    //���b�Z�[�W�E�B���h�E���\��
    _face.SetPosition(Vector2D(40, 540));
    Debug::DrawString(Vector2D(200, 580), "�z�͗E�҂̒��ł��Ŏ�...!");

    //�X�e�[�W���\��
    Debug::DrawRectWithSize(Vector2D(970, 10), Vector2D(250, 30), Color4(0.5, 0.65, 0.85, 1.0), true);
    Debug::DrawRectWithSize(Vector2D(970, 10), Vector2D(250, 30), ColorPalette::WHITE4, false);
    Debug::DrawString(Vector2D(980, 20), "���A�_���W���� ����" + _stageName);

    //�������\��
    Debug::DrawRectWithSize(Vector2D(920, 60), Vector2D(340, 60), Color4(0.5, 0.65, 0.85, 1.0), true);
    Debug::DrawRectWithSize(Vector2D(920, 60), Vector2D(340, 60), ColorPalette::WHITE4, false);
    Debug::DrawString(Vector2D(950, 80), "������ : $100,000,000");

    //���̑����\��
    Vector2D subWindowPos = Vector2D(724, 248);
    Debug::DrawRectWithSize(subWindowPos, Vector2D(150, 240), ColorPalette::WHITE4, true);
    Debug::DrawRectWithSize(subWindowPos, Vector2D(150, 240), ColorPalette::BLACK4, false);

    //�c�莞�ԃf�o�b�O�\��
    std::string timerStr = "Timer:";
    timerStr += std::to_string((_currentWaveInterval - _count) / 60);
    timerStr += "/";
    timerStr += std::to_string(_currentWaveInterval / 60);
    Debug::DrawString(subWindowPos + Vector2D(20, 30), timerStr);

    //�m���}�\��
    std::string passed = "passed :";
    passed += std::to_string(_goal->GetPassedNum());
    passed += "/";
    passed += std::to_string(_permitivePassedNum);
    Debug::DrawString(subWindowPos + Vector2D(20, 50), passed);
}