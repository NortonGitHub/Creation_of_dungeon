#include "Monster.h"
#include "TileField.h"
#include "AI/WallTracing.h"
#include "AI/AstarChaser.h"
#include "../Resources/ResourceManager.h"
#include "../DebugDraw.h"
#include "../InputManager/InputManager.h"
#include "ColleagueNotifyer.h"
#include "MagicSquare.h"
#include "BattlingTile.h"
#include "TiledObjectMnager.h"

#include <array>
#include "../Utility/CSVReader.h"

Monster::Monster(TiledVector startPos, BattleParameter param, TiledObject *target, ColleagueNotifyer& notifyer)
: Character(startPos, param, notifyer)
, _hasChoosed(false)
, _hasAppeared(false)
, _searchLength(4)
, _direction(TiledVector::Direction::FORWARD)
{
    _target = target;
    //_wallTrace = new WallTracing(*this, _pathToTarget);
    _astar = new AstarChaser(_target, *this, _pathToTarget, 100, true);
    _astar->SetAdditionalFunc(std::move([&](TiledObject* obj){ return (obj->GetType() == Type::ENEMY); }));

    _ai = _astar;
    
    _graph.Load(RESOURCE_TABLE->GetFolderPath() + "graph/tiledObject/bone.png");
    _position = startPos.GetWorldPos();
    _beforeTilePos = GetTilePos();
    
    _type = TiledObject::Type::MONSTER;
}


Monster::~Monster()
{
    delete _astar;
}


void Monster::LoadMonsters(std::vector<TiledObject*>& objects, ColleagueNotifyer& notifyer, std::string fileName)
{
    std::vector<std::string> dataArray;
    CSVReader reader;
    reader.Read(fileName, dataArray, 1);
    
    const int parameterNum = 6;
    std::array<int, parameterNum> params = { 0, 0, 0, 0, 0, 0 };
    int idx = 0;
    int count = 0;
    for (auto data : dataArray)
    {
        params[count] = std::stoi(data);
        count++;
        
        if (count == parameterNum)
        {
            BattleParameter param = { params[0], params[1], params[2], params[3] };
            TiledVector startPos(params[4], params[5]);
            
            Monster* monster = new Monster(startPos, param, nullptr, notifyer);
            objects.push_back(monster);
            
            auto magicSquare = new MagicSquare(startPos, *monster);
            monster->_home = magicSquare;
            objects.push_back(magicSquare);
            
            //���̃L������
            count = 0;
            idx++;
        }
    }
}


void Monster::SwitchAI(PathFindingAIBase* ai)
{
    //���݂Ɠ���AI��������ύX�Ȃ�
    if (_ai == ai)
        return;
    
    _ai->Reset();
    _ai = ai;
}


void Monster::Think()
{
    _ai->Update();
}


void Monster::Update()
{
    //���@�w�̏�ɂ���Ȃ炳��ɉ�
    auto objs = FIELD->GetTiledObjects(GetTilePos());
    for (auto obj : objs)
    {
        if (obj->GetType() == TiledObject::Type::MAGIC_SQUARE
            && _home == obj)
        {
            obj->Interact(*this);
            break;
        }
    }
    
    if (0 < _countAfetrBattle)
    {
        _countAfetrBattle++;
        
        if (60 < _countAfetrBattle)
            _countAfetrBattle = 0;
    }
    
    if (!_hasAppeared)
        return;
    
    if (_isBattling)
        return;
    
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
    TiledVector pos = GetTilePos();
    
    //�ړ���Ƃ̍�������������X�V
    TiledVector dir;
    if (_target != nullptr)
        _target->GetTilePos() - pos;
    else if (0 < _pathToTarget.size())
        _pathToTarget[0] - pos;
    
    if (dir == TiledVector::up)
        _direction = TiledVector::Direction::FORWARD;
    else if (dir == TiledVector::down)
        _direction = TiledVector::Direction::BACK;
    else if (dir == TiledVector::left)
        _direction = TiledVector::Direction::LEFT;
    else if (dir == TiledVector::right)
        _direction = TiledVector::Direction::RIGHT;
    
    _beforeTilePos = pos;
    
    if (_target == nullptr)
    {
        if (_pathToTarget.size() != 0)
            MoveToNext();
        
        return;
    }
    
    MoveToNext();
}


void Monster::MoveToNext()
{
    if (_pathToTarget.size() == 0)
        return;

    if (_countAfetrBattle == 0)
    {
        auto objects = FIELD->GetTiledObjects(GetTilePos());

        //�G�����ʂ��痈��Ȃ�҂��\����
        for (auto obj : objects)
        {
            if (obj->GetType() == Type::ENEMY)
                return;
        }
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


void Monster::Draw()
{
    /*
    auto color = ColorPalette::BLUE4;
    if (!_hasAppeared)
        color._a = 0.25;

    Debug::DrawString(_position + Vector2D(32, 0), "HP");
    Debug::DrawRectWithSize(_position + Vector2D(64, 0), Vector2D(_battleParameter._hp / double(_maxHP) * 64, 12), color, true);
    Debug::DrawRectWithSize(_position + Vector2D(64, 0), Vector2D(64, 12), ColorPalette::BLACK4, false);
    */

    _graph.SetDisplayMode(_hasAppeared && !_isBattling);
    
    if (!_hasAppeared || _isBattling)
        return;
    
    //AI�̃f�o�b�O���
    if (_ai != nullptr)
        _ai->Draw();
    
    GraphicalObject::Draw();
}


void Monster::Appear()
{
    _hasAppeared = true;
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
    
    //�o�g�����Ȃ�o�g���I��
    if (_isBattling)
    {
        _battle->RunAway();
        ResetCounter();
    }
}


void Monster::ExitBattle()
{
    auto tilePos = GetTilePos();
    
    if (FIELD->IsMovableThere(tilePos + TiledVector(0, 1), *this))
    {
        tilePos += TiledVector(0, 1);
    }
    else if (FIELD->IsMovableThere(tilePos + TiledVector(0, -1), *this))
    {
        tilePos += TiledVector(0, -1);
    }
    else if (FIELD->IsMovableThere(tilePos + TiledVector(1, 0), *this))
    {
        tilePos += TiledVector(1, 0);
    }
    else if (FIELD->IsMovableThere(tilePos + TiledVector(-1, 0), *this))
    {
        tilePos += TiledVector(-1, 0);
    }
    
    FIELD->MoveObject(*this, tilePos);
    _position = tilePos.GetWorldPos();
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
    ResetCounter();
    ResetTarget();
    _pathToTarget.resize(0);
    _hasChoosed = false;
    _hasAppeared = false;
}


void Monster::OnWin()
{
    Character::OnWin();
    ResetTarget();
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


bool Monster::IsEnable() const
{
    return _hasAppeared;
}

//�����\���ǂ���
bool Monster::IsReadyToProduce() const
{
    //�̗͂��ő� & ��������ĂȂ��Ȃ珢���\
    return (_maxHP == _battleParameter._hp)
            && (!_hasAppeared);
}

bool Monster::IsOverwritable(TiledObject* overwriter)
{
    if (overwriter == this)
        return true;
        
    if (overwriter->GetType() == Type::MONSTER)
        return false;
    
    return true;
}