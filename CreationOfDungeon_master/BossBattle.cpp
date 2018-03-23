#include "BossBattle.h"
#include "cd_666s\TilebaseAI\TiledObjectMnager.h"
#include "cd_666s/Resources/AllResourceManager.h"
#include "cd_666s/Utility/CSVReader.h"

#include "BossBattleObject.h"
#include "cd_666s\TilebaseAI\ColleagueNotifyer.h"
#include <array>

BossBattle::BossBattle()
	: _battleTime(100)
	, _readyTime(100)
	, _diedTime(100)
{
	_sequenceTimer = 0;
	now_situation = BattleSequence::Ready;
	_wasBossKilled = false;
}


BossBattle::~BossBattle()
{
}

void BossBattle::Init(std::string stageNum, std::vector<std::shared_ptr<TiledObject>>& objects, ColleagueNotifyer &notifyer)
{
	std::string fileName = "csv/boss/boss";
	fileName += stageNum + ".csv";

	std::vector<std::string> bossArray;
	CSVReader reader;
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, bossArray, 1);

	std::array<int, 6> param_i;

	for (size_t i = 0; i < param_i.size();i++) {
		param_i[i] = std::stoi(bossArray[i]);
	}

	BattleParameter param = { param_i[0], param_i[1], param_i[2], param_i[3], param_i[4], param_i[5] };
	auto _pos = Vector2D(std::stod(bossArray[6]), std::stod(bossArray[7]));
	std::string name = bossArray[8];
	name += stageNum;

	_boss = std::move(std::make_shared<BossBattleObject>(_pos, param, notifyer, name, true));

	objects.push_back(_boss);
}

void BossBattle::Update()
{
	if(_intruders.size() < 1){
		_boss->SetInRoom(false);
		_boss->SwitchAnime(false);
		return ;
	}
	
	_boss->SetInRoom(true);
	_intruders.front()->SetInRoom(true);
	
	switch (now_situation)
	{
	case BattleSequence::None:
		break;
	case BattleSequence::Ready:
		Ready();
		break;
	case BattleSequence::EnemyAttack:
		EnemyAttack();
		break;
	case BattleSequence::BossAttack:
		BossAttack();
		break;
	case BattleSequence::BossDied:
		BossDied();
		break;
	default:
		break;
	}
}

void BossBattle::SetBattleObject(std::shared_ptr<TiledObject>& intruder, ColleagueNotifyer& notifyer)
{
	auto param = intruder->GetRawParameter();
	std::string name = intruder->GetName();
	auto _pos = Vector2D(600, 600); 

	auto _intruder = std::make_shared<BossBattleObject>(_pos, param, notifyer, name, false);

	_intruder->SetInRoom(true);
	_intruders.push_back(_intruder);
}

bool BossBattle::HasKilled(BattleParameter& atk, BattleParameter& dff)
{
	int dmg = atk._attack;
	dff._hp -= dmg;

	if (dff._hp <= 0) {
		return true;
	}
	return false;
}

void BossBattle::GenerateObject(std::string typame)
{
}

void BossBattle::Ready()
{
	_boss->SwitchAnime(false);
	if(_sequenceTimer >= _readyTime){
		_sequenceTimer = 0;
		now_situation = BattleSequence::EnemyAttack;
	}

	++_sequenceTimer;
}

void BossBattle::EnemyAttack()
{
	auto enemy = _intruders.front();
	_boss->SwitchAnime(true);

	if (_sequenceTimer >= _battleTime) {
		auto& e = enemy->GetRawParameter();
		auto& b = _boss->_param;
		
 		if (HasKilled(e, b)) {
			now_situation = BattleSequence::BossDied;
			_boss->SwitchAnime(false);
			return;
		}
		_sequenceTimer = 0;
		
		now_situation = BattleSequence::BossAttack;

		return;
	}
	++_sequenceTimer;
}

void BossBattle::BossAttack()
{
	_boss->SwitchAnime(false);
	if (_sequenceTimer >= _battleTime) {
		_sequenceTimer = 0;
		now_situation = BattleSequence::Ready;
		_intruders.front()->OutBossRoom();
		_intruders.pop_front();	//UŒ‚‚ðI‚¦‚½“G‚Í”z—ñ‚©‚çœ‹Ž
	}

	++_sequenceTimer;
}

void BossBattle::BossDied()
{
	if (_sequenceTimer >= _diedTime) {
		_wasBossKilled = true;
		_boss->Clear();
		return;
	}

	++_sequenceTimer;
}
