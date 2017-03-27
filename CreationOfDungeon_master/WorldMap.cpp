#include "WorldMap.h"
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include "DxLib.h"
#include "Game.h"
#include "Title.h"

//　03/15にて　書き直すのが間に合いそうにないので、最低限の機能のみで動くようにします　従来のものはコメントアウトで

WorldMap::WorldMap()
{

    Init();

}


WorldMap::~WorldMap()
{
}

SceneBase * WorldMap::Update()
{

    char Buf[256];

    GetHitKeyStateAll(Buf);

    if (Buf[KEY_INPUT_ESCAPE] == 1)
    {
        if (keyFlag == false) {
            isPause = !isPause;
            keyFlag = true;
        }
        
    }
    else {
        keyFlag = false;
    }

    int mx, my;

    GetMousePoint(&mx, &my);

    if (isPause == false) {
        if (blendFlag == 0) {
            blend += 10;
        }
        else {
            blend -= 10;
        }

        if (blend > 255) {
            blend = 255;
            blendFlag = 1;
        }
        if (blend < 0) {
            blend = 0;
            blendFlag = 0;
        }


        for (auto itr = nowAreaPointList.begin(); itr != nowAreaPointList.end(); itr++) {

            if (itr->isPoint == 1) {

                int hit = 0;

                if (itr->hitType == 0) {

                    hit += ClickCheckCircle(itr->x, itr->y, pointR);
                    hit += ClickCheckCircle(itr->x - 5, itr->y, pointR - 1);
                    hit += ClickCheckCircle(itr->x - 5 - 4, itr->y, pointR - 2);
                    hit += ClickCheckCircle(itr->x - 5 - 4 - 3, itr->y, pointR - 3);
                    hit += ClickCheckCircle(itr->x + 5, itr->y, pointR - 1);
                    hit += ClickCheckCircle(itr->x + 5 + 4, itr->y, pointR - 2);
                    hit += ClickCheckCircle(itr->x + 5 + 4 + 3, itr->y, pointR - 3);

                }


                if (hit >= 1) {

                    if (nowMyPointNum == itr->pointNum) {
                        stageNum = itr->stageNum;
                        return new Game();
                    }
                    else {
                        nowMyPointNum = itr->pointNum;
                    }
                }

            }
        }

    }
    else {

        //ここから「タイトルに戻る」のクリック判定

        int hit = 0;

        hit += ClickCheckBox(530, 300, 30 * 7 + 15, 30);

        if (hit >= 1) {
            return new Title();
        }

        //ここまで

        //ここから「ゲームを再開する」のクリック判定

        hit = 0;

        hit += ClickCheckBox(530, 400, 30 * 8 + 15, 30);

        if (hit >= 1) {
            isPause = !isPause;
        }

        //ここまで
        
    }

    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
    {

        if (clickFlag == false) {
            clickFlag = true;
        }

    }
    else {
        clickFlag = false;
    }
    
    printfDx("x:%d y:%d", mx, my);
    
    return this;
}

void WorldMap::Draw()
{
    
    clsDx();


    if (isPause == false) {

        DrawMap();

    }
    else {

        DrawMap();

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
        DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

        SetFontSize(60);
        DrawFormatString(550, 100, GetColor(255, 255, 255), "ポーズ");

        SetFontSize(30);
        DrawFormatString(530, 300, GetColor(255, 255, 255), "タイトルに戻る");
        DrawBox(530, 300, 530 + 30 * 7 + 15, 300 + 30, GetColor(255, 255, 255), FALSE);

        DrawFormatString(530, 400, GetColor(255, 255, 255), "ゲームを再開する");
        DrawBox(530, 400, 530 + 30 * 8 + 15, 400 + 30, GetColor(255, 255, 255), FALSE);

        

    }

    

}



void WorldMap::Init() {


    /*

    finishPointNum = -1;

    isMyMove = false;

    myMoveDirection = -1;

    myVx = 0;

    myVy = 0;
    

    myPointSet(1);

    mySpeed = 3;

    */

    Area1Gr = LoadGraph("CreationOfDungeon_master/graph/Area1Icon.png");

    blend = 0;
    blendFlag = 0;

    isPause = false;
    keyFlag = false;

    clickFlag = false;

    nowMyAreaNum = 1;
    nowMyPointNum = 1;

    setNowAreaPointList();

    setNowRoadConnect();

}

void WorldMap::DrawMap() {

    DrawGraph(0, 0, Area1Gr, TRUE);

    
    int x = 0;
    int y = 0;
    

    for (auto itr = nowRoadConnect.begin(); itr != nowRoadConnect.end(); itr++) {
        int road1 = PointSearch(itr->road[0]);
        int road2 = PointSearch(itr->road[1]);

        DrawLine(nowAreaPointList[road1].x, nowAreaPointList[road1].y, nowAreaPointList[road2].x, nowAreaPointList[road2].y, GetColor(255, 255, 255), 10);

    }


    for (auto itr = nowAreaPointList.begin(); itr != nowAreaPointList.end(); itr++) {

        if (itr->isPoint == 1) {

            DrawCircle(itr->x, itr->y, pointR, GetColor(255, 0, 0), TRUE);
            DrawCircle(itr->x - 5, itr->y, pointR - 1, GetColor(255, 0, 0), TRUE);
            DrawCircle(itr->x - 5 - 4, itr->y, pointR - 2, GetColor(255, 0, 0), TRUE);
            DrawCircle(itr->x - 5 - 4 - 3, itr->y, pointR - 3, GetColor(255, 0, 0), TRUE);
            DrawCircle(itr->x + 5, itr->y, pointR - 1, GetColor(255, 0, 0), TRUE);
            DrawCircle(itr->x + 5 + 4, itr->y, pointR - 2, GetColor(255, 0, 0), TRUE);
            DrawCircle(itr->x + 5 + 4 + 3, itr->y, pointR - 3, GetColor(255, 0, 0), TRUE);

        }

        if (itr->pointNum == nowMyPointNum) {
            x = itr->x;
            y = itr->y;
        }

    }

    


    SetFontSize(30);
    DrawFormatString(x - 15, y - 15, GetColor(255, 255, 255), "MY");
    
}


