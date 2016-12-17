#pragma once
#include "SceneBase.h"
#include <vector>

//�\���̂̐錾�@���Ԃ͉���
struct Point;
struct Road;
struct RoadTurnPoint;



class Map :
    public SceneBase
{
private:

    int nowMyMapNum;  //���݂���}�b�v�̔ԍ�
    int nowMyStageNum;    //���݂���X�e�[�W�@���p�n�_�̏ꍇ��-1�A�ړ�����-2
    int nowMyPointNum;    //���݂���|�C���g�@�X�e�[�W�Ƃ͈Ⴄ�ԍ�
    bool isMyMove;    //�ړ����Ă��邩�ǂ����A�ړ�����true�A�ړ����Ă��Ȃ����false
    
    
    std::vector<RoadTurnPoint> targetTurnPointList;   //�ړ�����ꍇ�Ɉړ���܂ł̓��̂����A�Ȃ�����W�����ԂɎw�肵�A�����Ƀv�b�V������
    int finishPointNum; //�ړ������ꍇ�̍ŏI�ڕW�|�C���g�̔ԍ� �ړ����Ă��Ȃ����-1

    double myX; //���݂�X���W
    double myY; //���݂�Y���W
    double mySpeed; //�����̈ړ��X�s�[�h

    double myVx;    //x�����̑��x
    double myVy;    //y�����̑��x

    int myMoveDirection;    //�ړ�����Ƃ��̕�����\���@������nowMapRoadList��startPoint��endPoint�Ȃ�1�AendPoint��startPoint�Ȃ�2�A�ړ����Ă��Ȃ��ꍇ��-1�Astart

    const double pointR = 20;   //�|�C���g�̕`�ʂ���~�̔��a�@�f�o�b�N�p�@����������


    std::vector<Point> nowMapPointList;   //���݂���}�b�v�̃|�C���g�̃��X�g
    std::vector<Road> nowMapRoadList;   //���݂���}�b�v�̓��̃��X�g

    bool checkMoveReach();

public:
    Map();
    ~Map();

    SceneBase* Update();
    void Draw();

    void Init();    //������
    void Moving();  //�����Ă���Ƃ��̏���
    void KeyJudge();//�L�[����
    void setNowMapPointList();
    void setNowMapRoadList();
    bool myPointSet(int PointNum);  //�����̃|�C���g��ݒ肷��@�}�b�v�ړ��͂��Ȃ��@���s�i�ړ�����|�C���g���ʂ̃}�b�v���j������false�A������true��Ԃ�
    int PointSearch(int pointNum);  //�|�C���g�ԍ����炻�̃|�C���g�ԍ��̈�v����|�C���g����nowMapPointList�̔z��ԍ���Ԃ��@�Ⴄ�}�b�v�̃|�C���g�̏ꍇ���s����
    int RoadSearch(int startPointNum,int endPointNum);   //��̃|�C���g�ԍ����炻�̃|�C���g�ԍ������ԓ��̏���nowMapRoadList�̔z��ԍ���Ԃ��@�Ⴄ�}�b�v�̓��̏ꍇ���s����
    
    
    int MoveDirection(int startPointNum, int endPointNum); //��̃|�C���g�ԍ����炻�̃|�C���g�ԍ��̂����AnowMapRoadList��start����end�ւ̕�����Ԃ��@�֐��̈����ł���startPointNum��endPointNum�̕����Ɉړ�����ہAnowMapRoadList��startPoint��endPoint�Ȃ�1�AendPoint��startPoint�Ȃ�2��Ԃ��@�Ⴄ�}�b�v�̓��̏ꍇ���s����
};




//�g���\���̂��ȉ���
struct Point    //�|�C���g�̏���\���@�|�C���g�͈ړ����A�~�܂邱�Ƃ��o����ꏊ
{

    int mapNum;     //�|�C���g������}�b�v�̔ԍ�
    int pointNum;   //�|�C���g�ԍ��@�X�e�[�W�Ƃ͈Ⴂ���p�n�_�ɂ�����U����ԍ�
    int stageNum;   //�X�e�[�W�ԍ��@���p�n�_�̏ꍇ��-1
    
    int mapMove_mapNum;    //�}�b�v���ړ�����|�C���g�̏ꍇ�A�ړ���̃}�b�v�ԍ�������B�}�b�v���ړ����Ȃ��ꍇ-1
    int mapMove_pointNum;    //�}�b�v���ړ�����|�C���g�̏ꍇ�A�ړ���̃|�C���g�ԍ�������B�}�b�v���ړ����Ȃ��ꍇ-1
    int mapMove_movePointNum;   //�}�b�v���ړ�����|�C���g�̏ꍇ�A�}�b�v�ړ���A�����Ɉړ�����|�C���g�ԍ�������B�}�b�v���ړ����Ȃ��ꍇ-1

    double x;   //�|�C���g��X�ʒu
    double y;   //�|�C���g��Y�ʒu

    int upMovePoint; //��L�[���������ꍇ�Ɉړ�����|�C���g�̔ԍ��@�ǂ��ɂ��q�����Ă��Ȃ����-1
    int downMovePoint; //��L�[���������ꍇ�Ɉړ�����|�C���g�̔ԍ��@�ǂ��ɂ��q�����Ă��Ȃ����-1
    int leftMovePoint; //��L�[���������ꍇ�Ɉړ�����|�C���g�̔ԍ��@�ǂ��ɂ��q�����Ă��Ȃ����-1
    int rightMovePoint; //��L�[���������ꍇ�Ɉړ�����|�C���g�̔ԍ��@�ǂ��ɂ��q�����Ă��Ȃ����-1



};

struct Road    //���̏���\���@���͈ړ����邱�Ƃ��o���铹�@���̏��͈͂�̓��ɂ����ނ���i�P�ԁ��Q�ԂƂP�ԁ��Q�Ԃ͈ꏏ�j �S�������ꏊ����n�܂�A�S�������ꏊ�ŏI��铹�͑��݂��Ȃ��Ɖ��肷��
{
    int mapNum; //��������}�b�v�̔ԍ��@�����̓|�C���g��񂩂玩����������悤�ɂ�����

    int roadNum;   //���[�h�ԍ��@���ԍ�

    int startPointNum;  //�q�����Ă���|�C���g�ԍ��̂����̕Е��@����̏��́A����startPointNum�̃|�C���g���珇�ԂɋȂ���ꏊ�̏����i�[����
    int endPointNum;  //�q�����Ă���|�C���g�ԍ��̂����̕Е��@����̏��́A����endPointNum�̃|�C���g����t�̏��ԂɋȂ���ꏊ�̏����i�[����

    std::vector<RoadTurnPoint> roadTurnPoint;   //���̋Ȃ���ꏊ�̍��W�@startPointNum���珇�ԂɋȂ���ꏊ���i�[

};


struct RoadTurnPoint  //���̋Ȃ���ꏊ�̍��W�̏���\��
{
    double x;   //�Ȃ���ꏊ��X���W
    double y;   //�Ȃ���ꏊ��Y���W
};