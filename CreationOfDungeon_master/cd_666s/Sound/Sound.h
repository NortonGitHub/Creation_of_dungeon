#ifndef Sound_h
#define Sound_h

#include <string>
#include <vector>
#include <memory>
#include "../Resources/SoundResource.h"

class Sound
{
public:
    Sound(std::string fileName, bool isBGM = false);
    ~Sound();
    
    void Play();
    void Stop();

    //�~���b�w��Ń��[�v�ʒu���w�肷��
    void SetLoop(int loopPos);

    //0~255�Ŏw�肷��
    void SetVolume(int volume);

    //0~255�Ŏw�肷��
    int GetVolume() const { return _volume; };

    bool IsPlaying() const;

    //���[�v�\��
    bool _isLoop;

private:

    std::shared_ptr<SoundResource> _soundResource;

    //����
    int _volume;

    //���̉�����BGM���ǂ���
    const bool _isBGM;

    //��{���� (���\�[�X���Ƃ̉��ʂɊ|������l)
    static int BGM_BASE_VOLUME;
    static int SE_BASE_VOLUME;

};

#endif /* Sound_h */