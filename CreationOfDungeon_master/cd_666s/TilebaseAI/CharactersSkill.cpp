#include "CharactersSkill.h"
#include "DxLib.h"


CharactersSkill::CharactersSkill(BattleParameter& param)
    : _param(param)
{
}


CharactersSkill::~CharactersSkill()
{
}


void CharactersSkill::Update()
{
    auto mp = _param._mp;
    mp++;
    _param._mp = max(0, min(mp, _param._maxMP));
}


bool CharactersSkill::IsReadyToUse()
{
    return (_param._maxMP == _param._mp);
}