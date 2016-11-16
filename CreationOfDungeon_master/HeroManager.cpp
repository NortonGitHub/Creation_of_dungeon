#include "HeroManager.h"
#include "CSVDataLoader.h"


HeroManager::HeroManager()
{
//	heroes = new HeroBase();
	heroes.reserve(10);
}

HeroManager::HeroManager(std::string stage_num)
	: _name("hero")
{

	std::vector<CharaBase*> temp;
	temp.reserve(10);
	
	CSVDataLoader::LoadCharaCSV(heroes, stage_num);
	
}


HeroManager::~HeroManager()
{
	std::vector<CharaBase*>().swap(heroes);
}

void HeroManager::Update()
{
	for (auto hero : heroes) {
		hero->Update();
	}
}

void HeroManager::Draw()
{
	for (auto hero : heroes) {
		hero->Draw();
	}
}
