#pragma once
#include "cd_666s/TilebaseAI/GraphicalObject.h"
#include "mw_animation/Animator.h"

class Character;

class BossBattleObject :
	public GraphicalObject
{
public:
	BossBattleObject();
	BossBattleObject(Vector2D pos, std::string name);
	~BossBattleObject();

	enum class Type
	{
		DEFAULT,
		BOSS,
		ENEMY,
		FACE
	};

	//���[�v�����̑O��1�x�����Ă΂�鏈��
	virtual void Init();

	virtual void Update() override;
	virtual void Draw() override;

	//�\������ł���I�u�W�F�N�g����Ăяo�����֐�
	virtual void Interact(Character& character);

	//�A�C�e���擾�ł̏����⏢�����ꂽ���ǂ����ȂǁA
	//�I�u�W�F�N�g�͐������Ă�����ɗp���邩�ǂ����𔻒f����̂ɗp����.
	//�ڍׂȏ����͔h����ɂ���ĈقȂ�.
	virtual bool IsEnable() const { return true; }

	//�I�u�W�F�N�g���|���ꂽ���Ƃ������Ƃ��Ɏg�p
	virtual int GetDefeatedNum() const { return 0; }

	//�I�u�W�F�N�g���ړI�n�ɂ��ǂ蒅�������ǂ�����Ԃ�
	virtual bool HasArrived() const { return true; }

	Type GetType() const { return _type; }

protected:

	std::string _name;
	Type _type;

	//�������{�X�����̒��ɂ��邩
	bool _isInRoom;

	Animator _animator;

private:
	Vector2D _position;
};

