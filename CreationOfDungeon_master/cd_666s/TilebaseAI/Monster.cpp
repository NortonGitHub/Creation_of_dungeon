#include "Monster.h"
#include "TileField.h"
#include "AI/AstarChaser.h"
#include "../Resources/AllResourceManager.h"
#include "../DebugDraw.h"
#include "ColleagueNotifyer.h"
#include "MagicSquare.h"
#include "BattlingTile.h"
#include "TiledObjectMnager.h"

#include <array>
#include "../Utility/CSVReader.h"

Monster::Monster(TiledVector startPos, BattleParameter param, TiledObject *target, ColleagueNotifyer& notifyer, std::string monsterName)
: Character(startPos, param, notifyer)
, _hasChoosed(false)
, _hasAppeared(false)
, _defeatSE("resourse/sound/enemy_fall2.wav")
, _appearSE("resourse/sound/flame.wav")
{
    _name = monsterName;
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
    std::string fileName = "resourse/graph/tiledObject/";
    fileName += _name;
    _currentGraphPtr = _front.SetWithCreate(fileName + "_front.png", 32, 32, 2, 24);
    _right.SetWithCreate(fileName + "_right.png", 32, 32, 2, 24);
    _left.SetWithCreate(fileName + "_left.png", 32, 32, 2, 24);
    _back.SetWithCreate(fileName + "_back.png", 32, 32, 2, 24);

    _currentGraphPtr->SetRenderType(Texture2D::RenderType::UI);
    _right.GetGraphPtr()->SetDisplayMode(false);
    _left.GetGraphPtr()->SetDisplayMode(false);
    _front.GetGraphPtr()->SetDisplayMode(false);
    _back.GetGraphPtr()->SetDisplayMode(false);

    _position = startPos.GetWorldPos();
    _beforeTilePos = GetTilePos();
    
    _type = TiledObject::Type::MONSTER;
    _appearSE.SetVolume(200);
}


Monster::~Monster()
{
}


void Monster::LoadMonsters(std::vector<std::shared_ptr<TiledObject>>& objects, ColleagueNotifyer& notifyer, std::string fileName)
{
    std::vector<std::string> dataArray;
    CSVReader reader;
    reader.Read(RESOURCE_TABLE->GetFolderPath() + fileName, dataArray, 1);
    
    const int parameterNum = 7;
    std::array<int, parameterNum> params = { 0, 0, 0, 0, 0, 0, 0 };
    int idx = 0;
    int count = 0;
    for (auto data : dataArray)
    {
        // MEMO : �Ōゾ���̓t�@�C���������̂܂܎g��
        if (count < parameterNum - 1)
            params[count] = std::stoi(data);

        count++;
        
        if (count == parameterNum)
        {
            BattleParameter param = { params[0], params[1], params[2], params[3] };
            TiledVector startPos(params[4], params[5]);
            
            auto str = data.substr(1, data.size());
            auto monster = std::make_shared<Monster>(startPos, param, nullptr, notifyer, str);
            objects.push_back(monster);
            
            auto magicSquare = std::make_shared<MagicSquare>(startPos, *monster);
            monster->_home = magicSquare.get();
            objects.push_back(magicSquare);
            
            //���̃L������
            count = 0;
            idx++;
        }
    }
}


void Monster::Init()
{
}


void Monster::Think()
{
    if (_target != nullptr)
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
    //�ړ���Ƃ̍�������������X�V
    UpdateAttitude();
   
    //���̃^�C���ֈړ�
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
    _currentGraphPtr->SetDisplayMode(false);
    GraphArray* currentAnimation = nullptr;

    if (!_hasAppeared || _isBattling)
        return;
    
    switch (_direction)
    {
    case TiledVector::Direction::FORWARD:
        //        _animator.SwitchWithReset("forward");
        _currentGraphPtr = _front.GetGraphPtr();
        currentAnimation = &_front;
        break;

    case TiledVector::Direction::LEFT:
        //        _animator.SwitchWithReset("left");
        _currentGraphPtr = _left.GetGraphPtr();
        currentAnimation = &_left;
        break;

    case TiledVector::Direction::RIGHT:
        //        _animator.SwitchWithReset("right");
        _currentGraphPtr = _right.GetGraphPtr();
        currentAnimation = &_right;
        break;

    case TiledVector::Direction::BACK:
        //        _animator.SwitchWithReset("back");
        _currentGraphPtr = _back.GetGraphPtr();
        currentAnimation = &_back;
        break;
    }

    if (_position != GetTilePos().GetWorldPos())
        currentAnimation->Update();

    _currentGraphPtr->SetDisplayMode(true);

    //AI�̃f�o�b�O���
    if (_ai != nullptr)
        _ai->Draw();

    _currentGraphPtr->SetScale(Vector2D(TILE_SIZE / 32.0, TILE_SIZE / 32.0));
    _currentGraphPtr->SetPosition(_position);
}


void Monster::Appear()
{
    _hasAppeared = true;
    _appearSE.Play();
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

    _defeatSE.Play();
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

    if (overwriter->GetType() == Type::ENEMY)
        return !_isBattling;

    if (overwriter->GetType() == Type::MONSTER)
        return false;
    
    return true;
}