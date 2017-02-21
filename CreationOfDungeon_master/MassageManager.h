#pragma once
#include <string>
#include <vector>


typedef enum {
    nomal = 0,
    dynamic = 1,
}Talk_Type;



//構造体の宣言
struct Message    //メッセージ
{

    std::string allMessage; //全てのメッセージ

    std::string hiddenMessage;  //まだ表示していないメッセージ
    std::string displayedMessage;   //表示済みのメッセージ

};

struct MessageData    //メッセージデータ
{

    Message message;    //メッセージの構造体

    int speakPeople;    //メッセージをしゃべる人
    int speakFace;  //メッセージをしゃべる人の表情

};

struct TalkData    //会話データ
{
    std::vector<MessageData> messageData;   //会話内容の集合体

    int importance;     //会話の重要度

    bool isStartMassage;    //messageData[0]が会話の最初のメッセージかどうか

};

struct TalkDatabase    //会話データの集合体
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

    static const int TalkTypeNum = 2; //会話の種類の数 nomal=0 dynamic=1
    static const int TalkGroupNum = 100; //会話の数

    std::vector<TalkDatabase> talkDatabase;

    int count;

    bool lastMessage;

    bool push;

    bool autoMessage;  //オートでメッセージが進むかどうか

public:

    MassageManager();
    MassageManager(std::string situation);
    ~MassageManager();

    void Update();
    void Draw();

    void IntoTalkStorage(std::string talkType,int talkNum);

    void IntoTalkStorage(std::string talkType, int talkNum,std::string* str,int strSize);

    //メッセージが残っているかどうか　残っていればfalse 残ってなければtrue
    bool isEmpty();

    void setAutoMessage(bool a);
    bool getAutoMessage();



};


