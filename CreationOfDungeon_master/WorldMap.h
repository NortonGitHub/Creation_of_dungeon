#pragma once
#include "SceneBase.h"
#include "cd_666s/Sound/Sound.h"
#include <vector>

//�\���̂̐錾�@���Ԃ͉���
struct Point;
struct PointConnect;


class WorldMap :
    public SceneBase
{
private:
    
    int nowMyStageNum;    //���݂���X�e�[�W�@���p�n�_�̏ꍇ��-1�A�ړ�����-2
    int nowMyPointNum;    //���݂���|�C���g�@�X�e�[�W�Ƃ͈Ⴄ�ԍ�
    bool isMyMove;    //�ړ����Ă��邩�ǂ����A�ړ�����true�A�ړ����Ă��Ȃ����false
    
    int finishPointNum; //�ړ������ꍇ�̍ŏI�ڕW�|�C���g�̔ԍ� �ړ����Ă��Ȃ����-1

    double myX; //���݂�X���W
    double myY; //���݂�Y���W
    double mySpeed; //�����̈ړ��X�s�[�h

    double myVx;    //x�����̑��x
    double myVy;    //y�����̑��x


    const double pointR = 20;   //�|�C���g�̕`�ʂ���~�̔��a�@�f�o�b�N�p�@����������


    std::vector<Point> MapPointList;   //�|�C���g�̃��X�g

    bool checkMoveReach();



    int Area1Gr;
    int blend;
    int blendFlag;

    bool isPause;
    bool keyFlag;
    bool clickFlag;

    int stageNum;

    std::string class_name;

    Sound _bgm;

public:
    WorldMap();
    ~WorldMap();


    std::string GetClassNameData() const {
        return class_name;
    }

    SceneBase* Update();
    SceneBase* Update(UIManager _ui) override;
    void Draw() override;

    void Init();    //������
    void Moving();  //�����Ă���Ƃ��̏���
    void KeyJudge();//�L�[����
    bool myPointSet(int PointNum);  //�����̃|�C���g��ݒ肷��@�}�b�v�ړ��͂��Ȃ��@���s�i�ړ�����|�C���g���ʂ̃}�b�v���j������false�A������true��Ԃ�
    int PointSearch(int pointNum);  //�|�C���g�ԍ����炻�̃|�C���g�ԍ��̈�v����|�C���g����nowMapPointList�̔z��ԍ���Ԃ��@�|�C���g�̏ꍇ���s����
    int RoadSearch(int startPointNum,int endPointNum);   //��̃|�C���g�ԍ����炻�̃|�C���g�ԍ������ԓ��̏���nowMapRoadList�̔z��ԍ���Ԃ��@�Ⴄ�}�b�v�̓��̏ꍇ���s����
    void setNowMapPointList();

    void setNowMapRoadList();
    int MoveDirection(int startPointNum, int endPointNum);

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




    bool isStayPoint;   //�~�܂��|�C���g���ǂ���



};


struct PointConnect {

    int connectPointNum;    //�q�����Ă���|�C���g�ԍ�
    int PointCost;          //���̃|�C���g�Ƃ̋���


};
