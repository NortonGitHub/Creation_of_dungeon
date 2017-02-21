#pragma once
#include <string>
#include <vector>


typedef enum {
    nomal = 0,
    dynamic = 1,
}Talk_Type;



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

struct TalkDatabase    //��b�f�[�^�̏W����
{
    
    TalkData talkData;

    int TalkGroupNum;

    Talk_Type TalkType;

};



class MassageManager {

private:

    std::vector<TalkData> TalkStorage;

    static const int waitFrame = 5;
    static const int lastWaitFrame = 100;

    static const int TalkTypeNum = 2; //��b�̎�ނ̐� nomal=0 dynamic=1
    static const int TalkGroupNum = 100; //��b�̐�

    std::vector<TalkDatabase> talkDatabase;

    int count;

    bool lastMessage;

    bool push;

    bool autoMessage;  //�I�[�g�Ń��b�Z�[�W���i�ނ��ǂ���

public:

    MassageManager();
    MassageManager(std::string situation);
    ~MassageManager();

    void Update();
    void Draw();

    void IntoTalkStorage(std::string talkType,int talkNum);

    void IntoTalkStorage(std::string talkType, int talkNum,std::string* str,int strSize);

    //���b�Z�[�W���c���Ă��邩�ǂ����@�c���Ă����false �c���ĂȂ����true
    bool isEmpty();

    void setAutoMessage(bool a);
    bool getAutoMessage();



};


