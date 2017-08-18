#include "MessageReciever.h"
#include "../DebugDraw.h"
#include "../Resources/ResourceManager.h"

MessageReciever::MessageReciever()
    : _face("graph/devilGirlUsual.png", Vector2D(40, 545))
    , _messageUI("graph/ui/message_window.png", Vector2D(20, 520))

{
    _face.SetScale(Vector2D(2, 2));
    _messageUI.SetPriority(Sprite::Priority::UI);

    _faces.push_back(IMAGE_RESOURCE_TABLE->Create("graph/devilGirlUsual.png"));
    _faces.push_back(IMAGE_RESOURCE_TABLE->Create("graph/devilGirlAngry.png"));
    _faces.push_back(IMAGE_RESOURCE_TABLE->Create("graph/devilGirlSmile.png"));
    _faces.push_back(IMAGE_RESOURCE_TABLE->Create("graph/devilGirlCry.png"));
    _faces.push_back(IMAGE_RESOURCE_TABLE->Create("graph/face_braver.png"));
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
    //î≠òbé“ê›íË
    if (!_processer.isEmpty())
    {
        auto currentData = _processer.GetCurrentTalkData();
        if (0 <= currentData.speakPeople
            &&  currentData.speakPeople < _faces.size())
            _face.SetResource(_faces[currentData.speakFace]);
    }

    //ï∂éöëóÇËï`âÊ
    _processer.Draw(Vector2D(200, 550));
}