bool WorldMap::myPointSet(int PointNum) {

    //std::vector<Point>::iterator itr;

    /*
    for (auto itr = nowMapPointList.begin(); itr != nowMapPointList.end(); itr++) {

        if (itr->pointNum == PointNum) {
            nowMyPointNum = itr->pointNum;
            nowMyStageNum = itr->stageNum;
            myX = itr->x;
            myY = itr->y;
            return true;
        }

    }

    */


    return false;
    

}

int WorldMap::PointSearch(int pointNum) {

    
    for (int vec = 0; vec < nowAreaPointList.size(); vec++) {

        if (nowAreaPointList[vec].pointNum == pointNum) {
            return vec;
        }

    }

    

    return -1;

    

}






bool WorldMap::checkMoveReach() {

    /*

    double margin = 5.0;

    if (targetTurnPointList[0].x - margin <= myX && targetTurnPointList[0].x + margin >= myX && targetTurnPointList[0].y - margin <= myY && targetTurnPointList[0].y + margin >= myY) {
        
        myX = targetTurnPointList[0].x;
        myY = targetTurnPointList[0].y;

        return true;
    }

    */

    return false;

    

}

void WorldMap::setNowAreaPointList() {

    

    //ここからポイント情報の読み込み
    //ファイルの読み込み

    std::string path = "CreationOfDungeon_master\\csv\\WorldMap\\Area" + std::to_string(nowMyAreaNum) + ".csv";

    std::ifstream ifs(path);
    if (ifs.fail()) {
        printfDx("fail\n");
        return;
    }

    //csvファイルを1行ずつ読み込む
    std::string str;
    while (getline(ifs, str)) {
        std::string::size_type index = str.find("#");  // "#"を検索
                                                       //"#"が入っていた行は飛ばす
        if (index != std::string::npos) {
            continue;
        }


        std::string token;
        std::istringstream stream(str);

        Point point;
        PointConnect pc;
        int num = 0;
        //1行のうち、文字列とコンマを分割する
        while (getline(stream, token, ',')) {
            switch (num) {
            case 0:
                point.pointNum = stoi(token);
                break;
            case 1:
                point.stageNum = stoi(token);
                break;
            case 2:
                point.x = stoi(token);
                break;
            case 3:
                point.y = stoi(token);
                break;
            case 4:
                point.hitType = stoi(token);
                break;
            case 5:
                point.isStayPoint = stoi(token);
                break;
            
            default:

                if (num > 5) {
                    pc.connectPointNum = stoi(token);
                    pc.PointCost = -1;
                }

                break;
            }

            num++;

        }

        if (num != -1) {
            point.isPoint = 1;
            point.pointConect.push_back(pc);
            nowAreaPointList.push_back(point);
        }

    }

    

}

void WorldMap::setNowRoadConnect() {

    for (auto itr = nowAreaPointList.begin(); itr != nowAreaPointList.end(); itr++) {

        if (itr->isPoint == 1) {

            for (auto itr2 = itr->pointConect.begin(); itr2 != itr->pointConect.end(); itr2++) {

                bool isConnect = true;

                for (auto itr3 = nowRoadConnect.begin(); itr3 != nowRoadConnect.end(); itr3++) {

                    for (int i = 0; i < 2; i++) {
                        if (itr3->road[(i + 2) % 2] == itr->pointNum && itr3->road[(i + 1 + 2) % 2] == itr2->connectPointNum) {
                            isConnect = false;
                            break;
                        }
                    }
                    if (isConnect == false) {
                        break;
                    }

                }

                if (isConnect == true) {
                    RoadConnect rc;
                    rc.road[0] = itr->pointNum;
                    rc.road[1] = itr2->connectPointNum;
                    nowRoadConnect.push_back(rc);
                }

            }



        }


    }
}



int WorldMap::ClickCheckBox(int x, int y, int rx, int ry) {

    int mx, my;

    GetMousePoint(&mx, &my);

    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
    {

        if (clickFlag == false) {
            if (mx > x && mx < x + rx && my > y && my < y + ry) {
                return 1;
            }
        }
        
    }

    return 0;

}


int WorldMap::ClickCheckCircle(int x, int y, int r) {

    int mx, my;

    GetMousePoint(&mx, &my);

    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
    {

        if (clickFlag == false) {
            if (pow((x - mx)*(x - mx) + (y - my)*(y - my), 0.5) < r) {
                return 1;
            }
        }
        
    }

    return 0;

}












