#ifndef GRAPH_ARRAY_H
#define GRAPH_ARRAY_H

#include "../cd_666s/Render/Sprite.h"
#include <vector>

/*
�摜�����̊��o�ŋ�؂�
�z��ŊǗ����� DxLib�pSprite�N���X�̊g�����W���[��
*/

class GraphArray
{
    friend class Animator;
    typedef int Handle;
    typedef std::pair<Vector2D, Vector2D> PixelInset;

public:
    GraphArray();

    GraphArray(Sprite *arg_graph
        , const int divNumH, const int divNumV
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    GraphArray(Sprite *arg_graph
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    GraphArray(std::string name
        , const int divNumH, const int divNumV
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    GraphArray(std::string name
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    GraphArray(std::string name);

    ~GraphArray();

    void Set(Sprite *arg_graph
        , const int divNumH, const int divNumV
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    void Set(Sprite *arg_graph, const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    //�摜�𐶐����āA��������A�j���[�V����������
    Sprite* SetWithCreate(std::string name
        , const int divNumH, const int divNumV
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    //�摜�𐶐����āA��������A�j���[�V����������
    Sprite* SetWithCreate(std::string name
        , const int sizeH, const int sizeV
        , const int allDivNum, const int endTime);

    //�摜�𐶐����āA��������A�j���[�V����������
    Sprite* SetWithCreate(std::string name);


    void SetIndex(int index)
    {
        _index = index;
        _currentTime = index * (_endTime / _handleArray.size());
        _graphPtr->GetTexturePtr()->_handle = _handleArray[_index];
    }
    void SetSpeed(int speed) { _speed = speed; }

    void SetCurrentTime(int time)
    {
        if (time < 0 || _endTime < time)
            return;

        _currentTime = time;
    }

    Vector2D GetSingleSize() const { return _singleSize; }

    Sprite* GetGraphPtr() { return _graphPtr; }

    //���[�v���~�߁A�w�肳�ꂽ�C���f�N�X�̉摜��\������
    void DeterminHandle(int index);

    //�A�j���[�V���������[�v������Ƃ��͂�����Ă�
    void Update();

    bool HasEndedUp() const { return (_hasEnd); }

    //�����L��/�����ɂ����Update������/�����Ȃ��Ȃ�
    bool _isLoop;

private:

    void CreateArray(const int divNumH, const int divNumV
        , const int sizeH, const int sizeV, const int allDivNum);


    //�摜�𕪊����ĕێ�����
    std::vector<Handle> _handleArray;

    //1��������̉摜�T�C�Y
    Vector2D _singleSize;

    //��ʂɕ\������摜�{��
    Sprite *_graphPtr;


    //���̃N���X���ŉ摜���������ꂽ���ǂ���
    bool _isCreatedInside;

    //���[�v�I���̎���(�t���[���w��)
    int _endTime;

    //���݂̎���(�t���[���w��)
    int _currentTime;

    //���Ԃ�������{��(�ʏ��1)
    int _speed;

    //���ݕ\������C���f�N�X
    int _index;

    bool _hasEnd;
};

#endif