#pragma once
#include <string>


class BGM {

private:

    static const int BGM_NUM_MAX = 10;
    static const int SE_NUM_MAX = 20;

    int bgmHandle[BGM_NUM_MAX];
    int seHandle[SE_NUM_MAX];

public:
    BGM();
    BGM(std::string class_name);
    ~BGM();

    void BGMPlay();//bgmHandle[0]を再生する。既に再生されている場合、何もしない。再生する際、全てのBGMを停止する
    void BGMPlay(int bgmNum);//bgmHandle[bgmNum]を再生する。既に再生されている場合、何もしない。再生する際、全てのBGMを停止する
    void BGMStop();//全てのBGMを停止する

    void SEPlay(int seNum);//seHandle[bgmNum]を再生する。
    void SEStop(int seNum);//seHandle[bgmNum]を停止する。

};