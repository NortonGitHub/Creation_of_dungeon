#include "Dungeon.h"
#include "../InputManager/InputManager.h"
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

#include "MineBomb.h"

#include <assert.h>


Dungeon::Dungeon(std::string stageName)
    : _permitivePassedNum(2)
    , _stageName(stageName)
    , _goal(nullptr)
    , _start(nullptr)
    , _face("resourse/graph/devilGirlUsual.png", Vector2D(40, 545))
    , _messageUI("resourse/graph/ui/message_window.png", Vector2D(20, 520))
    , _mainsFrame("resourse/graph/ui/main_window.png", Vector2D(20, 20))
    , _background("resourse/graph/background/background.png", Vector2D(0, 7600))
    , _windowBackground("resourse/graph/ui/main_window_background1.png", Vector2D(28, 28))
    , _waveInfomartionBoard("resourse/graph/ui/enemyinformation.png", Vector2D(754, 248))
    , _infoDrawer(_dictionary)
    , _intruderInformation(_dictionary)
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
    
    //ステージ生成
    std::vector<std::string> dataArray;
    CSVReader reader;
    
    //ウェーブの情報を読み込む
    std::string fileName = "csv/StageData/wave";
    fileName += (_stageName + ".csv");
    std::vector<std::string> waveInfoArray;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, waveInfoArray, 1);

    auto waveInterval = std::stoi(waveInfoArray[0]);
    _timer.InitWithSetup(waveInterval);
    _permitivePassedNum = std::stoi(waveInfoArray[1]);
    
    //フィールドのサイズを読み込む
    fileName = "csv/StageData/map";
    fileName += (_stageName + ".csv");
    auto fieldSizeH = reader.GetLineSize(fileName, 0);
    auto fieldSizeV = reader.GetLineNum(fileName);
    
    //フィールドのデータを読み込む
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, dataArray);
    int countX = 0;
    int countY = 0;
    FIELD->Init(fieldSizeH, fieldSizeV);

    //オブジェクトを読み込む
    auto& _objs = OBJECT_MGR->_objects;
    _objs.push_back(std::make_shared<MineBomb>(TiledVector(4, 3)));
    _objs.push_back(std::make_shared<MineBomb>(TiledVector(8, 1)));

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
    
    //侵入位置を設定
    _intruderInformation.InitWithSetup(_start);

    //キャラたちをロード
    fileName = "csv/StageData/enemys";
    fileName += (_stageName + ".csv");
    Enemy::LoadEnemys(_objs, *_start, *_goal, _enemys, fileName);

    fileName = "csv/StageData/monsters";
    fileName += (_stageName + ".csv");
    Monster::LoadMonsters(_objs, _monsters, fileName);
    
    FIELD->Setup();

    _monsters.Update();
    _enemys.Update();
    OBJECT_MGR->Refresh();
    
    for (auto obj : _objs)
    {
        if (obj.get() != nullptr)
            obj->Init();
    }
}


void Dungeon::GenerateObject(std::string typeName, int countX, int countY)
{
    FIELD->SetRawNumber(TiledVector(countX, countY), stoi(typeName));

    auto& _objs = OBJECT_MGR->_objects;
    switch(stoi(typeName))
    {
        case 0:
            return;
            
        case 1:
            _objs.push_back(std::make_shared<Obstacle>(TiledVector(countX, countY)));
            return;
            
        case 2:
            //_objs.push_back(std::make_shared<EnemysItem>(param, TiledVector(countX, countY)));
            EnemysItem::LoadItem(countX, countY, _objs, "");
            return;

        case 6:
            _objs.push_back(std::make_shared<River>(TiledVector(countX, countY)));
            return;

        case 100:
            if (_goal == nullptr)
            {
                _goal = std::make_shared<Goal>(TiledVector(countX, countY), _monsters);
                _objs.push_back(_goal);
            }
            return;
            
        case 200:
            if (_start == nullptr)
            {
                _start = std::make_shared<StartPoint>(TiledVector(countX, countY));
                _objs.push_back(_start);
            }
            return;
    }
}


void Dungeon::Clear()
{
    _infoDrawer.Clear();

    OBJECT_MGR->Clear();
    _start = nullptr;
    _goal = nullptr;
    FIELD->Clear();

    RESOURCE_TABLE->Refresh();
}


bool Dungeon::HasClear()
{
    //WAVEを耐えきったらクリア
    if (_timer.HasTimeUp())
        return true;
    
    //WAVE中の敵を全滅させたらクリア
    if (Enemy::HasWipeOuted())
        return true;
    
    //最後の敵を倒したらクリア
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

    //情報網更新
    _monsters.Update();
    _enemys.Update();
    
    //捜査情報更新
    _controller.Update();
    
    for (auto obj : OBJECT_MGR->_objects)
    {
        if (obj != nullptr)
            obj->Update();
    }
}


void Dungeon::Draw()
{
    //時間になったら初期化
    if (_timer.HasTimeUp())
        return;

    FIELD->Draw();
    for (auto obj : OBJECT_MGR->_objects)
    {
        if (obj != nullptr)
            obj->Draw();
    }
    
    _infoDrawer.Update();
    _infoDrawer.Draw();
    _controller.Draw();
    
    OBJECT_MGR->Refresh();

    //メッセージウィンドウ仮表示
    Debug::DrawString(Vector2D(300, 600), "クリエイションオブダンジョン体験版にようこそ");

    //ステージ名表示
    Debug::DrawRectWithSize(Vector2D(970, 40), Vector2D(250, 60), Color4(0.5, 0.65, 0.85, 1.0), true);
    Debug::DrawRectWithSize(Vector2D(970, 40), Vector2D(250, 60), ColorPalette::WHITE4, false);
    Debug::DrawString(Vector2D(1010, 64), "洞窟ダンジョン その" + _stageName);

    //残り時間表示
    _timer.Draw();

    //ノルマ表示
    std::string passed = "MISS:";
    Debug::DrawString(_waveInfomartionBoard.GetPosition() + Vector2D(20, 85), passed);
    passed = std::to_string(_goal->GetPassedNum());
    passed += "/";
    passed += std::to_string(_permitivePassedNum);
    Debug::DrawString(_waveInfomartionBoard.GetPosition() + Vector2D(50, 105), passed);

    //侵入者情報表示
    _intruderInformation.Draw();
}
