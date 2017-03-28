#include "Enemy.h"
#include "TileField.h"
#include "AI/AstarChaser.h"
#include "../DebugDraw.h"
#include "ColleagueNotifyer.h"
#include "TiledObjectMnager.h"
#include "BattlingTile.h"
#include "EnemysItem.h"

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

    _appearSE.Load("resourse/sound/blockSelect.wav");
    _hasTreasureIcon.Load("resourse/graph/icon/treasure_attached.png");
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

    if (_damageTimer.IsCounting())
        _damageTimer.Update();

    if (!CheckActable())
        return;

    //��Ԋm�F�t�F�C�Y
    //�ڕW���������Ă����猳�̕W�I��
    if (_target == nullptr || !_target->IsEnable())
    {
        _target = &_baseTarget;
        _astar->SetTarget(_target);
    }
    
    //�퓬���ׂ����m�F
    if (!_afterBattleTimer.IsCounting())
    {
        auto offset = _target->GetPosition() - _position;
        
        if (_target->GetType() == TiledObject::Type::MONSTER
            && offset.GetLength() < TILE_SIZE / 4)
        {
            Battle(_target);
            return;
        }
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
        //&& _skill->IsReadyToUse()
        && _skill->ShouldActivate())
    {
        _skill->Activate();
        return;
    }

    //�ړ���Ƃ̍�������������X�V
    //UpdateAttitude();
    
    //�̗͂������ȉ��ŃA�C�e�����������Ă���Ȃ��
    auto param = GetAffectedParameter();
    if (param._hp <= param._maxHP / 2)
        UseItem(param);

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
            
            //�ǐՑΏۂ��ǂ����`�F�b�N
            if (obj->GetType() != TiledObject::Type::MONSTER)
            {
                //�A�C�e�����擾�\���`�F�b�N
                if (obj->GetType() != TiledObject::Type::ITEM)
                    continue;

                auto objPtr = dynamic_cast<EnemysItem<Equipment>*>(obj);
                if (objPtr != nullptr)
                {
                    if (objPtr->IsEmpty())
                        continue;

                    if (_equipItem != nullptr)
                        continue;
                }
                else
                {
                    auto ptr = dynamic_cast<EnemysItem<ConsumableItem>*>(obj);
                    if (ptr->IsEmpty())
                        continue;

                    bool result = false;
                    for (size_t i = 0; i<_consumableItems.size(); ++i)
                    {
                        if (_consumableItems[i] == nullptr)
                        {
                            result = true;
                            break;
                        }
                    }

                    if (!result)
                        continue;
                }
            }
            
            //�Ώۂ�����(���݂��Ȃ��Ȃ�)�Ȃ疳��
            if (!obj->IsEnable())
                continue;
            
            //�ʂ̒��Ԃ����łɑΏۂɂ��Ă���Ȃ疳��
            if (!_notifyer.IsChasable(*obj))
                continue;
            
            //�����܂ŗ�����߂��ق���D�悷��悤�ɂ���
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
    //TODO : �S�[��������Ԃ�ǉ�����Ȃǂ���
    //�S�[��������^�[�Q�b�e�B���O����Ȃ�������p�ӂ���
    _hasAppeared = false;
    target->Interact(*this);
    OBJECT_MGR->Remove(this);
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
}


bool Enemy::IsOverwritable(TiledObject* overwriter)
{
    if (overwriter == this)
        return true;
    
    return true;
}