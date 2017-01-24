#ifndef Dungeon_h
#define Dungeon_h

#include <string>
#include "MonsterController.h"
#include "TiledVector.h"
#include "ColleagueNotifyer.h"
#include "ObjectInformationDrawer.h"
#include "IntruderInfomation.h"
#include "DungeonTimer.h"
#include "../../Vector2D.h"
#include "../Render/Sprite.h"
#include "../Sound/Sound.h"

class GraphicalObject;
class TiledObject;
class Sprite;
class Sound;
class Action;
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

    //�I�����������X�^�[�̏��
    ObjectInformationDrawer _infoDrawer;

    //���ɐN�����Ă��郂���X�^�[�̏��
    IntruderInfomation _intruderInformation;

    // MEMO : debug�p
    Sprite _face, _messageUI, _mainsFrame, _background, _windowBackground, _waveInfomartionBoard;
    //std::vector<Sprite*> _icons;
};

#endif /* Dungeon_h */
