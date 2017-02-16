#include "Monster.h"
#include "TileField.h"
#include "AI/AstarChaser.h"
#include "../DebugDraw.h"
#include "ColleagueNotifyer.h"
#include "BattlingTile.h"
#include "TiledObjectMnager.h"

Monster::Monster(TiledVector startPos, BattleParameter param, TiledObject *target, ColleagueNotifyer& notifyer, std::string monsterName)
: Character(startPos, param, notifyer, monsterName)
, _hasChoosed(false)
{
    _target = target;
    _astar = std::make_unique<AstarChaser>(_target, *this, _pathToTarget, 100, true);
    _astar->SetAdditionalFunc(std::move([&](TiledObject* obj)
    {
        if (obj->GetType() != Type::ENEMY)
            return false;

        auto enemy = dynamic_cast<Enemy*>(obj);
        return (!enemy->_isBattling); 
    }));

    _ai = _astar.get();

    _type = TiledObject::Type::MONSTER;
    _appearSE.Load("resourse/sound/flame.wav");
    _appearSE.SetVolume(200);
}


Monster::~Monster()
{
}


void Monster::Think()
{
    if (_target != nullptr)
        _ai->Update();
}


void Monster::Update()
{
    Character::Update();

    //���@�w�̏�ɂ���Ȃ炳��ɉ�
    auto magicSquare = FIELD->GetTiledObject<MagicSquare>(GetTilePos());
    if (magicSquare != nullptr)
         magicSquare->Interact(*this);
    
    //�o�����ĂȂ���΍s���ł��Ȃ�
    if (!_hasAppeared)
        return;

    //�o�g�����Ȃ�s���ł��Ȃ�
    if (_isBattling)
        return;

    //�o�g������͓����Ȃ�(�A��h�~)
    if (0 < _countAfetrBattle)
    {
        _countAfetrBattle++;

        if (30 < _countAfetrBattle)
            _countAfetrBattle = 0;
    }

    if (CheckActCounter())
    {
        //�w�����Ȃ���ΏI��
        if (_ai == nullptr)
            return;
    
        //���E
        _sight = FIELD->GetParabolicMovableCell(GetTilePos(), 5, _direction);
    
        //�ӎv����
        Think();
    
        //�ӎv���s
        Act();
    }
    
    auto vec = (GetTilePos() - _beforeTilePos).GetWorldPos() - Vector2D(FIELD_OFFSET_X, FIELD_OFFSET_Y);
    _position += vec * (1.0 / (GetActInterval() + 1));
}


void Monster::Act()
{
    //�ړ���Ƃ̍�������������X�V
    UpdateAttitude();
   
    //���̃^�C���ֈړ�
    MoveToNext();
}


void Monster::MoveToNext()
{
    if (_pathToTarget.size() == 0)
        return;

    if (_countAfetrBattle == 0 )
    {
        //�G�����ʂ��痈��Ȃ�҂��\����
        auto obj = FIELD->GetTiledObject<Enemy>(GetTilePos());
        if (obj != nullptr)
            return;
    }
    
    //�ړ�������o����
    TiledVector pos = GetTilePos();
    pos = _pathToTarget[0];
    
    //�L���[����폜
    _pathToTarget.erase(_pathToTarget.begin());
    FIELD->MoveObject(*this, pos);
}


void Monster::ResetTarget()
{
    Character::ResetTarget();
    _astar->SetTarget(nullptr);
}


void Monster::DrawTargetMarker()
{
    if (_target != nullptr)
    {
        auto worldPos = _target->GetPosition() + Vector2D(TILE_SIZE / 2, TILE_SIZE / 2);
        Debug::DrawCircle(worldPos,
            TILE_SIZE, ColorPalette::BLACK4, false);

        Debug::DrawLine(worldPos + Vector2D(-TILE_SIZE / 2, 0), worldPos + Vector2D(TILE_SIZE / 2, 0), ColorPalette::BLACK4);
        Debug::DrawLine(worldPos + Vector2D(0, -TILE_SIZE / 2), worldPos + Vector2D(0, TILE_SIZE / 2), ColorPalette::BLACK4);
    }
}

//���@�w�ւ̌Ăі߂�
void Monster::WarpToHome(const MagicSquare& square)
{
    //�o�g�����Ȃ�o�g�����痣�E
    if (_isBattling)
    {
        _battle->RunAway();
        ResetCounter();
    }

    OnDie();
}


void Monster::SetTarget(TiledObject *target)
{
    if (!IsEnable() || !IsAlive())
        return;
        
    //�ڕW�̏�����
    ResetTarget();
    
    //�ڕW�ݒ�
    _target = target;
    _astar->SetTarget(target);
    
    //�o�g�����Ȃ�o�g���I��
    if (_isBattling)
    {
        _battle->RunAway();
        ResetCounter();
    }
}


void Monster::SetTarget(TiledVector pos)
{
    if (!IsEnable() || !IsAlive())
        return;
    
    //�����ֈړ�
    _target = nullptr;
    _astar->SetTarget(pos);
    _astar->FindPath();
    
    //�o�g�����Ȃ�o�g���I��
    if (_isBattling)
    {
        _battle->RunAway();
        ResetCounter();
    }
}


void Monster::OnAttacked(Character& attacker)
{
    //�U�����ꂽ��W�I���U�����Ă�����ɕύX
    Character::OnAttacked(attacker);
    _astar->SetTarget(&attacker);
}


void Monster::OnDie()
{
    //�w�ɖ߂�
    auto homePos = _home->GetTilePos();
    _beforeTilePos = homePos;
    _position = homePos.GetWorldPos();
    FIELD->MoveObject(*this, homePos);

    //�e�p�����[�^�����Z�b�g
    _hasChoosed = false;
    
    //�e�p�����[�^�����Z�b�g
    ResetCounter();
    ResetTarget();
    _pathToTarget.resize(0);
    _hasAppeared = false;
}


bool Monster::IsRunnable()
{
    auto tilePos = GetTilePos();
    
    if (FIELD->IsMovableThere(tilePos + TiledVector(0, 1), *this))
        return true;
    
    if (FIELD->IsMovableThere(tilePos + TiledVector(0, -1), *this))
        return true;

    if (FIELD->IsMovableThere(tilePos + TiledVector(1, 0), *this))
        return true;

    if (FIELD->IsMovableThere(tilePos + TiledVector(-1, 0), *this))
        return true;
    
    return false;
}

//�����\���ǂ���
bool Monster::IsReadyToProduce() const
{
    //�̗͂��ő� & ��������ĂȂ��Ȃ珢���\
    return (_battleParameter._maxHP == _battleParameter._hp)
            && (!_hasAppeared);
}

bool Monster::IsOverwritable(TiledObject* overwriter)
{
    if (overwriter == this)
        return true;

    if (overwriter->GetType() == Type::ENEMY)
        return !_isBattling;

    if (overwriter->GetType() == Type::MONSTER)
        return false;
    
    return true;
}