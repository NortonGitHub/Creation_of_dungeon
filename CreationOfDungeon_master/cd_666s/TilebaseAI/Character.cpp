#include "Character.h"
#include "TiledObjectMnager.h"
#include "ColleagueNotifyer.h"
#include "TileField.h"
#include "BattlingTile.h"
#include "../DebugDraw.h"

Character::Character(TiledVector startPos, const BattleParameter param, ColleagueNotifyer& notifyer, std::string name)
: TiledObject(startPos)
, _actCounter(0)
, _actInterval(30)
, _direction(TiledVector::Direction::FORWARD)
, _battleParameter(param)
, _notifyer(notifyer)
, _countAfetrBattle(0)
, _name(name)
, _isBattling(false)
, _hasAppeared(false)
, _target(nullptr)
, _battle(nullptr)
, _defeatSE("resourse/sound/enemy_fall2.wav")
{
    _notifyer.AddColleague(*this);
    
    _battleParameter._speed = fmin(100, fmax(_battleParameter._speed, 0));
    double speedRatio = static_cast<double>(100 - _battleParameter._speed + 15) / 100;
    _actInterval *= speedRatio;

    std::string fileName = "resourse/graph/tiledObject/";
    fileName += _name;
    _animator.AddAnimation("front", std::make_shared<GraphArray>(fileName + "_front.png", 32, 32, 2, 24));
    _animator.AddAnimation("right", std::make_shared<GraphArray>(fileName + "_right.png", 32, 32, 2, 24));
    _animator.AddAnimation("left", std::make_shared<GraphArray>(fileName + "_left.png", 32, 32, 2, 24));
    _animator.AddAnimation("back", std::make_shared<GraphArray>(fileName + "_back.png", 32, 32, 2, 24));

    _position = startPos.GetWorldPos();
    _beforeTilePos = GetTilePos();

    auto currentGraph = _animator.GetCurrentGraph();
    currentGraph->SetDisplayMode(false);
    _animator.Transform([&](GraphArray* animation)
    {
        animation->GetGraphPtr()->SetPosition(_position);
        animation->GetGraphPtr()->SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
        animation->GetGraphPtr()->SetRenderType(Texture2D::RenderType::UI);
    });
}


Character::~Character()
{
    _notifyer.RemoveColleague(*this);
}


void Character::Update()
{
    GraphicalObject::Update();

    if (!IsEnable())
        return;

    //�p�����X�V
    _animator.Transform([&](GraphArray* animation)
    {
        animation->GetGraphPtr()->SetPosition(_position);
    });

    //�o�t�X�V
    std::vector<std::unique_ptr<ParameterEffecter>> copy;
    for (size_t i = 0; i<_effecters.size(); ++i)
    {
        if (_effecters[i]->IsEnable())
        {
            _effecters[i]->UpdateCounter();
            copy.push_back(std::move(_effecters[i]));
        }
    }
    _effecters = std::move(copy);

    //�X�L���X�V
    if (_skill.get() != nullptr)
        _skill->Update();
}


void Character::Draw()
{
    auto currentGraph = _animator.GetCurrentGraph();
    currentGraph->SetDisplayMode(_hasAppeared && !_isBattling);

    if (!_hasAppeared || _isBattling)
        return;

    switch (_direction)
    {
    case TiledVector::Direction::FORWARD:
        _animator.SwitchWithReset("front");
        break;

    case TiledVector::Direction::LEFT:
        _animator.SwitchWithReset("left");
        break;

    case TiledVector::Direction::RIGHT:
        _animator.SwitchWithReset("right");
        break;

    case TiledVector::Direction::BACK:
        _animator.SwitchWithReset("back");
        break;
    }

    if (_position != GetTilePos().GetWorldPos())
    {
        _animator.Update();
    }

    //AI�̃f�o�b�O���
    if (_ai != nullptr)
        _ai->Draw();
}


bool Character::Contain(Vector2D pos) const
{
    auto size = _animator.GetCurrentAnimation()->GetSingleSize();
    
    if (pos._x < _position._x)
        return false;
    if (pos._y < _position._y)
        return false;
    if (_position._x + size._x * TILE_SCALE < pos._x)
        return false;
    if (_position._y + size._y * TILE_SCALE  < pos._y)
        return false;

    return true;
}


void Character::UpdateAttitude()
{
    TiledVector pos = GetTilePos();

    //�ړ���Ƃ̍�������������X�V
    TiledVector dir;
    if (_pathToTarget.size() == 0)
    {
        if (_target != nullptr)
            dir = _target->GetTilePos() - pos;
    }
    else
    {
        dir = _pathToTarget[0] - pos;
    }

    if (dir == TiledVector::up)
        _direction = TiledVector::Direction::FORWARD;
    else if (dir == TiledVector::down)
        _direction = TiledVector::Direction::BACK;
    else if (dir == TiledVector::left)
        _direction = TiledVector::Direction::LEFT;
    else if (dir == TiledVector::right)
        _direction = TiledVector::Direction::RIGHT;

    _beforeTilePos = pos;
}


void Character::OnOccuredBattle(BattlingTile* battle)
{
    _beforeTilePos = GetTilePos();
    _position = GetTilePos().GetWorldPos();
    _battle = battle;
    _isBattling = true;

    ResetTarget();
}


void Character::OnFinishBattle(BattlingTile* battle)
{
    if (battle == _battle)
        _battle = nullptr;

    _isBattling = false;
    _countAfetrBattle = 1;
}


bool Character::IsOverwritable(TiledObject* overwriter)
{
    return false;
}


bool Character::CheckActable(const int recoverCountFromAfterBattle)
{
    //�o�����ĂȂ���΍s���ł��Ȃ�
    if (!_hasAppeared)
        return false;

    //�o�g�����Ȃ�s���ł��Ȃ�
    if (_isBattling)
        return false;

    //�o�g������͓����Ȃ�(�A��h�~)
    if (0 < _countAfetrBattle)
    {
        _countAfetrBattle++;

        if (_countAfetrBattle < recoverCountFromAfterBattle)
            return false;
        else
            _countAfetrBattle = 0;
    }
    
    return true;
}


bool Character::CheckActCounter()
{
    bool result = (_actCounter == _actInterval);

    _actCounter++;
    if (_actInterval < _actCounter)
        _actCounter = 0;

    return result;
}


BattleParameter Character::GetAffectedParameter()
{
    BattleParameter param = _battleParameter;
    for (size_t i=0; i<_effecters.size(); ++i)
    {
        if (_effecters[i]->IsEnable())
            _effecters[i]->AffectParameter(param);
    }

    return param;
}


void Character::Damaged(int damage)
{
    if (IsEnable())
    {
        _battleParameter._hp -= damage;
        _battleParameter._hp = min(_battleParameter._maxHP, max(_battleParameter._hp, 0));
    }

    //�퓬�œ|���ꂽ�����m�F����
    if (!IsAlive())
    {
        OnDie();

        //��񋤗L�Ԃ�������O
        _notifyer.NotifyRemoveTarget(*this);
        ResetTarget();
        OnWin();
    }
}


void Character::OnDie()
{    
    //�t�B�[���h���珜�O
    OBJECT_MGR->Remove(this);
}


void Character::OnWin()
{
    ResetTarget();
    _defeatSE.Play();
}


void Character::Appear()
{
    _hasAppeared = true;
    _appearSE.Play();
}


bool Character::IsAlive() const
{
    return (0 < _battleParameter._hp);
}


bool Character::IsEnable() const
{
    return _hasAppeared;
}