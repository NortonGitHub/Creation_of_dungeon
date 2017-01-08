#include "Sound.h"
#include "DxLib.h"
#include "../Resources/ResourceManager.h"

//基本音量の初期値
int Sound::BGM_BASE_VOLUME = 50;
int Sound::SE_BASE_VOLUME = 75;

Sound::Sound(std::string fileName, bool isBGM)
    : _isBGM(isBGM)
{
    //ファイルを読み込んで音声データ生成
    _soundResource = std::dynamic_pointer_cast<SoundResource>
        (RESOURCE_TABLE->Create(std::make_shared<SoundResource>(RESOURCE_TABLE->GetFolderPath() + fileName)));
}


Sound::~Sound()
{
    Stop();
    _soundResource = nullptr;
}


void Sound::Play()
{
    if (_isLoop)
        PlaySoundMem(_soundResource->GetHandle(), DX_PLAYTYPE_LOOP);
    else
        PlaySoundMem(_soundResource->GetHandle(), DX_PLAYTYPE_BACK);
}


void Sound::Stop()
{
    StopSoundMem(_soundResource->GetHandle());
}

void Sound::SetLoop(int loopPos)
{
    SetLoopPosSoundMem(loopPos, _soundResource->GetHandle());
}

void Sound::SetVolume(int volume)
{
    //基本音量を書き換えて
    _volume = volume;

    //音声ファイルタイプの基本音量を取得して
    double ratio = (_isBGM) ? static_cast<double>(BGM_BASE_VOLUME)
        : static_cast<double>(SE_BASE_VOLUME);
    ratio /= 100.0;

    //0 - 255 の値とBASE_VOLUMEの倍率で最終的な音量決定
    ChangeVolumeSoundMem(static_cast<int>(_volume * ratio), _soundResource->GetHandle());
}

bool Sound::IsPlaying() const
{
    return (CheckSoundMem(_soundResource->GetHandle()) == 1);
}