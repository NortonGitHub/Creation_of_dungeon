#include "MassageManager.h"
#include <Windows.h>
#include "DxLib.h"
#include "MouseManager.h"
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <algorithm>

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
        else if (i == 1) {
            str = "data\\talkData\\dynamic.csv";
        }


        //ファイルの読み込み
        std::ifstream ifs(str);
        if (ifs.fail()) {
            printfDx("fail\n");
            return;
        }

        int load = 0;   //0でロードする文章を発見していない 1でロードする文章を発見し読み込み中 2でロード終了

        int talkNum = 0;

        TalkDatabase tdb;

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
                        tdb.TalkGroupNum = stoi(token);
                    }
                    if (num == 2) {
                        tdb.talkData.importance = stoi(token);
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
                tdb.talkData.isStartMassage = true;
                switch (i) {
                case 0:
                    tdb.TalkType = nomal;
                    break;
                case 1:
                    tdb.TalkType = dynamic;
                    break;
                default:
                    break;
                }
                talkDatabase.push_back(tdb);
                tdb.talkData.messageData.clear();
            }

            if (load == 1 && mes.message.allMessage.empty() == 0) {
                tdb.talkData.messageData.push_back(mes);
            }


        }

    }

    



}

MassageManager::MassageManager(std::string situation) {



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

    Talk_Type tt;

    if (talkType == "nomal") {
        tt = nomal;
    }
    else if (talkType == "dynamic") {
        tt = dynamic;
    }


    std::vector<TalkDatabase>::iterator itr1;

    for (itr1 = talkDatabase.begin(); itr1 != talkDatabase.end(); itr1++) {

        if (itr1->TalkType == tt && itr1->TalkGroupNum == talkNum) {
            break;
        }

    }

    if (itr1 == talkDatabase.end()) {
        return;
    }
    

    if (TalkStorage.empty() == 0) {


        std::vector<TalkData>::iterator itr2;

        for (itr2 = TalkStorage.begin(); itr2 != TalkStorage.end(); itr2++) {
            if (itr1->talkData.importance > itr2->importance) {
                if (itr2->isStartMassage == false) {
                    TalkStorage.erase(TalkStorage.begin());
                    TalkStorage.insert(TalkStorage.begin(), itr1->talkData);
                    count = 0;
                    lastMessage = false;
                    itr2 = TalkStorage.begin();
                    break;
                }
                else if (itr2->messageData[0].message.displayedMessage.empty() == 0) {
                    TalkStorage.erase(TalkStorage.begin());
                    TalkStorage.insert(TalkStorage.begin(), itr1->talkData);
                    count = 0;
                    lastMessage = false;
                    itr2 = TalkStorage.begin();
                    break;
                }else{
                    TalkStorage.insert(itr2, itr1->talkData);
                    itr2 = TalkStorage.begin();
                    break;
                }
            }
        }

        if (itr2 == TalkStorage.end()) {
            TalkStorage.push_back(itr1->talkData);
        }

    }
    else {
        TalkStorage.push_back(itr1->talkData);
    }

    

}

void MassageManager::IntoTalkStorage(std::string talkType, int talkNum, std::string* str, int strSize) {


    Talk_Type tt;

    if (talkType == "nomal") {
        tt = nomal;
    }
    else if (talkType == "dynamic") {
        tt = dynamic;
    }


    std::vector<TalkDatabase>::iterator itr1;

    for (itr1 = talkDatabase.begin(); itr1 != talkDatabase.end(); itr1++) {

        if (itr1->TalkType == tt && itr1->TalkGroupNum == talkNum) {
            break;
        }

    }

    if (itr1 == talkDatabase.end()) {
        return;
    }

    TalkDatabase tdb = (*itr1);

    std::string::size_type index;

    for (int i = 0; i < strSize; i++) {
        for (int j = 0; j < tdb.talkData.messageData.size(); j++) {
            index = tdb.talkData.messageData[j].message.allMessage.find("<%=%>");
            if (index != std::string::npos) {
                tdb.talkData.messageData[j].message.allMessage.replace(index, 5, str[i]);
                tdb.talkData.messageData[j].message.hiddenMessage.replace(index, 5, str[i]);
                break;
            }
        }
        if (index == std::string::npos) {
            break;
        }
    }


    if (TalkStorage.empty() == 0) {


        std::vector<TalkData>::iterator itr2;

        for (itr2 = TalkStorage.begin(); itr2 != TalkStorage.end(); itr2++) {
            if (tdb.talkData.importance > itr2->importance) {
                if (itr2->isStartMassage == false) {
                    TalkStorage.erase(TalkStorage.begin());
                    TalkStorage.insert(TalkStorage.begin(), tdb.talkData);
                    count = 0;
                    lastMessage = false;
                    itr2 = TalkStorage.begin();
                    break;
                }
                else if (itr2->messageData[0].message.displayedMessage.empty() == 0) {
                    TalkStorage.erase(TalkStorage.begin());
                    TalkStorage.insert(TalkStorage.begin(), tdb.talkData);
                    count = 0;
                    lastMessage = false;
                    itr2 = TalkStorage.begin();
                    break;
                }
                else {
                    TalkStorage.insert(itr2, tdb.talkData);
                    itr2 = TalkStorage.begin();
                    break;
                }
            }
        }

        if (itr2 == TalkStorage.end()) {
            TalkStorage.push_back(tdb.talkData);
        }

    }
    else {
        TalkStorage.push_back(tdb.talkData);
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





