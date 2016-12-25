#include "BattlingTile.h"
#include "TileField.h"
#include "TiledObjectMnager.h"
#include "../Resources/ResourceManager.h"
#include "../DebugDraw.h"


BattlingTile::BattlingTile(Enemy& enemy, Monster& monster, TiledVector tilePos)
: TiledObject(tilePos)
, _enemy(enemy)
, _monster(monster)
, _count(0)
{
    _graph.Load(RESOURCE_TABLE->GetFolderPath() + "graph/tiledObject/dust1.png");
    _graph.SetPosition(tilePos.GetWorldPos());

    //�퓬�ɉ�������L�����͈ꎞ�I�Ƀo�g����Ԃ�
    _enemy.OnOccuredBattle(this);
    _monster.OnOccuredBattle(this);
    _position = tilePos.GetWorldPos();
    
    _type = Type::BATTLE;
}


BattlingTile::~BattlingTile()
{
    //�퓬���I������痼�҃o�g����Ԃ��������
    _enemy.OnFinishBattle(this);
    _monster.OnFinishBattle(this);
}

//���Ԍo�߂Ő퓬
void BattlingTile::Update()
{
    _count++;
    if (_count < 30)
        return;
    
    _monster.Interact(_enemy);
    _enemy.Interact(_monster);
    CheckAlive();

    _count = 0;
}

//�퓬���͍�����`��
void BattlingTile::Draw()
{
    GraphicalObject::Draw();
    
    //
}

//���������L�����͐퓬�}�X�ɗ���
void BattlingTile::Win(Character& chara)
{
}

//�s�k�����L�����͏�����
void BattlingTile::Lose(Character& chara)
{
}

//�퓬���痣�E
void BattlingTile::RunAway()
{
    FIELD->RemoveObject(*this);
    OBJECT_MGR->Remove(this);
}

//�퓬�㔻��
void BattlingTile::CheckAlive()
{
    //��������
    if (!_enemy.IsAlive())
    {
        Win(_monster);
        Lose(_enemy);
        FIELD->RemoveObject(*this);
        OBJECT_MGR->Remove(this);
    }
    else if (!_monster.IsAlive())
    {
        Win(_enemy);
        Lose(_monster);
        FIELD->RemoveObject(*this);
        OBJECT_MGR->Remove(this);
    }
}

//�㏑���s��
bool BattlingTile::IsOverwritable(TiledObject* overwriter)
{
    return false;
}
