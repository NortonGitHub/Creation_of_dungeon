#include "MassageManager.h"
#include <Windows.h>
#include "DxLib.h"
#include "MouseManager.h"
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

#pragma once




MassageManager::MassageManager() {

    count = 0;

    lastMessage = false;

    push = false;

    autoMessage = true;

    TalkStorage.clear();

    for (int i = 0; i < TalkTypeNum; i++) {

        std::string str = "";

        if (i == 0) {
            str = "data\\talkData\\nomal.csv";
        }


        //ファイルの読み込み
        std::ifstream ifs(str);
        if (ifs.fail()) {
            printfDx("fail\n");
            return;
        }

        int load = 0;   //0でロードする文章を発見していない 1でロードする文章を発見し読み込み中 2でロード終了

        int talkNum = 0;

        while (getline(ifs, str)) {
            std::string::size_type index = str.find("#");  // "#"を検索
                                                           //"#"が入っていた行は飛ばす
            if (index != std::string::npos) {
                continue;
            }

            index = str.find("*talkNum");  // "*talkNum"を検索

            if (index == std::string::npos && load == 0) {
                continue;                       //"*talkNum"が入っていない行は飛ばす
            }



            std::string token;
            std::istringstream stream(str);

            MessageData mes;

            int num = 0;
            
            //1行のうち、文字列とコンマを分割する
            while (getline(stream, token, ',')) {

                if (load == 0) {
                    if (num == 1) {
                        talkNum = stoi(token);
                    }
                    if (num == 2) {
                        talkDatabase[i][talkNum].importance = stoi(token);
                        load = 1;
                        break;
                    }
                }
                else if (load == 1) {

                    if (num == 0) {
                        if (token == "*end") {
                            load = 2;
                            break;
                        }
                    }

                    switch (num) {
                    case 0:
                        mes.speakPeople = stoi(token);
                        break;
                    case 1:
                        mes.speakFace = stoi(token);
                        break;
                    case 2:
                        mes.message.allMessage = token;
                        mes.message.hiddenMessage = token;
                        mes.message.displayedMessage = "";
                        break;
                    default:
                        break;
                    }


                }

                num++;

            }

            if (load == 2) {
                load = 0;
                talkDatabase[i][talkNum].isStartMassage = true;
            }

            if (load == 1 && mes.message.allMessage.empty() == 0) {
                talkDatabase[i][talkNum].messageData.push_back(mes);
            }


        }

    }

    



}

MassageManager::~MassageManager() {



}

void MassageManager::Update() {

    


    if (TalkStorage.empty()) {
        count = 0;
        lastMessage = false;
        return; //TalkStorageが空なら何もしない
    }
    else {

        count++;
        if (count > waitFrame && lastMessage == false) {
            count = 0;
            if (IsDBCSLeadByte(TalkStorage[0].messageData[0].message.hiddenMessage[0]) == 0) {
                std::string c = (TalkStorage[0].messageData[0].message.hiddenMessage).substr(0, 1).c_str();
                TalkStorage[0].messageData[0].message.displayedMessage += c;
                TalkStorage[0].messageData[0].message.hiddenMessage.erase(0, 1);
            }
            else {
                std::string c = (TalkStorage[0].messageData[0].message.hiddenMessage).substr(0, 2);
                TalkStorage[0].messageData[0].message.displayedMessage += c;
                TalkStorage[0].messageData[0].message.hiddenMessage.erase(0, 2);
            }
            if (TalkStorage[0].messageData[0].message.hiddenMessage.empty()) {
                lastMessage = true;
            }
            else {
                lastMessage = false;
            }
        }

        if (count > waitFrame && lastMessage == true) {

            if (autoMessage == true) {
                if (count > lastWaitFrame) {
                    if (TalkStorage[0].messageData[0].message.hiddenMessage.empty()) {
                        lastMessage = false;
                        TalkStorage[0].messageData.erase(TalkStorage[0].messageData.begin());
                        TalkStorage[0].isStartMassage = false;
                        count = 0;

                        if (TalkStorage[0].messageData.empty()) {
                            TalkStorage.erase(TalkStorage.begin());
                        }

                    }
                }
            }
            else{
                if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
                {
                    if (push == false) {
                        // 押されている
                        push = true;
                        if (TalkStorage[0].messageData[0].message.hiddenMessage.empty()) {
                            lastMessage = false;
                            TalkStorage[0].messageData.erase(TalkStorage[0].messageData.begin());

                            count = 0;

                            if (TalkStorage[0].messageData.empty()) {
                                TalkStorage.erase(TalkStorage.begin());
                            }

                        }

                    }
                }
                else
                {
                    // 押されていない
                    push = false;
                }
            }

            
            
            
        }

    }


}

void MassageManager::Draw() {

    if (TalkStorage.empty()) {
        count = 0;
        return; //TalkStorageが空なら何もしない
    }
    else {
        DrawFormatString(0, 250, GetColor(255, 255, 255), "%d番の人が%dの表情で話しています", TalkStorage[0].messageData[0].speakPeople, TalkStorage[0].messageData[0].speakFace);
        DrawFormatString(0, 300, GetColor(255, 255, 255), "%s", TalkStorage[0].messageData[0].message.displayedMessage.c_str());
    }

}

void MassageManager::IntoTalkStorage(std::string talkType, int talkNum) {

    int tt;

    if (talkType == "nomal") {
        tt = 0;
    }

    if (TalkStorage.empty() == 0) {

        std::vector<TalkData>::iterator itr;

        for (itr = TalkStorage.begin(); itr != TalkStorage.end(); itr++) {
            if (talkDatabase[tt][talkNum].importance > itr->importance) {
                if (itr->isStartMassage == false) {
                    TalkStorage.erase(TalkStorage.begin());
                    TalkStorage.insert(TalkStorage.begin(), talkDatabase[tt][talkNum]);
                    count = 0;
                    lastMessage = false;
                    itr = TalkStorage.begin();
                    break;
                }
                else if (itr->messageData[0].message.displayedMessage.empty() == 0) {
                    TalkStorage.erase(TalkStorage.begin());
                    TalkStorage.insert(TalkStorage.begin(), talkDatabase[tt][talkNum]);
                    count = 0;
                    lastMessage = false;
                    itr = TalkStorage.begin();
                    break;
                }else{
                    TalkStorage.insert(itr, talkDatabase[tt][talkNum]);
                    itr = TalkStorage.begin();
                    break;
                }
            }
        }

        if (itr == TalkStorage.end()) {
            TalkStorage.push_back(talkDatabase[tt][talkNum]);
        }

    }
    else {
        TalkStorage.push_back(talkDatabase[tt][talkNum]);
    }

    

}

bool MassageManager::isEmpty() {
    if (TalkStorage.empty()) {
        return true;
    }
    else {
        return false;
    }
}


void MassageManager::setAutoMessage(bool a) {
    autoMessage = a;
}

bool MassageManager::getAutoMessage() {
    return autoMessage;
}



