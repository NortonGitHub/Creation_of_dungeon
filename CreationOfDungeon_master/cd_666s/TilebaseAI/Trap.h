#pragma once
#include "TiledObject.h"

class Trap : public TiledObject
{
public:
    Trap(TiledVector startPos, int duravity, int level);
    ~Trap();

    virtual void Update() override;

    bool IsBrakeable(int brokerLevel) const { return _level <= brokerLevel; };

    //�\������ł���I�u�W�F�N�g����Ăяo�����֐�
    virtual void Interact(Character& character) override {};

    //���̃I�u�W�F�N�g�̏�ɕʂ̃I�u�W�F�N�g�����邩�ǂ���
    //overwriter : ��ɏ�낤�Ƃ���I�u�W�F�N�g
    virtual bool IsOverwritable(TiledObject* overwriter) override { return true; };

    //�A�C�e���擾�ł̏����⏢�����ꂽ���ǂ����ȂǁA
    //�I�u�W�F�N�g�͐������Ă�����ɗp���邩�ǂ����𔻒f����̂ɗp����.
    virtual bool IsEnable() const { return true; }

protected:

    //�ϋv��
    int _duravity;

    //�������ɏ��Ղ����
    int _cost;

    //�j��\���������l
    int _level;
};

