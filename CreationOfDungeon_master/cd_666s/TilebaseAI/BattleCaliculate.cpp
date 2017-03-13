#include <algorithm>
#include "Character.h"

namespace Battle
{
    //物理攻撃用
    double GetPhysicalAttackDamage(int power, int attack, int defence)
    {
        double atk = attack;
        double def = defence;
        double damage = 0;

        if (atk <= 805)
            damage = 5 + std::pow(atk, 1.8) * std::pow(def, -0.5) * power * 0.01;
        else
            damage = 5 + std::pow(atk, 0.5) * std::pow(def, -0.5) * power * 60;

        return damage;
    }

    //魔法攻撃用
    double GetMagicalAttackDamage(int power, int attack, int defence)
    {
        double magicAtk = attack;
        double magicDef = defence;
        double damage = 0;

        if (magicAtk <= 1055)
            damage = 5 + std::pow(magicAtk, 1.65) * std::pow(magicDef, -0.5) * power * 0.01;
        else
            damage = 5 + std::pow(magicAtk, 0.5) * std::pow(magicDef, -0.5) * power * 30;

        return damage;
    }

    //物理被ダメージ用
    double GetPhysicalDefencedDamage(int power, int attack, int defence)
    {
        double atk = attack;
        double def = defence;
        double damage = 0;

        if (atk <= 346)
            damage = 5 + std::pow(atk, 2.0) * std::pow(def, -0.84) * power * 0.01;
        else
            damage = 5 + std::pow(atk, 0.7) * std::pow(def, -0.84) * power * 20;

        return damage;
    }

    //魔法被ダメージ用
    double GetMagicalDefencedDamage(int power, int attack, int defence)
    {
        double magicAtk = attack;
        double magicDef = defence;
        double damage = 0;

        if (magicAtk <= 742)
        {
            damage = 5 + std::pow(magicAtk, 1.85) * std::pow(magicDef, -0.84) * power * 0.01;
        }
        else
        {
            damage = 5 + std::pow(magicAtk, 0.7) * std::pow(magicDef, -0.84) * power * 20;
        }

        return damage;
    }

    double GetDamage(int power, int attack, bool isPhysical, Character& opponent)
    {
        double damage = 0;
        auto opponentType = opponent.GetType();
        auto param = opponent.GetAffectedParameter();

        if (opponentType == TiledObject::Type::ENEMY)
        {
            if (isPhysical)
            {
                damage = GetPhysicalAttackDamage(power, attack, param._defence);
            }
            else
            {
                damage = GetMagicalAttackDamage(power, attack, param._magicDefence);
            }
        }
        else
        {
            if (isPhysical)
            {
                damage = GetPhysicalDefencedDamage(power, attack, param._defence);
            }
            else
            {
                damage = GetMagicalDefencedDamage(power, attack, param._magicDefence);
            }
        }

        return damage;
    }
};