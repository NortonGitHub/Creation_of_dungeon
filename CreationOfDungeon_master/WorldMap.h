#pragma once
#include "SceneBase.h"
#include <vector>

//�\���̂̐錾�@���Ԃ͉���
struct Point;
struct PointConnect;
struct RoadConnect;


class WorldMap :
    public SceneBase
{
private:
    
    int nowMyStageNum;    //���݂���X�e�[�W�@���p�n�_�̏ꍇ��-1�A�ړ�����-2
    int nowMyPointNum;    //���݂���|�C���g�@�X�e�[�W�Ƃ͈Ⴄ�ԍ��@���S�Ƀ|�C���g�ʂ̔ԍ�
    int nowMyAreaNum;      //���݂���G���A

    bool isMyMove;    //�ړ����Ă��邩�ǂ����A�ړ�����true�A�ړ����Ă��Ȃ����false
    
    int finishPointNum; //�ړ������ꍇ�̍ŏI�ڕW�|�C���g�̔ԍ� �ړ����Ă��Ȃ����-1

    double myX; //���݂�X���W
    double myY; //���݂�Y���W
    double mySpeed; //�����̈ړ��X�s�[�h

    double myVx;    //x�����̑��x
    double myVy;    //y�����̑��x


    const double pointR = 9;   //�|�C���g�̕`�ʂ���~�̔��a�@�f�o�b�N�p�@����������


    std::vector<Point> nowAreaPointList;   //���݂̃G���A�̃|�C���g�̃��X�g
    std::vector<RoadConnect> nowRoadConnect;   //���݂̃G���A�̓��̌q����̏��

    bool checkMoveReach();



    int Area1Gr;
    int blend;
    int blendFlag;

    bool isPause;
    bool keyFlag;
    bool clickFlag;

    int stageNum;

public:
    WorldMap();
    ~WorldMap();

    SceneBase* Update();
    void Draw();

    void Init();    //������

    bool myPointSet(int PointNum);  //�����̃|�C���g��ݒ肷��@�}�b�v�ړ��͂��Ȃ��@���s�i�ړ�����|�C���g���ʂ̃}�b�v���j������false�A������true��Ԃ�
    int PointSearch(int pointNum);  //�|�C���g�ԍ����炻�̃|�C���g�ԍ��̈�v����|�C���g����nowMapPointList�̔z��ԍ���Ԃ��@�|�C���g�̏ꍇ���s����

    void setNowAreaPointList();
    void setNowRoadConnect();

    void DrawMap();

    int ClickCheckBox(int x, int y, int rx, int ry);    //�N���b�N�����Ƃ��̔���i�l�p�`�j
    int ClickCheckCircle(int x, int y, int r);    //�N���b�N�����Ƃ��̔���i�~�`�j

};




//�g���\���̂��ȉ���
struct Point    //�|�C���g�̏���\���@�|�C���g�͈ړ����A�~�܂邱�Ƃ��o����ꏊ
{

    int AreaNum;

    int pointNum;   //�|�C���g�ԍ��@�X�e�[�W�Ƃ͈Ⴂ���p�n�_�ɂ�����U����ԍ�
    int stageNum;   //�X�e�[�W�ԍ��@���p�n�_�̏ꍇ��-1
    

    double x;   //�|�C���g��X�ʒu
    double y;   //�|�C���g��Y�ʒu

    int hitType;    //�����蔻��̃^�C�v


    int isStayPoint;   //�~�܂��|�C���g���ǂ���   0�Ŏ~�܂�Ȃ� 1�Ŏ~�܂��

    int isPoint;        //�|�C���g���L�����ǂ����i�N���A���ł��̃|�C���g���o����悤�ɂȂ��Ă��邩�j0�Ŗ����@1�ŗL��

    std::vector<PointConnect> pointConect;


};


struct PointConnect {

    int connectPointNum;    //�q�����Ă���|�C���g�ԍ�
    int PointCost;          //���̃|�C���g�Ƃ̋���


};

struct RoadConnect {

    int road[2];    //�q�����Ă���|�C���g���


};


