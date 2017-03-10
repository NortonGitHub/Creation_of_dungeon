#include "MessageReciever.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"

MessageReciever::MessageReciever()
    : _face("resourse/graph/devilGirlUsual.png", Vector2D(40, 545))
    , _messageUI("resourse/graph/ui/message_window.png", Vector2D(20, 520))

{
    _face.SetScale(Vector2D(2, 2));
    _messageUI.SetPriority(Sprite::Priority::UI);

    _faces.push_back(IMAGE_RESOURCE_TABLE->Create("resourse/graph/devilGirlUsual.png"));
    _faces.push_back(IMAGE_RESOURCE_TABLE->Create("resourse/graph/face_braver.png"));
    _faces.push_back(IMAGE_RESOURCE_TABLE->Create("resourse/graph/face_magician.png"));
}


MessageReciever::~MessageReciever()
{
}


void MessageReciever::Init()
{
    _processer.Init();
}


void MessageReciever::Recieve(const TalkDatabase& senderData)
{
    std::string typeStr = (senderData.TalkType == Talk_Type::dynamic) ? "dynamic" : "nomal";
    _processer.IntoTalkStorage(typeStr, senderData.TalkGroupNum);
}


void MessageReciever::Update()
{
    _processer.Update();
}


void MessageReciever::Draw()
{
    //発話者設定
    if (!_processer.isEmpty())
    {
        auto currentData = _processer.GetCurrentTalkData();
        if (0 <= currentData.speakPeople
            &&  currentData.speakPeople < _faces.size())
            _face.SetResource(_faces[currentData.speakPeople]);
    }

    //文字送り描画
    _processer.Draw(Vector2D(200, 550));
    //Debug::DrawString(Vector2D(300, 600), "クリエイションオブダンジョン体験版にようこそ");
}