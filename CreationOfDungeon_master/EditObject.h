#include <string>
#include <vector>
#include <memory>
#pragma once

class EditObject
{

public:
	EditObject();
	~EditObject();

	//使う構造体を以下に
	struct EditOblect_Block {   //店の売り物の情報

		std::string ObjectName;				  //オブジェクト名
		std::string ResourceName;
		int Cost;							//設置にかかるお金
		int IncreaseCost;							//複数設置時に設置コストが上がる割合
		std::string GenerateText;

	};

	struct EditOblect_Trap {   //店の売り物の情報

		std::string ObjectName;				  //オブジェクト名
		std::string ResourceName;
		int Cost;							//設置にかかるお金
		int IncreaseCost;							//複数設置時に設置コストが上がる割合
		std::string GenerateText;
		int level;
		int LevelUpCost;
	};

	struct EditOblect_Monster {   //店の売り物の情報

		std::string ObjectName;				  //オブジェクト名
		std::string ResourceName;
		int Cost;							//設置にかかるお金
		int IncreaseCost;							//複数設置時に設置コストが上がる割合
		std::string GenerateInformationPath;
		int level;
		int LevelUpCost;
	};

	std::vector<std::string> getEditOblectList(std::string CategoryName);

	void ResetLevel();

	int GetCost(std::string CategoryName, std::string objectName);
	int GetIncreaseCost(std::string CategoryName, std::string objectName);

	int GetEditObjectNum(std::string CategoryName);

private:

	std::vector<std::shared_ptr<EditOblect_Block>> editOblectBlockList;
	std::vector<std::shared_ptr<EditOblect_Trap>> editOblectTrapList;
	std::vector<std::shared_ptr<EditOblect_Monster>> editOblectMonsterList;

};

