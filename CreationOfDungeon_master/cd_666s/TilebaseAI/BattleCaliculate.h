#pragma once

namespace Battle
{
	//物理攻撃用
	double GetPhysicalAttackDamage(int power, int attack, int defence);
	//魔法攻撃用
	double GetMagicalAttackDamage(int power, int attack, int defence);
	//物理被ダメージ用
	double GetPhysicalDefencedDamage(int power, int attack, int defence);
	//魔法被ダメージ用
	double GetMagicalDefencedDamage(int power, int attack, int defence);
};
