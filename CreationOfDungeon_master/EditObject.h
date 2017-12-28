#include <string>
#include <vector>
#include <memory>
#pragma once

class EditObject
{

public:
	EditObject();
	~EditObject();

	//�g���\���̂��ȉ���
	struct EditOblect_Block {   //�X�̔��蕨�̏��

		std::string ObjectName;				  //�I�u�W�F�N�g��
		std::string ResourceName;
		std::string GenerateText;

	};

	struct EditOblect_Trap {   //�X�̔��蕨�̏��

		std::string ObjectName;				  //�I�u�W�F�N�g��
		std::string ResourceName;             
		std::string GenerateText;
		int level;
		int LevelUpCost;
	};

	struct EditOblect_Monster {   //�X�̔��蕨�̏��

		std::string ObjectName;				  //�I�u�W�F�N�g��
		std::string ResourceName;
		std::string GenerateInformationPath;
		int level;
		int LevelUpCost;
	};

	std::vector<std::string> getEditOblectList(std::string CategoryName);

	void ResetLevel();

private:

	std::vector<std::shared_ptr<EditOblect_Block>> editOblectBlockList;
	std::vector<std::shared_ptr<EditOblect_Trap>> editOblectTrapList;
	std::vector<std::shared_ptr<EditOblect_Monster>> editOblectMonsterList;

};

