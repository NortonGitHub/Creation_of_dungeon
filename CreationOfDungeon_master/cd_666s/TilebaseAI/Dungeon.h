#ifndef Dungeon_h
#define Dungeon_h

#include <string>
#include <unordered_map>
#include "MonsterController.h"
#include "TiledVector.h"
#include "ColleagueNotifyer.h"
#include "ObjectInformationDrawer.h"
#include "IntruderInfomation.h"
#include "TiledObjectDictionary.h"
#include "DungeonTimer.h"
#include "MessageReciever.h"

#include "../Render/Sprite.h"
#include "../Sound/Sound.h"



class Goal;
class StartPoint;

class Dungeon
{
public:
    Dungeon(std::string stageName);
    ~Dungeon();
    
    //void InitWithLoad(std::string stageName);
    void Init();
    void Clear();
    void Update();
    void Draw();

    bool HasClear();
    bool HasGameOver();
    
private:
    
    void LoadTileSize(std::string stageName, std::vector<std::string>& rawData);

    //�Q�[�����ԂƎ��Ԓʒm���W���[���Q
    DungeonTimer _timer;

    //�E�҂�ʂ��Ă�������
    int _permitivePassedNum;
    
    std::string _stageName;
    
    void GenerateObject(std::string typeName, int countX, int countY);
    
    //�����Ԃ̏�񋤗L��
    ColleagueNotifyer _enemys, _monsters;
    
    //�J�n�_�ƏI���n�_�̓O���[�o���ȃ��x���ŃC���X�^���X�������Ă���
    std::shared_ptr<Goal> _goal;
    std::shared_ptr<StartPoint> _start;

    //�����X�^�[���샂�W���[��
    MonsterController _controller;

    //�A�C�R���Ɩ��O�̑Ή��\
    const TiledObjectDictionary _dictionary;

    //�I�����������X�^�[�̏��
    ObjectInformationDrawer _infoDrawer;

    //���ɐN�����Ă��郂���X�^�[�̏��
    IntruderInfomation _intruderInformation;

    //���b�Z�[�W�E�B���h�E
    MessageReciever _messageReciever;

    // MEMO : debug�p
    Sprite _mainsFrame, _background, _windowBackground, _waveInfomartionBoard;

    // MEMO : �ˊэH���p
    void LoadMessage(std::string stageName);
    void UpdateSecretary();
    std::unordered_map<std::string, TalkDatabase> _dungeonMessage;
    bool _intrudeLastCharacter;
};

#endif /* Dungeon_h */
