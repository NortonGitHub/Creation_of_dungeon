#include "CharaManager.h"

#if 0
#include "HeroBase.h"
#include "MonsterBase.h"
#include "ObstacleBase.h"
#include "SummonsBase.h"
#endif

#include "HeroManager.h"
#include "MonsterManager.h"
#include "ObstacleManager.h"
#include "SummonsManager.h"

CharaManager::CharaManager() {
}

CharaManager::CharaManager(std::string stage_num)
{
#if 0
	character.reserve(5);
	character.push_back(new HeroBase());
	character.push_back(new MonsterBase());
	character.push_back(new ObstacleBase());
	character.push_back(new SummonsBase());
#endif
	chara.push_back(new HeroManager(stage_num));
	chara.push_back(new MonsterManager(stage_num));
	chara.push_back(new ObstacleManager(stage_num));
	chara.push_back(new SummonsManager(stage_num));

}


CharaManager::~CharaManager()
{
}

void CharaManager::Update(MouseContent mc)
{
#if 0
	for (auto chara : character) {
		chara->GetManagerInstance()->Update();
	}
#endif
	
	for (auto c : chara) {
		c->Update();
	}
}

void CharaManager::Draw()
{
#if 0
	for (auto chara : character) {
		chara->GetManagerInstance()->Draw();
	}
#endif
	for (auto c : chara) {
		c->Draw();
	}
}
