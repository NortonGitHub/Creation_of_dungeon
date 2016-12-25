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
{
}


Dungeon::~Dungeon()
{
    Clear();
    OBJECT_MGR->Refresh();
}


void Dungeon::Init()
{
    _count = 0;
    _controller.Init();
    _infoDrawer.Init();
    
    //ステージ生成
    std::vector<std::string> dataArray;
    CSVReader reader;
    
    //ウェーブの情報を読み込む
    std::string fileName = RESOURCE_TABLE->GetFolderPath() + "data/wave";
    fileName += (_stageName + ".csv");
    std::vector<std::string> waveInfoArray;
    reader.Read(fileName, waveInfoArray, 1);
    
    _currentWaveInterval = std::stoi(waveInfoArray[0]);
    _permitivePassedNum = std::stoi(waveInfoArray[1]);
    
    //ゲーム時間換算で秒単位に変換
    _currentWaveInterval *= 60;
    
    //フィールドのサイズを読み込む
    fileName = RESOURCE_TABLE->GetFolderPath() + "data/map";
    fileName += (_stageName + ".csv");
    auto fieldSizeH = reader.GetLineSize(fileName, 0);
    auto fieldSizeV = reader.GetLineNum(fileName);
    
    //フィールドのデータを読み込む
    reader.Read(fileName, dataArray);
    int countX = 0;
    int countY = 0;
    FIELD->Init(fieldSizeH, fieldSizeV);
    
    //オブジェクトを読み込む
    std::vector<TiledObject*>& _objs = OBJECT_MGR->_objects._objects;
    for (auto data : dataArray)
    {
        //受け取ったデータを変換表をもとに変換
        GenerateObject(data, countX, countY);
        
        //次のマップ番号まで
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
    
    //キャラたちをロード
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
    OBJECT_MGR->_objects.Clear();
    
    _start = nullptr;
    _goal = nullptr;
}


bool Dungeon::HasClear()
{
    //WAVEを耐えきったらクリア
    if (_currentWaveInterval < _count)
        return true;
    
    //WAVE中の敵を全滅させたらクリア
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
    //時間になったら初期化
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
    
    //情報網更新
    _monsters.Update();
    _enemys.Update();
    
    //捜査情報更新
    _controller.Update();
    
    for (auto obj : OBJECT_MGR->_objects._objects)
    {
        if (obj != nullptr)
            obj->Update();
    }
    
    Draw();
}


void Dungeon::Draw()
{
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

    //ステージ名表示
    Debug::DrawString(Vector2D(625, 0), _stageName);
    
    //残り時間デバッグ表示
    std::string timerStr = "Timer:";
    timerStr += std::to_string( (_currentWaveInterval - _count) / 60);
    timerStr += " / ";
    timerStr += std::to_string(_currentWaveInterval / 60);
    Debug::DrawString(Vector2D(625, 32), timerStr);
    
    //ノルマ表示
    std::string passed = "passed :";
    passed += std::to_string(_goal->GetPassedNum());
    passed += " / ";
    passed += std::to_string(_permitivePassedNum);
    Debug::DrawString(Vector2D(625, 64), passed);
}
