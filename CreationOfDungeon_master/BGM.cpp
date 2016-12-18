#include "BGM.h"
#include "DxLib.h"


BGM::BGM() {

}

BGM::BGM(std::string class_name) {
    //bgmHandle[0]によく使うBGMをロードする
    //BGMは同時再生できないようにしている

    if (class_name == "game") {
        //現在取り合えず適当に書いている
        bgmHandle[0] = LoadSoundMem("bgm\\sample.ogg");

        seHandle[0] = LoadSoundMem("se\\sample.ogg");

    }
    else if (class_name == "editmap") {


    }

}

BGM::~BGM() {

    for (int i = 0; i < BGM_NUM_MAX; i++) {
        DeleteSoundMem(bgmHandle[i]);
    }

    for (int i = 0; i < SE_NUM_MAX; i++) {
        DeleteSoundMem(seHandle[i]);
    }

}

void BGM::BGMPlay() {

    if (CheckSoundMem(bgmHandle[0])) {
        return;
    }

    for (int i = 0; i < BGM_NUM_MAX; i++) {
        StopSoundMem(bgmHandle[i]);
    }

    PlaySoundMem(bgmHandle[0], DX_PLAYTYPE_LOOP, TRUE);


}

void BGM::BGMPlay(int bgmNum) {

    if (CheckSoundMem(bgmHandle[bgmNum])) {
        return;
    }

    for (int i = 0; i < BGM_NUM_MAX; i++) {
        StopSoundMem(bgmHandle[i]);
    }

    PlaySoundMem(bgmHandle[bgmNum], DX_PLAYTYPE_LOOP, TRUE);

}

void BGM::BGMStop() {

    for (int i = 0; i < BGM_NUM_MAX; i++) {
        StopSoundMem(bgmHandle[i]);
    }

}


void BGM::SEPlay(int seNum) {

    PlaySoundMem(seHandle[seNum], DX_PLAYTYPE_BACK, TRUE);

}

void BGM::SEStop(int seNum) {

    for (int i = 0; i < SE_NUM_MAX; i++) {
        StopSoundMem(seHandle[i]);
    }

}




