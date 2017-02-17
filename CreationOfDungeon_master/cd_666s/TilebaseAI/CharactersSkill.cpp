#include "CharactersSkill.h"
#include "DxLib.h"


CharactersSkill::CharactersSkill(BattleParameter& param, int cost)
    : _param(param)
    , _mp(0)
    , _mpCost(cost)
{
}


CharactersSkill::~CharactersSkill()
{
}


void CharactersSkill::Update()
{
    _mp++;
    _mp = max(0, min(_mp, _mpCost));
}


bool CharactersSkill::IsReadyToUse()
{
    return (_mpCost == _mp);
}