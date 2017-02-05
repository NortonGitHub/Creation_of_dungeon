#ifndef Sound_h
#define Sound_h

#include <string>
#include <vector>
#include <memory>
#include "../Resources/SoundResource.h"

class Sound
{
public:
    Sound(std::string fileName = "", bool isLoopType = false);
    ~Sound();
    
    void Load(std::string fileName);

    void Play();
    void Stop();

    //ミリ秒指定でループ位置を指定する
    void SetLoop(int loopPos);

    //0~255で指定する
    void SetVolume(int volume);

    //0~255で指定する
    int GetVolume() const { return _volume; };

    bool IsPlaying() const;

    //ループ可能か
    bool _isLoop;

private:

    std::shared_ptr<SoundResource> _soundResource;

    //音量
    int _volume;

    //基本音量 (リソースごとの音量に掛けられる値)
    static int BGM_BASE_VOLUME;
    static int SE_BASE_VOLUME;

};

#endif /* Sound_h */
