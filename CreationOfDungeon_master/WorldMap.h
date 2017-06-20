#pragma once
#include "SceneBase.h"
#include "cd_666s/Sound/Sound.h"
#include <vector>

//�\���̂̐錾�@���Ԃ͉���
struct Point;
struct PointConnect;
struct RoadConnect;
struct SearchPointConnect;



class WorldMap :
    public SceneBase
{
private:
    
    //int nowMyStageNum;    //���݂���X�e�[�W�@���p�n�_�̏ꍇ��-1�A�ړ�����-2
    int nowMyPointNum;    //���݂���|�C���g�@�X�e�[�W�Ƃ͈Ⴄ�ԍ��@���S�Ƀ|�C���g�ʂ̔ԍ�
    int nowMyAreaNum;      //���݂���G���A

    //bool isMyMove;    //�ړ����Ă��邩�ǂ����A�ړ�����true�A�ړ����Ă��Ȃ����false

    //int finishPointNum; //�ړ������ꍇ�̍ŏI�ڕW�|�C���g�̔ԍ� �ړ����Ă��Ȃ����-1

    double myX; //���݂�X���W
    double myY; //���݂�Y���W
    double mySpeed; //�����̈ړ��X�s�[�h

    double myVx;    //x�����̑��x
    double myVy;    //y�����̑��x


    const double pointR = 9;   //�|�C���g�̕`�ʂ���~�̔��a�@�f�o�b�N�p�@����������


    std::vector<Point*> nowAreaPointList;   //���݂̃G���A�̃|�C���g�̃��X�g
    std::vector<RoadConnect*> nowRoadConnect;   //���݂̃G���A�̓��̌q����̏��

    std::vector<int> movePointList;

    int Area1Gr;

    int charaGr_f[4];
    int charaGr_b[4];
    int charaGr_l[4];
    int charaGr_r[4];

    int charaAnimeCnt;
    int charaAnimeFrameTime;

    int blend;
    int blendFlag;

    bool isPause;
    bool keyFlag;
    bool clickFlag;

    int stageNum;

    std::string class_name;

    Sound _bgm;

    bool debugFlag;

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

    bool myPointSet(int PointNum);  //�����̃|�C���g��ݒ肷��@�}�b�v�ړ��͂��Ȃ��@���s�i�ړ�����|�C���g���ʂ̃}�b�v���j������false�A������true��Ԃ�
    int PointSearch(int pointNum);  //�|�C���g�ԍ����炻�̃|�C���g�ԍ��̈�v����|�C���g����nowMapPointList�̔z��ԍ���Ԃ��@�|�C���g�̏ꍇ���s����

    void setNowAreaPointList();
    void setNowRoadConnect();

    void setPointCost();

    Point* getPoint(int pointNum);

    void DrawMap();

    int ClickCheckBox(int x, int y, int rx, int ry);    //�N���b�N�����Ƃ��̔���i�l�p�`�j
    int ClickCheckCircle(int x, int y, int r);    //�N���b�N�����Ƃ��̔���i�~�`�j

    bool checkMoveReach(Point* point);

    void movePoint();

    void searchPath(int pointNum);

    void setSearchPointConnect(int pointNum, std::vector<SearchPointConnect*>* spc);

    void setMovePath(int pointNum, std::vector<SearchPointConnect*>* spc);

};




//�g���\���̂��ȉ���
struct Point    //�|�C���g�̏���\���@�|�C���g�͈ړ����邱�Ƃ��o����ꏊ
{

    int AreaNum;

    int pointNum;   //�|�C���g�ԍ��@�X�e�[�W�Ƃ͈Ⴂ���p�n�_�ɂ�����U����ԍ�
    int stageNum;   //�X�e�[�W�ԍ��@���p�n�_�̏ꍇ��-1


    double x;   //�|�C���g��X�ʒu
    double y;   //�|�C���g��Y�ʒu

    int hitType;    //�����蔻��̃^�C�v


    int isStayPoint;   //�~�܂��|�C���g���ǂ���   0�Ŏ~�܂�Ȃ� 1�Ŏ~�܂��

    int isPoint;        //�|�C���g���L�����ǂ����i�N���A���ł��̃|�C���g���o����悤�ɂȂ��Ă��邩�j0�Ŗ����@1�ŗL��

    std::vector<PointConnect*> pointConect;


};


struct PointConnect {

    int connectPointNum;    //�q�����Ă���|�C���g�ԍ�
    double PointCost;          //���̃|�C���g�Ƃ̋���


};

struct RoadConnect {

    int road[2];    //�q�����Ă���|�C���g���


};



struct SearchPointConnect {

    int pointNum;           //�|�C���g�ԍ�
    int connectPointNum;    //���̔ԍ��֍s���ŒZ�o�H�̔ԍ�

    bool isSearch;

    double PointCost;          //���̃|�C���g�ɍs���܂ł̃R�X�g


};




