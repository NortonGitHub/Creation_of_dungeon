#include "Dungeon.h"
#include "../InputManager/InputManager.h"
#include "../Render/RenderManager.h"
#include "../Resources/AllResourceManager.h"
#include "../DebugDraw.h"
#include "../Utility/CSVReader.h"

#include "TileField.h"
#include "Enemy.h"
#include "Monster.h"
#include "../../IntrudedEnemy.h"
#include "Obstacle.h"
#include "WeakObstacle.h"
#include "River.h"
#include "EnemysItem.h"
#include "Goal.h"
#include "TiledObjectMnager.h"
#include "StartPoint.h"
#include "Trap.h"

#include <assert.h>
#include <iostream>


Dungeon::Dungeon(std::string stageName)
	: _permitivePassedNum(2)
	, _stageName(stageName)
	, _goal(nullptr)
	, _start(nullptr)
	, _mainsFrame("resource/graph/ui/main_window.png", Vector2D(20, 20))
	, _background("resource/graph/background/background.png", Vector2D(0, 0))
	, _windowBackground("resource/graph/ui/main_window_background1.png", Vector2D(28, 28))
	, _waveInfomartionTimer("resource/graph/ui/enemytimer.png", Vector2D(754, 248))
	, _hartFrame("resource/graph/ui/LifeFrame.png", Vector2D(734, 248 - 200))
	, _hart("resource/graph/ui/HartFull.png", Vector2D(734 + 7, 78 + 28))
	, _infoDrawer(_dictionary)
	, _intruderInformation(_dictionary)
	, _intrudeLastCharacter(false)
	, _defeatedNum(0)
{

	auto b_pos = _stageName.rfind('b');

	if (b_pos != std::string::npos) {
		_stageNum = _stageName.substr(0, b_pos);
		_counter.Init();
	}
	else {
		_stageNum = _stageName;
	}

	//_hart.reserve(5);

	/*
	for (int i = 0; i < _permitivePassedNum + 1; i++) {
		_hart.push_back({ "resource/graph/background/ui/HartFull.png",Vector2D(754 + 30 + i * 20,248 + 180) });
		_hart.back().SetPriority(Sprite::Priority::UI);
		_hart.back().SetDisplayMode(true);
		_hartN.push_back({ "resource/graph/background/ui/HartNull.png",Vector2D(754 + 30 + i * 20,248 + 180) });
		_hartN.back().SetPriority(Sprite::Priority::UI);
		_hartN.back().SetDisplayMode(false);
	}
	*/

	
	_hart.SetPriority(Sprite::Priority::UI);
	_hart.SetDisplayMode(false);
	_hart.SetScale(Vector2D(5.0, 5.0));

	_hartFrame.SetPriority(Sprite::Priority::UI);
	_hartFrame.SetDisplayMode(true);


	_background.Load("resource/graph/background/background_cave.png");
	_background.SetPosition(Vector2D(0, 0));

	_windowBackground.Load("resource/graph/ui/main_window_background_cave.png");
	_windowBackground.SetPosition(Vector2D(28, 28));

	_mainsFrame.SetPriority(Sprite::Priority::UI);
	_background.SetPriority(Sprite::Priority::BACKGROUND);
	_windowBackground.SetPriority(static_cast<int>(Sprite::Priority::BACKGROUND) + 1);
	_waveInfomartionTimer.SetPriority(Sprite::Priority::UI);
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

	_messageReciever.Init();
	LoadMessage(_stageName);

	//ボスステージかどうかを判別
	_is_boss = _stageName.rfind('b') != std::string::npos;

	//ステージ生成
	std::vector<std::string> dataArray;
	CSVReader reader;

	//ウェーブの情報を読み込む
	std::string fileName = "csv/StageData/wave";
	fileName += (_stageName + ".csv");
	std::vector<std::string> waveInfoArray;
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, waveInfoArray, 1);
	auto waveInterval = std::stoi(waveInfoArray[0]);

	_counter.InitWithSetup(waveInterval);
	_timer.InitWithSetup(waveInterval);

	_permitivePassedNum = std::stoi(waveInfoArray[1]);

	//タイルの大きさを読み込む
	fileName = "csv/StageData/tilesize.csv";
	std::vector<std::string> tileInfoArray;
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, tileInfoArray);
	LoadTileSize(_stageName, tileInfoArray);

	//フィールドのサイズを読み込む
	//fileName = "csv/StageData/map";
	//fileName += (_stageName + ".csv");
	fileName = "csv/StageData/EditMapData.csv";
	auto fieldSizeH = reader.GetLineSize(fileName, 0);
	auto fieldSizeV = reader.GetLineNum(fileName);

	//フィールドのデータを読み込む
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, dataArray);
	int countX = 0;
	int countY = 0;
	FIELD->Init(fieldSizeH, fieldSizeV);

	//ダンジョンの地形の設定
	std::string ft;

	std::vector<std::string> FieldTypeArray;
	fileName = "csv/StageData/DungeonType.csv";
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, FieldTypeArray, 2);

	int FieldTypeNum = stoi(FieldTypeArray[stoi(_stageName) * 2 - 1]);

	switch (FieldTypeNum) {
	case 0:
		ft = "#CAV";
		_windowBackground.Load("resource/graph/ui/main_window_background_cave.png");
		_background.Load("resource/graph/background/background_cave.png");
		break;
	case 1:
		ft = "#FST";
		_windowBackground.Load("resource/graph/ui/main_window_background_forest.png");
		_background.Load("resource/graph/background/background_forest.jpg");
		break;
	case 2:
		ft = "#STN";
		_windowBackground.Load("resource/graph/ui/main_window_background_stone.png");
		_background.Load("resource/graph/background/background_stone.jpg");
		break;
	default:
		ft = "#CAV";
		_windowBackground.Load("resource/graph/ui/main_window_background_cave.png");
		_background.Load("resource/graph/background/background_cave.jpg");
		break;
	}
	_windowBackground.SetPosition(Vector2D(28, 28));
	_background.SetPosition(Vector2D(0, 0));

	//ボス情報の読み込み
	if (_is_boss) {
		//		_bossBattle.Init(_stageNum);
	}
	//ここまで

	//オブジェクトを読み込む
	auto& _objs = OBJECT_MGR->_objects;
	for (auto data : dataArray)
	{
		//受け取ったデータを変換表をもとに変換
		GenerateObject(data, countX, countY);

		FIELD->SetFieldType(TiledVector(countX, countY), ft);

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

	assert((_goal != nullptr) && (_start != nullptr) && "Cannot Read Start and Goal");

	//侵入位置を設定
	_intruderInformation.InitWithSetup(_start);

	//キャラたちをロード
	fileName = "csv/StageData/enemys";
	fileName += (_stageName + ".csv");
	Enemy::LoadEnemys(_objs, *_start, *_goal, _enemys, fileName);

	//fileName = "csv/StageData/monsters";
	//fileName += (_stageName + ".csv");
	fileName = "csv/StageData/EditMap_MonsterData.csv";
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
	FIELD->SetFieldType(TiledVector(countX, countY), typeName);

	auto& _objs = OBJECT_MGR->_objects;

	if (typeName.find("9#") != std::string::npos)
	{
		Trap::CreateTrap(typeName, countX, countY, _objs);
		return;
	}

	if (typeName.find("2&") != std::string::npos)
	{
		LoadItem(typeName, countX, countY, _objs);
		return;
	}

	if (typeName.find("200") != std::string::npos)
	{
		if (_start == nullptr)
		{
			_start = std::make_shared<StartPoint>(TiledVector(countX, countY), _messageReciever);
			_objs.push_back(_start);
		}
		return;
	}

	if (typeName.find("100") != std::string::npos)
	{
		if (_goal == nullptr)
		{
			_goal = std::make_shared<Goal>(TiledVector(countX, countY), _monsters, _messageReciever, _permitivePassedNum);
			_objs.push_back(_goal);
		}
		return;
	}

	if (typeName.find("6") != std::string::npos)
	{
		_objs.push_back(std::make_shared<River>(TiledVector(countX, countY)));
		return;
	}

	if (typeName.find("1") != std::string::npos)
	{
		_objs.push_back(std::make_shared<Obstacle>(TiledVector(countX, countY)));
		return;
	}

	if (typeName == "0")
		return;

	if (typeName.find("300") != std::string::npos)
	{
		_objs.push_back(std::make_shared<WeakObstacle>(TiledVector(countX, countY)));
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
	//WAVEを耐えきったらクリア(通常ステージのみ)
	if (_timer.HasTimeUp() && !_is_boss)
		return true;

	//WAVE中の敵を全滅させたらクリア
	if (Enemy::HasWipeOuted())
		return true;

	//最後の敵を倒したらクリア
	if (_start->GetTimeUnitlNext() == StartPoint::NobodyIntruder()
		&& _enemys.GetColleagues() == 0
		&& !HasGameOver())
		return true;

	if (_is_boss && _counter.GetAllEnemy() <= _counter.GetCount()) {
		return true;
	}

	/*
	auto b = _start->GetTimeUnitlNext();
	auto a = _enemys.GetColleagues();
	*/

	return false;
}


bool Dungeon::HasGameOver()
{
	//ボスステージのゲームオーバー条件 : ボスの体力
	if (_is_boss) {
		//MEMO:暫定的に敵をさせていい上限をpermitedNumとしている。
		auto passedNum = _goal->GetPassedNum();
		if (_permitivePassedNum < passedNum)
			return true;

		//return _bossBattle.WasBossKilled();
	}
	//通常ステージのゲームオーバー条件 : 通過させた敵の数
	else {
		auto passedNum = _goal->GetPassedNum();
		if (_permitivePassedNum < passedNum)
			return true;
	}
	return false;
}


void Dungeon::Update()
{
	//メッセージ更新
	UpdateSecretary();

	if (_is_boss) {
		_counter.Update(_defeatedNum);
	}
	else {
		_timer.Update();
	}

	//情報網更新
	_monsters.Update();
	_enemys.Update();

	//捜査情報更新
	_controller.Update();

	for (auto& obj : OBJECT_MGR->_objects)
	{
		if (obj != nullptr) {
			obj->Update();

			if (!_is_boss)
				continue;

			if (obj->GetType() == TiledObject::Type::ENEMY) {
				_defeatedNum = obj->GetDefeatedNum();
			}

			//敵がゴールに到着したらボスとの戦闘開始
			if (obj->HasArrived())
			{
				//	_bossBattle.SetBattleObject(OBJECT_MGR->_objects, obj);
			}
		}
	}


	if (_is_boss) {
		//	_bossBattle.Update();
	}
}


void Dungeon::Draw()
{
	//時間になったら初期化
	if (_timer.HasTimeUp() && !_is_boss)
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


	//メッセージウィンドウ更新
	_messageReciever.Update();
	_messageReciever.Draw();

	//ステージ名表示
	Debug::DrawRectWithSize(Vector2D(970, 40), Vector2D(250, 60), Color4(0.5, 0.65, 0.85, 1.0), true);
	Debug::DrawRectWithSize(Vector2D(970, 40), Vector2D(250, 60), ColorPalette::WHITE4, false);
	Debug::DrawString(Vector2D(1010, 64), "洞窟ダンジョン その" + _stageName);

	if (_is_boss) {
		_counter.Draw();
	}
	else {
		//残り時間表示
		_timer.Draw();
	}

	DrawEnemyTimer();
}

void Dungeon::DrawEnemyTimer() {

	//ノルマ表示
	//std::string passed = "×";
	//Debug::DrawString(_waveInfomartionTimer.GetPosition() + Vector2D(30, 170), passed);
	std::string passed = std::to_string(_permitivePassedNum - _goal->GetPassedNum());
	auto color = (_permitivePassedNum - _goal->GetPassedNum() <= 0) ? ColorPalette::RED4 : ColorPalette::BLACK4;
	Debug::DrawString(_hartFrame.GetPosition() + Vector2D(64, 58), passed, color, 48);
	/*
	passed += "/";
	passed += std::to_string(_permitivePassedNum);
	Debug::DrawString(_waveInfomartionTimer.GetPosition() + Vector2D(60, 190), passed);
	*/
	//侵入者情報表示
	_intruderInformation.Draw();
}


void Dungeon::LoadMessage(std::string stageName)
{
	/*
	int messageNum = 0;
	if (stageName == "1")
	messageNum = 1;
	else if (stageName == "2")
	messageNum = 2;
	else if (stageName == "3")
	messageNum = 3;
	*/
	int messageNum = 0;
	try {
		messageNum = std::stoi(stageName);
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
		return;
	}
	catch (const std::out_of_range& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	std::string filePath = "csv/talkData/stage";
	filePath += stageName;
	filePath += "/";
	//_dungeonMessage.insert(std::make_pair("missed", _messageReciever._processer.CreateTalkData("csv/talkData/missed.csv", Talk_Type::nomal)));
	_dungeonMessage.insert(std::make_pair("start", _messageReciever._processer.CreateTalkData(filePath + "0_secretary_start.csv", Talk_Type::nomal)));
	_dungeonMessage.insert(std::make_pair("middle", _messageReciever._processer.CreateTalkData(filePath + "1_secretary_middle.csv", Talk_Type::nomal)));

	if (messageNum != 3)
	{
		_dungeonMessage.insert(std::make_pair("last", _messageReciever._processer.CreateTalkData(filePath + "2_secretary_last.csv", Talk_Type::nomal)));
	}
	else
	{
		_dungeonMessage.insert(std::make_pair("blaver", _messageReciever._processer.CreateTalkData(filePath + "3_blaver_appeared.csv", Talk_Type::nomal)));
		_dungeonMessage.insert(std::make_pair("last", _messageReciever._processer.CreateTalkData(filePath + "2_secretary_blaverAppeared.csv", Talk_Type::nomal)));
	}
}


void Dungeon::UpdateSecretary()
{
	auto timeRatio = _timer.GetTimeRatio();

	if (timeRatio == 0)
	{
		_messageReciever.Recieve(_dungeonMessage.at("start"));
		return;
	}

	if (timeRatio == 0.5)
	{
		_messageReciever.Recieve(_dungeonMessage.at("middle"));
		return;
	}

	if (_intrudeLastCharacter)
		return;

	if (_stageName == "1")
	{
		if ((_timer.GetCount() / 60) == 40)
		{
			_messageReciever.Recieve(_dungeonMessage.at("last"));
			_intrudeLastCharacter = true;
			return;
		}
	}
	else if (_stageName == "2")
	{
		if ((_timer.GetCount() / 60) == 50)
		{
			_messageReciever.Recieve(_dungeonMessage.at("last"));
			_intrudeLastCharacter = true;
			return;
		}
	}
	else
	{
		if (_start->GetTimeUnitlNext() == -1)
		{
			_messageReciever.Recieve(_dungeonMessage.at("last"));
			_messageReciever.Recieve(_dungeonMessage.at("blaver"));
			_intrudeLastCharacter = true;
		}
	}
}