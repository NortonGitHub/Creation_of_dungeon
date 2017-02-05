#include "Enemy.h"
#include "TileField.h"
#include "AI/AstarChaser.h"
#include "../DebugDraw.h"
#include "ColleagueNotifyer.h"
#include "TiledObjectMnager.h"
#include "BattlingTile.h"

int Enemy::_defeatedNum = 0;
int Enemy::_enemysNum = 0;

Enemy::Enemy(TiledVector startPos, BattleParameter params, TiledObject &baseTarget, ColleagueNotifyer& notifyer, std::string enemyName)
: Character(startPos, params, notifyer, enemyName)
, _baseTarget(baseTarget)
{
    _target = &baseTarget;
    
    _astar = std::make_unique<AstarChaser>(_target, *this, _pathToTarget, 20, true);
    //�����̖������o�H��ɂ������荞�܂��p������
    _astar->SetAdditionalFunc(std::move([&](TiledObject* obj)
    {
        if (obj->GetType() != _type)
            return false;

        auto enemy = dynamic_cast<Enemy*>(obj);
        return !enemy->_isBattling;
    }));
    _ai = _astar.get();

    _type = TiledObject::Type::ENEMY;

    _appearSE.Load("resourse/sound/blockSelect.wav");
}


Enemy::~Enemy()
{
}


void Enemy::Think()
{
    bool hasFound = SearchTarget();
    
    //�͈͓��ɓ�������ǐՂ�
    if (hasFound)
    {
        _astar->SetTarget(_target);
        _astar->SetSearchRange(6);
    }
    //�Ώۂ�������Ȃ��Ă��Ō�Ɍ��������n�_�܂ł��ǂ蒅������
    else
    {
        if (_pathToTarget.size() == 0)
        {
            //�S�[����ڎw������
            _target = &_baseTarget;
            _astar->SetTarget(&_baseTarget);
            _astar->SetSearchRange(20);
        }
    }
    
    _ai->Update();
}


void Enemy::Update()
{
    Character::Update();

    if (!CheckActable(60))
        return;

    //��Ԋm�F�t�F�C�Y
    //�ڕW���������Ă����猳�̕W�I��
    if (_target == nullptr || !_target->IsEnable())
    {
        _target = &_baseTarget;
        _astar->SetTarget(_target);
    }
    
    //�퓬���ׂ����m�F
    if (_countAfetrBattle == 0)
    {
        auto offset = _target->GetPosition() - _position;
        
        if (_target->GetType() == TiledObject::Type::MONSTER
            && offset.GetLength() < TILE_SIZE / 2)
        {
            Battle(_target);
            return;
        }
    }
    
    //�s���t�F�C�Y
    if (CheckActCounter())
    {
        //���E�X�V
        _sight = FIELD->GetParabolicMovableCell(GetTilePos(), 5, _direction);
    
        //�ӎv����
        Think();
    
        //�ӎv���s
        Act();
    }

    auto vec = (GetTilePos() - _beforeTilePos).GetWorldPos() - Vector2D(FIELD_OFFSET_X,FIELD_OFFSET_Y);
    _position += vec * (1.0 / (GetActInterval() + 1));
}


void Enemy::Act()
{
    //�ړ���Ƃ̍�������������X�V
    UpdateAttitude();
    
    //�ړ����������Ă�Ȃ��Ȃ�
    if (0 < _pathToTarget.size())
    {
        //�ڕW�ֈړ�
        MoveToNext();
        return;
    }
    
    //�ڕW�̏�ɂ��Ȃ���ΏI��
    if (_target->GetTile().lock() != GetTile().lock())
        return;

     switch(_target->GetType())
     {
     case TiledObject::Type::ITEM:
         ObtainItem(_target);
         return;

     case TiledObject::Type::GOAL:
         ArriveAtGoal(_target);
         return;
     }
}


bool Enemy::SearchTarget()
{
    //�Ώۂ����܂��ĂȂ��Ȃ王�E�ɓ��������̂�Ώۂ�
    int minOffset = 999;
    bool hasFound = false;
    
    //���E�ɓ��������̂�Ώۂɂ���
    for (size_t i=0; i<_sight.size(); ++i)
    {
        auto objects = FIELD->GetTiledObjects(_sight[i]);
        for (auto obj : objects)
        {
            if (obj == nullptr)
                continue;
            
            if (obj == &_baseTarget)
                continue;
            
            if (obj->GetType() != TiledObject::Type::MONSTER
                && obj->GetType() != TiledObject::Type::ITEM)
                continue;
            
            if (!obj->IsEnable())
                continue;
            
            if (!_notifyer.IsChasable(*obj))
                continue;
            
            int offset = (_sight[i] - GetTilePos()).GetBresenhamLength(false);
            if (minOffset <= offset)
                continue;
            
            if (obj->GetType() == TiledObject::Type::MONSTER)
            {
                auto monster = dynamic_cast<Monster*>(obj);
                if (monster->_isBattling)
                    continue;
            }

            minOffset = offset;
            _target = obj;
            hasFound = true;
        }
    }
    
    return hasFound;
}


void Enemy::ObtainItem(TiledObject* target)
{
    //�A�C�e�����ׂɂȂ���ΏI��
    auto offset = _target->GetTilePos() - GetTilePos();
    if (offset.GetBresenhamLength(false) > 1)
        return;
    
    //����΃A�C�e���擾
    _target->Interact(*this);
    _notifyer.NotifyRemoveTarget(*_target);
    
    //���̖ڕW��
    _target = &_baseTarget;
    _astar->SetTarget(&_baseTarget);
    _astar->SetSearchRange(20);
    
    _ai->Update();
}


void Enemy::ArriveAtGoal(TiledObject* target)
{
    //TODO : �S�[��������Ԃ�ǉ�����Ȃǂ���
    //�S�[��������^�[�Q�b�e�B���O����Ȃ�������p�ӂ���
    _hasAppeared = false;
    target->Interact(*this);
    OBJECT_MGR->Remove(this);
}


void Enemy::Battle(TiledObject* target)
{
    // TODO : ���}���u�Ƃ��āB
    auto chara = dynamic_cast<Monster*>(target);
    OBJECT_MGR->Add(std::make_shared<BattlingTile>(*this, *chara, GetTilePos()));
}


void Enemy::MoveToNext()
{
    //�ړ�������o����
    TiledVector pos = GetTilePos();
    pos = _pathToTarget[0];
    
    //�L���[����폜
    _pathToTarget.erase(_pathToTarget.begin());
    
    //�ړI�̌o�H�Ɉړ�
    FIELD->MoveObject(*this, pos);
}


void Enemy::ResetTarget()
{
    Character::ResetTarget();
    _target = &_baseTarget;
    _astar->SetTarget(_target);
}


void Enemy::OnAttacked(Character& attacker)
{
    //�U�����ꂽ��W�I���U�����Ă�����ɕύX
    Character::OnAttacked(attacker);
    _astar->SetTarget(&attacker);
}


void Enemy::OnDie()
{
    Character::OnDie();
    
    //�e�p�����[�^�����Z�b�g
    ResetCounter();
    _target = nullptr;
    _hasAppeared = false;
    _defeatedNum++;
}


bool Enemy::IsOverwritable(TiledObject* overwriter)
{
    if (overwriter == this)
        return true;
    
    if (overwriter->GetType() == Type::ENEMY)
        return (!_hasAppeared) && (!_isBattling);
    
    return true;
}