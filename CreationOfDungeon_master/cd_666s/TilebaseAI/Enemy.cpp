#include "Enemy.h"
#include "TileField.h"
#include "AI/AstarChaser.h"
#include "../DebugDraw.h"
#include "ColleagueNotifyer.h"
#include "TiledObjectMnager.h"
#include "BattlingTile.h"
#include "EnemysItem.h"

#include "EnemysSearch.h"

int Enemy::_defeatedNum = 0;
int Enemy::_enemysNum = 0;

Enemy::Enemy(TiledVector startPos, BattleParameter params, TiledObject &baseTarget, ColleagueNotifyer& notifyer, std::string enemyName)
    : Character(startPos, params, notifyer, enemyName, TiledObject::Type::ENEMY)
    , _baseTarget(baseTarget)
    , _damageTimer(30, false, false)
{
    _target = &baseTarget;
    
    _astar = std::make_unique<AstarChaser>(_target, *this, _pathToTarget, 20, true);
    _ai = _astar.get();

    _appearSE.Load("resource/sound/blockSelect.wav");
    _hasTreasureIcon.Load("resource/graph/icon/treasure_attached.png");
    _hasTreasureIcon.SetScale(Vector2D(2.0, 2.0));
    _hasTreasureIcon.SetDisplayMode(false);
    _hasTreasureIcon.SetPriority(Sprite::Priority::UI);

    _consumableItems.resize(3);
    _consumableItemGraphs.resize(3);

    for (size_t i = 0; i<_consumableItemGraphs.size(); ++i)
    {
        _consumableItemGraphs[i].SetPriority(1090);
    }
    _equipmentsGraph.SetPriority(1090);
    BuildSearchingRuleList();
}


Enemy::~Enemy()
{
}


void Enemy::Think()
{
    _target = SearhTargetByRuleList();
    if (_target == nullptr)
        _target = &_baseTarget;

    //�͈͓��ɓ�������ǐՂ�
    if (_target != &_baseTarget)
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

    if (_damageTimer.IsCounting())
        _damageTimer.Update();

    //�퓬���ׂ����m�F
    if (!_afterBattleTimer.IsCounting()
        && !_isBattling)
    {
        auto monster = OBJECT_MGR->GetContainedObject<Monster>(_position + Vector2D(TILE_SIZE / 2, TILE_SIZE / 2));
        if (monster != nullptr
            && monster->IsEnable())
        {
            auto offset = monster->GetPosition() - _position;
            if (offset.GetLength() < TILE_SIZE / 4)
            {
                Battle(monster);
                return;
            }
        }
    }

    if (!CheckActable())
        return;

    //��Ԋm�F�t�F�C�Y
    //�ڕW���������Ă����猳�̕W�I��
    if (_target == nullptr || !_target->IsEnable())
    {
        _target = &_baseTarget;
        _astar->SetTarget(_target);
    }
    
    if (_damageTimer.IsCounting())
        return;

    Character::Action();

    auto graphSize = _hasTreasureIcon.GetSize();
    _hasTreasureIcon.SetPosition(_position + Vector2D(TILE_SIZE - graphSize._x, 0));
}


void Enemy::Act()
{
    if (_skill.get() != nullptr
        && _skill->ShouldActivate())
    {
        _skill->Activate();
        return;
    }

    //�̗͂������ȉ��ŃA�C�e�����������Ă���Ȃ��
    auto param = GetAffectedParameter();
    if (param._hp <= param._maxHP / 2)
        UseItem(param);

    //�ړ����������ĂȂ��Ȃ�ڕW�ֈړ�
    if (0 < _pathToTarget.size())
    {
        //������������ǐՂ��Ă��Ƃ�(�q�[���\��)��
        //����O�Ŏ~�܂�
        if (_target->GetType() == _type)
        {
            if (1 < _pathToTarget.size())
                MoveToNext();
        }
        else
        {
            MoveToNext();
        }

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


void Enemy::ObtainItem(TiledObject* target)
{
    //�A�C�e�����ׂɂȂ���ΏI��
    auto offset = _target->GetTilePos() - GetTilePos();
    if (offset.GetBresenhamLength(false) > 1)
        return;

    auto equipment = dynamic_cast<EnemysItem<Equipment>*>(target);
    if (equipment != nullptr)
    {
        //����΃A�C�e���擾
        equipment->GiveItem(*this);
    }
    else
    {
        auto item = dynamic_cast<EnemysItem<ConsumableItem>*>(target);
        if (item != nullptr)
        {
            //����΃A�C�e���擾
            item->GiveItem(*this);
        }
        else
        {
            return;
        }
    }

    _notifyer.NotifyRemoveTarget(*_target);

    //���̖ڕW��
    _target = &_baseTarget;
    _astar->SetTarget(&_baseTarget);
    _astar->SetSearchRange(20);
    
    _ai->Update();
}


void Enemy::ArriveAtGoal(TiledObject* target)
{
    _hasAppeared = false;
    _hasArrived = true;

	_target = nullptr;
	
    target->Interact(*this);
    OBJECT_MGR->Remove(this);
	_notifyer.NotifyRemoveTarget(*this);

	_tempParam = Character::GetRawParameter();

}


void Enemy::Battle(TiledObject* target)
{
    // TODO : ���}���u�Ƃ��āB
    auto enemy = OBJECT_MGR->GetSharedObject<Enemy>(this);
    auto monster = OBJECT_MGR->GetSharedObject<Monster>(target);
    OBJECT_MGR->Add(std::make_shared<BattlingTile>(enemy, monster, GetTilePos()));
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


void Enemy::UseItem(BattleParameter& param)
{
    for (size_t i = 0; i < _consumableItems.size(); ++i)
    {
        if (_consumableItems[i] != nullptr)
        {
            _consumableItems[i] = nullptr;
            _consumableItemGraphs[i].SetResource(nullptr);
            Damaged(-param._maxHP / 2);
            break;
        }
    }

    //�ȉ��A�A�C�e��������ΏI��
    if (_equipItem != nullptr)
        return;

    for (size_t i = 0; i < _consumableItems.size(); ++i)
    {
        if (_consumableItems[i] != nullptr)
            return;
    }

    //�����܂Ŕ�������A�C�e�����������Ă��Ȃ��̂ŃA�C�R������
    _hasTreasureIcon.SetDisplayMode(false);
}


void Enemy::SetTarget(Character *target) 
{
    if (!IsEnable() || !IsAlive())
        return;

    //�ڕW�̏�����
    ResetTarget();

    _target = target; 
    _astar->SetTarget(target); 
}


void Enemy::ResetTarget()
{
    Character::ResetTarget();
    _target = &_baseTarget;
    _astar->SetTarget(_target);
}


void Enemy::OnDie()
{
    Character::OnDie();
    
    //�e�p�����[�^�����Z�b�g
    _target = nullptr;
    _defeatedNum++;

    //�t�B�[���h���珜�O
    OBJECT_MGR->Remove(this);

    //������ǐՂ��Ă������Ԃ͂�����߂�悤�ɂ���
    _notifyer.NotifyRemoveTarget(*this);
}


bool Enemy::IsOverwritable(TiledObject* overwriter)
{
    if (overwriter == this)
        return true;
    
    return true;
}