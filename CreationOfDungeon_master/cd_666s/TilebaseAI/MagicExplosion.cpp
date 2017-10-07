#include "MagicExplosion.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "BattlingTile.h"
#include "BattleCaliculate.h"


MagicExplosion::MagicExplosion(int power, int attack, int range, TiledVector pos, TiledObject::Type type, std::shared_ptr<ImageResource> image)
    : TiledObject(pos)
    , _power(power)
    , _magicAttack(attack)
    , _range(range)
    , _shooterType(type)
    , _hasJudged(false)
{
    _graph.SetResource(image);
    _graph.SetPosition((pos - TiledVector(range, range)).GetWorldPos());
    int divNum = _graph.GetSize()._x / 32;

    auto scale = (range * 2 + 1) * TILE_SCALE;
    _graph.SetScale(Vector2D(scale, scale));
    _animation.Set(&_graph, 32, 32, divNum, 32);
    _animation._isLoop = false;    

    _sound.Load("resource/sound/flame.wav");
}


MagicExplosion::~MagicExplosion()
{
}


void MagicExplosion::Update()
{
    _animation.Update();

    if (_animation.HasEndedUp())
        OBJECT_MGR->Remove(this);

    if (_hasJudged)
        return;

    CheckHit();
}


void MagicExplosion::CheckHit()
{
    _hasJudged = true;

    TiledVector pos;
    TiledVector currentPos = GetTilePos();
    auto opponentType = (_shooterType == Type::ENEMY) ? Type::MONSTER : Type::ENEMY;

    for (int i = -_range; i <= _range; ++i)
    {
        for (int k = -_range; k <= _range; ++k)
        {
            if (i == 0 && k == 0)
                continue;

            pos = currentPos + TiledVector(i, k);
            auto objects = FIELD->GetTiledObjects(pos);

            for (auto obj : objects)
            {
                if (!obj->IsEnable())
                    continue;

                //敵かバトル中マスがあったら相手にダメージ
                if (obj->GetType() == opponentType)
                {
                    auto chara = dynamic_cast<Character*>(obj);
                    auto opponentParam = chara->GetAffectedParameter();

                    if (opponentType == Type::ENEMY)
                        chara->Damaged(Battle::GetMagicalAttackDamage(_power, _magicAttack, opponentParam._magicDefence));
                    else
                        chara->Damaged(Battle::GetMagicalDefencedDamage(_power, _magicAttack, opponentParam._magicDefence));

                    _sound.Play();
                    break;
                }

                if (obj->GetType() == Type::BATTLE)
                {
                    auto battle = dynamic_cast<BattlingTile*>(obj);
                    if (opponentType == Type::ENEMY)
                        battle->MagicalAttack(_power, _magicAttack);
                    else
                        battle->MagicalDamaged(_power, _magicAttack);

                    _sound.Play();
                    break;
                }
            }
        }
    }
}