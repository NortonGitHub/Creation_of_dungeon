#include "Trap.h"
#include "../DebugDraw.h"


Trap::Trap(TiledVector startPos, int duravity, int level)
    : TiledObject(startPos)
    , _duravity(duravity)
    , _cost(duravity)
    , _level(level)
{
    _type = TiledObject::Type::TRAP;
    _position = startPos.GetWorldPos();
}


Trap::~Trap()
{
}


void Trap::Update()
{
    _duravity++;
    _duravity = min(_cost, max(_duravity, 0));

    if (IsActivatable())
        Activate();
}


void Trap::Draw()
{
    GraphicalObject::Draw();

    bool display = Trap::IsActivatable();

    //�������ɂ��邩�ǂ���
    float alpha = (display) ? 1.0f : 0.35f;
    auto tex = _graph.GetTexturePtr();
    if (!tex.expired())
        tex.lock()->SetBaseColor(Color4(1, 1, 1, alpha));

    //�ϋv�̓Q�[�W��\�����邩
    if (!display)
    {
        double ratio = static_cast<double>(_duravity) / static_cast<double>(_cost);
        Debug::DrawRectWithSize(_position + Vector2D(-16, 0), Vector2D(64, 8), ColorPalette::BLACK4, false);
        Debug::DrawRectWithSize(_position + Vector2D(-16, 0), Vector2D(64 * ratio, 8), ColorPalette::BLUE4, true);
    }
}

//�g���b�v���N���ł��邩�ǂ���
bool Trap::IsActivatable() const
{
    return IsEnable();
}

//�g���b�v���N��
void Trap::Activate()
{
    _duravity -= _cost;
}