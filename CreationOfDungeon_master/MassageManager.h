#pragma once
#include <string>
#include <vector>


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



class MassageManager {

private:

    std::vector<TalkData> TalkStorage;

    static const int waitFrame = 5;
    static const int lastWaitFrame = 100;

    static const int TalkTypeNum = 1; //会話の種類の数 nomal=0
    static const int TalkGroupNum = 100; //会話の数

    TalkData talkDatabase[TalkTypeNum][TalkGroupNum];

    int count;

    bool lastMessage;

    bool push;

    bool autoMessage;  //オートでメッセージが進むかどうか

public:

    MassageManager();
    ~MassageManager();

    void Update();
    void Draw();

    void IntoTalkStorage(std::string talkType,int talkNum);

    //メッセージが残っているかどうか　残っていればfalse 残ってなければtrue
    bool isEmpty();

    void setAutoMessage(bool a);
    bool getAutoMessage();

};


