#pragma once

namespace Battle
{
	//�����U���p
	double GetPhysicalAttackDamage(int power, int attack, int defence);
	//���@�U���p
	double GetMagicalAttackDamage(int power, int attack, int defence);
	//������_���[�W�p
	double GetPhysicalDefencedDamage(int power, int attack, int defence);
	//���@��_���[�W�p
	double GetMagicalDefencedDamage(int power, int attack, int defence);
};
