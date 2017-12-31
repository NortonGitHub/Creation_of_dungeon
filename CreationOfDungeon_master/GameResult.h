#include "cd_666s/Render/Sprite.h"
#include "RobTresureItem.h"

#pragma once
class GameResult
{
public:
	GameResult();
	~GameResult();

	void Init(std::string stagenum);

	void Calculation();

	void Update();
	void Draw();

	bool GetIsStop() { return IsStop; };
	int GetMoney() { return money; };

private:

	std::string _stageNum;

	int _count;

	int _magnification;

	int _defeatedNum;

	bool isBoss;

	std::shared_ptr<Sprite> _StageClearGr;
	std::shared_ptr<Sprite> _BossClearGr;
	std::shared_ptr<Sprite> _UnderLineGr;

	bool IsStop;

	struct ResultItem {
		std::shared_ptr<Sprite> _graph;
		RobTresureItem robTresureItem;
		int num;

	};

	std::vector<ResultItem> resultItem;

	std::vector<std::weak_ptr<Sprite>> displayObject;

	int money;
	

};

