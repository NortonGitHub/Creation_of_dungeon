#pragma once
#include <string>
#include <vector>


//�\���̂̐錾
struct Message    //���b�Z�[�W
{

    std::string allMessage; //�S�Ẵ��b�Z�[�W

    std::string hiddenMessage;  //�܂��\�����Ă��Ȃ����b�Z�[�W
    std::string displayedMessage;   //�\���ς݂̃��b�Z�[�W

};

struct MessageData    //���b�Z�[�W�f�[�^
{

    Message message;    //���b�Z�[�W�̍\����

    int speakPeople;    //���b�Z�[�W������ׂ�l
    int speakFace;  //���b�Z�[�W������ׂ�l�̕\��

};

struct TalkData    //��b�f�[�^
{
    std::vector<MessageData> messageData;   //��b���e�̏W����

    int importance;     //��b�̏d�v�x

    bool isStartMassage;    //messageData[0]����b�̍ŏ��̃��b�Z�[�W���ǂ���

};



class MassageManager {

private:

    std::vector<TalkData> TalkStorage;

    static const int waitFrame = 5;
    static const int lastWaitFrame = 100;

    static const int TalkTypeNum = 1; //��b�̎�ނ̐� nomal=0
    static const int TalkGroupNum = 100; //��b�̐�

    TalkData talkDatabase[TalkTypeNum][TalkGroupNum];

    int count;

    bool lastMessage;

    bool push;

    bool autoMessage;  //�I�[�g�Ń��b�Z�[�W���i�ނ��ǂ���

public:

    MassageManager();
    ~MassageManager();

    void Update();
    void Draw();

    void IntoTalkStorage(std::string talkType,int talkNum);

    //���b�Z�[�W���c���Ă��邩�ǂ����@�c���Ă����false �c���ĂȂ����true
    bool isEmpty();

    void setAutoMessage(bool a);
    bool getAutoMessage();

};


