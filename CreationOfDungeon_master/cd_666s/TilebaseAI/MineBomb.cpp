#include "MineBomb.h"
#include "MapTile.h"
#include "Enemy.h"
#include "../DebugDraw.h"
#include "TiledObjectMnager.h"

MineBomb::MineBomb(TiledVector trapPos)
    : Trap(trapPos, 220, 5)
    , _range(1)
    , _damage(50)
{
    _name = "mine";
    _graph.Load("resourse/graph/tiledObject/mine.png");
    _graph.SetPriority(200);
    _graph.SetPosition(_position);
    _graphArray.Set(&_graph, 32, 32, 8, 32);
    _graphArray._isLoop = false;
    _graphArray._isPlaying = false;
}


MineBomb::~MineBomb()
{
}


void MineBomb::Update()
{
    bool isOverrided = false;

    //�G�������̃}�X�ɂ��邩�ǂ���
    Enemy* target = GetTile().lock()->GetTiledObject<Enemy>();
    if (target != nullptr)
    {
        //��苗���܂ŋ߂Â����甭��
        auto distance = (target->GetPosition() - _position).GetLength();
        if (distance < TILE_SIZE / 4)
            isOverrided = true;
    }

    //�N�������炻�̃��[�v�ł̏����͏I��
    if (isOverrided && IsEnable())
    {
        _graphArray._isPlaying = true;
        _duravity -= _cost;
        target->Damaged(target->GetAffectedParameter()._maxHP / 2);
        return;
    }

    Trap::Update();
}


void MineBomb::Draw()
{
    _graphArray.Update();

    bool display = (!_graphArray.HasEndedUp() || IsEnable());

    //�������ɂ��邩�ǂ���
    float alpha = (display) ? 1.0 : 0.35;
    _graph.GetTexturePtr().lock()->SetBaseColor(Color4(1, 1, 1, alpha));

    //�ϋv�̓Q�[�W��\�����邩
    if (!display)
    {
        double ratio = static_cast<double>(_duravity) / static_cast<double>(_cost);
        Debug::DrawRectWithSize(_position + Vector2D(-16, 0), Vector2D(64, 8), ColorPalette::BLACK4, false);
        Debug::DrawRectWithSize(_position + Vector2D(-16, 0), Vector2D(64 * ratio, 8), ColorPalette::BLUE4, true);
    }
}


bool MineBomb::IsEnable() const
{
    return (_cost <= _duravity);
}