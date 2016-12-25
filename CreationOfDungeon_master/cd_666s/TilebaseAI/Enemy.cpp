#include "Enemy.h"
#include "TileField.h"
#include "AI/AstarChaser.h"
#include "../Resources/ResourceManager.h"
#include "../DebugDraw.h"
#include "StartPoint.h"
#include "Goal.h"
#include "ColleagueNotifyer.h"
#include "TiledObjectMnager.h"
#include "BattlingTile.h"

#include <array>
#include "../Utility/CSVReader.h"


Enemy::Enemy(TiledVector startPos, BattleParameter params, TiledObject &baseTarget, ColleagueNotifyer& notifyer)
: Character(startPos, params, notifyer)
, _baseTarget(baseTarget)
, _searchLength(4)
, _hasAppeared(false)
, _direction(TiledVector::Direction::FORWARD)
{
    _target = &baseTarget;
    
    _astar = new AstarChaser(_target, *this, _pathToTarget, 20, true);

    //�����̖������o�H��ɂ������荞�܂��p������
    _astar->SetAdditionalFunc(std::move([&](TiledObject* obj){ return (obj->GetType() == _type); }));
    _ai = _astar;
    
    _graph.Load(RESOURCE_TABLE->GetFolderPath() + "graph/tiledObject/blaver.png");
    _position = startPos.GetWorldPos();
    _beforeTilePos = GetTilePos();
    _type = TiledObject::Type::ENEMY;
}


Enemy::~Enemy()
{
}


void Enemy::LoadEnemys(std::vector<TiledObject*>& objects, StartPoint* point, Goal* goal, ColleagueNotifyer& notifyer, std::string fileName)
{
    std::vector<std::string> dataArray;
    CSVReader reader;
    reader.Read(fileName, dataArray, 1);
    
    const int parameterNum = 5;
    std::array<int, parameterNum> params = {0, 0, 0, 0, 0};
    int idx = 0;
    int count = 0;
    for (auto data : dataArray)
    {
        params[count] = std::stoi(data);
        count++;
        
        if (count == parameterNum)
        {
            //�퓬�f�[�^�ݒ�
            BattleParameter param = {params[0], params[1], params[2], params[3]};
            Enemy* enemy = new Enemy(point->GetTilePos(), param, *goal, notifyer);
            objects.push_back(enemy);
            //�o�����Ԃ�b�P�ʂɕϊ����ē���҃��X�g�ɒǉ�
            point->AddToAppearList(enemy, params[4] * 60);
            
            //���̃L������
            count = 0;
            idx++;
        }
    }
}


void Enemy::SwitchAI(PathFindingAIBase* ai)
{
    //���݂Ɠ���AI��������ύX�Ȃ�
    if (_ai == ai)
        return;
    
    _ai->Reset();
    _ai = ai;
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
    if (!_hasAppeared)
        return;
    
    if (_isBattling)
        return;
    
    if (0 < _countAfetrBattle)
    {
        _countAfetrBattle++;
        
        if (_countAfetrBattle < 60)
            return;
        else
            _countAfetrBattle = 0;
    }
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
    TiledVector pos = GetTilePos();
    if (pos != _beforeTilePos)
        _beforeTilePos = pos;
    
    //�ړ���Ƃ̍�������������X�V
    auto dir = (_pathToTarget.size() == 0) ? _target->GetTilePos() - pos : _pathToTarget[0] - pos;
    if (dir == TiledVector::up)
        _direction = TiledVector::Direction::FORWARD;
    else if (dir == TiledVector::down)
        _direction = TiledVector::Direction::BACK;
    else if (dir == TiledVector::left)
        _direction = TiledVector::Direction::LEFT;
    else if (dir == TiledVector::right)
        _direction = TiledVector::Direction::RIGHT;
    
    _beforeTilePos = pos;
    
    //�ړ����������Ă�Ȃ��Ȃ�
    if (0 < _pathToTarget.size())
    {
        //�ڕW�ֈړ�
        MoveToNext();
        return;
    }
    
    //�ڕW�̏�ɂ��Ȃ���ΏI��
    if (_target->GetTile() != GetTile())
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
    OBJECT_MGR->Add(new BattlingTile(*this, *chara, GetTilePos()));
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


void Enemy::Draw()
{
    _graph.SetDisplayMode(IsEnable() && !_isBattling);
    
    auto color = ColorPalette::RED4;
//    Debug::DrawString(_position + Vector2D(32, 0), "HP");
//    Debug::DrawRectWithSize(_position + Vector2D(64, 20), Vector2D(_battleParameter._hp / double(_maxHP) * 64, 12), color, true);
//    Debug::DrawRectWithSize(_position + Vector2D(64, 20), Vector2D(64, 12), ColorPalette::BLACK4, false);
    
    if (!_hasAppeared || _isBattling)
        return;
    
    for (size_t i=0; i<_sight.size(); ++i)
    {
        Debug::DrawRectWithSize(_sight[i].GetWorldPos(), Vector2D(TILE_SIZE, TILE_SIZE),
                                Color4(1.0, 0.5, 0.5, 0.25), true);
    }
    
    //AI�̃f�o�b�O���
    _ai->Draw();
    
    GraphicalObject::Draw();
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
}


void Enemy::OnWin()
{
    Character::OnWin();
    _target = &_baseTarget;
    _astar->SetTarget(_target);
}


void Enemy::Appear()
{
    _hasAppeared = true;
}


bool Enemy::IsOverwritable(TiledObject* overwriter)
{
    if (overwriter == this)
        return true;
    
    if (overwriter->GetType() == Type::ENEMY)
        return !_hasAppeared;
    
    return true;
}


bool Enemy::IsEnable() const
{
    return _hasAppeared;
}