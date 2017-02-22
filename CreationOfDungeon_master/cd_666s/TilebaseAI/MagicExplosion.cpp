#include "MagicExplosion.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "BattlingTile.h"
//#include "Character.h"

MagicExplosion::MagicExplosion(int power, int range, TiledVector pos, TiledObject::Type type)
    : TiledObject(pos)
    , _power(power)
    , _range(range)
    , _shooterType(type)
    , _hasJudged(false)
{
    if (_shooterType == TiledObject::Type::ENEMY)
        _graph.Load("resourse/graph/tiledObject/explosion.png");
    else
        _graph.Load("resourse/graph/tiledObject/mine.png");

    _animation.Set(&_graph, 32, 32, 8, 32);
    _animation._isLoop = false;

    _graph.SetPosition((pos - TiledVector(range, range)).GetWorldPos());
    _graph.SetScale(Vector2D((range * 2 + 1) * TILE_SIZE / 32.0, (range * 2 + 1) * (TILE_SIZE / 32.0)));
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
                    chara->Damaged(20);
                    break;
                }

                if (obj->GetType() == Type::BATTLE)
                {
                    auto battle = dynamic_cast<BattlingTile*>(obj);
                    battle->Damaged(20, _shooterType);
                    break;
                }
            }
        }
    }
}