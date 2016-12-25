#include "Character.h"
#include "TiledObjectMnager.h"
#include "ColleagueNotifyer.h"
#include "TileField.h"
#include "BattlingTile.h"
#include "../DebugDraw.h"

Character::Character(TiledVector startPos, const BattleParameter param, ColleagueNotifyer& notifyer)
: TiledObject(startPos)
, _actCounter(0)
, _actInterval(30)
, _battleParameter(param)
, _notifyer(notifyer)
, _maxHP(1)
, _countAfetrBattle(0)
, _isBattling(false)
, _target(nullptr)
{
    _notifyer.AddColleague(*this);
    _maxHP = _battleParameter._hp;
    
    _battleParameter._speed = fmin(100, fmax(_battleParameter._speed, 0));
    double speedRatio = static_cast<double>(100 - _battleParameter._speed + 15) / 100;
    _actInterval *= speedRatio;
}


Character::~Character()
{
    _notifyer.RemoveColleague(*this);
}


void Character::Update()
{
    GraphicalObject::Update();
}


void Character::Draw()
{
}


void Character::OnOccuredBattle(BattlingTile* battle)
{
    _beforeTilePos = GetTilePos();
    _position = GetTilePos().GetWorldPos();
    _battle = battle;
    _isBattling = true;
    _pathToTarget.clear();
    _pathToTarget.resize(0);
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


bool Character::CheckActCounter()
{
    if (_actCounter <  _actInterval)
    {
        _actCounter++;
        return false;
    }
    
    _actCounter = 0;
    return true;
}


void Character::Interact(Character& chara)
{
    //�G���ׂɂ���ΐ퓬
    chara.Attack(*this);
    
    OnAttacked(chara);
    
    //�퓬�œ|���ꂽ�����m�F����
    if (!IsAlive())
    {
        OnDie();
        
        //��񋤗L�Ԃ�������O
        chara._notifyer.NotifyRemoveTarget(*this);
        chara.ResetTarget();
        chara.OnWin();
    }
}


void Character::Attack(Character &defender)
{
    BattleParameter& defenderParameter = defender._battleParameter;
    
    //�_���[�W�̌v�Z�� : ������̍U���� - ����̖h���
    int damage = _battleParameter._attack - defenderParameter._defence;
    //�_���[�W��0�ȏ�
    damage = fmax(damage, 0);
    
    defenderParameter._hp -= damage;
}


void Character::OnAttacked(Character& attacker)
{
    //����͍U�����ɋC�Â�
    _target = &attacker;
}


void Character::OnDie()
{    
    //�t�B�[���h���珜�O
    OBJECT_MGR->Remove(this);
}


void Character::OnWin()
{
}


bool Character::IsAlive()
{
    return (0 < _battleParameter._hp);
}