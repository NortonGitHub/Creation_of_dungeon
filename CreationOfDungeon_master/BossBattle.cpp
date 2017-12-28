#include "BossBattle.h"
#include "cd_666s\TilebaseAI\TiledObjectMnager.h"
#include "cd_666s/Resources/AllResourceManager.h"
#include "cd_666s/Utility/CSVReader.h"


BossBattle::BossBattle()
{
	_sequenceTimer = 0;
	now_situation = BattleSequence::None;
	_wasBossKilled = false;
}


BossBattle::~BossBattle()
{
}

void BossBattle::Init(std::string stageNum)
{
	std::string fileName = "csv/StageData/boss";
	fileName += stageNum + ".csv";

	std::vector<std::string> bossArray;
	CSVReader reader;
	reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, bossArray);
	_boss._hp = std::stoi(bossArray[0]);

}

void BossBattle::Update()
{
	if(_intruders.empty()){
		return ;
	}

	switch (now_situation)
	{
	case BattleSequence::None:
		break;
	case BattleSequence::Starting:
		Starting();
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

void BossBattle::SetBattleObject(std::vector<std::shared_ptr<TiledObject>>& objects, std::shared_ptr<TiledObject> intruder)
{
	auto param = intruder->GetRawParameter();

	auto _lead = !(_intruders.empty());

	_intruders.push({ _lead, param });

	OBJECT_MGR->Add(intruder);
}

bool BossBattle::HasKilled(BattleParameter atk, BattleParameter& dff)
{
	auto dmg = atk._attack;
	dff._hp -= dmg;

	if (0 <= dff._hp) {
		return true;
	}
	return false;
}

void BossBattle::GenerateObject(std::string typeName)
{
}

void BossBattle::Starting()
{
	if(_sequenceTimer >= 2500){
		_sequenceTimer = 0;
		now_situation = BattleSequence::EnemyAttack;
	}

	++_sequenceTimer;
}

void BossBattle::EnemyAttack()
{
	auto enemy = _intruders.front();
	if (_sequenceTimer >= 2500) {
		_intruders.pop();	//UŒ‚‚ðI‚¦‚½“G‚Í”z—ñ‚©‚çœ‹Ž
		_sequenceTimer = 0;
		now_situation = BattleSequence::None;
	}

	if (HasKilled(enemy._param, _boss)) {
		now_situation = BattleSequence::BossDied;
		return;
	}
	++_sequenceTimer;
}

void BossBattle::BossAttack()
{
	if (_sequenceTimer >= 2500) {
		_intruders.pop();
		_sequenceTimer = 0;
		now_situation = BattleSequence::None;
	}

	++_sequenceTimer;
}

void BossBattle::BossDied()
{
	if (_sequenceTimer >= 2500) {
		return;
	}

	++_sequenceTimer;
}
