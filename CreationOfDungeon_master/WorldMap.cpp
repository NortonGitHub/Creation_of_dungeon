#include "WorldMap.h"
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <typeinfo>
#include "DxLib.h"
#include "Game.h"
#include "Title.h"
#include "EditMap.h"

//　03/15にて　書き直すのが間に合いそうにないので、最低限の機能のみで動くようにします　従来のものはコメントアウトで

WorldMap::WorldMap()
    : class_name("world_map")
    , _bgm("resource/sound/world1.wav", true)
{

    Init();
    _bgm.Play();

}


WorldMap::~WorldMap()
{
}

SceneBase* WorldMap::Update(UIManager _ui)
{
    //_ui.Update();
    return Update();
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
        /*
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
        */

        charaAnimeCnt++;

        if (charaAnimeCnt >= charaAnimeFrameTime * 4) {
            charaAnimeCnt = 0;
        }

        if (movePointList.empty() == true) {

            for (int i = 0; i < nowAreaPointList.size(); i++) {

                if (nowAreaPointList[i]->isPoint == 1 && nowAreaPointList[i]->isStayPoint == 1) {

                    int hit = 0;

                    if (nowAreaPointList[i]->hitType == 0) {

                        hit += ClickCheckCircle(nowAreaPointList[i]->x, nowAreaPointList[i]->y, pointR);
                        hit += ClickCheckCircle(nowAreaPointList[i]->x - 5, nowAreaPointList[i]->y, pointR - 1);
                        hit += ClickCheckCircle(nowAreaPointList[i]->x - 5 - 4, nowAreaPointList[i]->y, pointR - 2);
                        hit += ClickCheckCircle(nowAreaPointList[i]->x - 5 - 4 - 3, nowAreaPointList[i]->y, pointR - 3);
                        hit += ClickCheckCircle(nowAreaPointList[i]->x + 5, nowAreaPointList[i]->y, pointR - 1);
                        hit += ClickCheckCircle(nowAreaPointList[i]->x + 5 + 4, nowAreaPointList[i]->y, pointR - 2);
                        hit += ClickCheckCircle(nowAreaPointList[i]->x + 5 + 4 + 3, nowAreaPointList[i]->y, pointR - 3);

                    }
                    else if (nowAreaPointList[i]->hitType == 100) {
                        if (typeid(*nowAreaPointList[i]) == typeid(AreaConnectPoint)) {
                            hit += ClickCheckCircle(dynamic_cast<AreaConnectPoint*>(nowAreaPointList[i])->buttonX, dynamic_cast<AreaConnectPoint*>(nowAreaPointList[i])->buttonY, 15);
                        }
                    }


                    if (hit >= 1) {

                        if (nowMyPointNum == nowAreaPointList[i]->pointNum) {
                            stageNum = nowAreaPointList[i]->stageNum;
                            //return new Game(stageNum);
                            return new EditMap(stageNum);
                        }
                        else {
                            searchPath(nowAreaPointList[i]->pointNum);
                            //nowMyPointNum = nowAreaPointList[i]->pointNum;
                        }
                    }

                }
            }

        }
        else {
            movePoint();
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


    AreaGrBuffer[0] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
    /*
    AreaGrBuffer[1] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
    AreaGrBuffer[2] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
    AreaGrBuffer[3] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
    AreaGrBuffer[4] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
    AreaGrBuffer[5] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
    AreaGrBuffer[6] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
    AreaGrBuffer[7] = LoadGraph("resource/graph/worldMap/Area1Icon.png");
    */
    AreaGr = &AreaGrBuffer[0];

    charaGr_f[0] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlFront1.png");
    charaGr_f[1] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlFront2.png");
    charaGr_f[2] = charaGr_f[0];
    charaGr_f[3] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlFront3.png");

    charaGr_b[0] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlBack1.png");
    charaGr_b[1] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlBack2.png");
    charaGr_b[2] = charaGr_b[0];
    charaGr_b[3] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlBack3.png");

    charaGr_l[0] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlLeft1.png");
    charaGr_l[1] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlLeft2.png");
    charaGr_l[2] = charaGr_l[0];
    charaGr_l[3] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlLeft3.png");

    charaGr_r[0] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlRight1.png");
    charaGr_r[1] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlRight2.png");
    charaGr_r[2] = charaGr_r[0];
    charaGr_r[3] = LoadGraph("resource/graph/worldMap//DevilGirlMini/DevilGirlRight3.png");


    blend = 0;
    blendFlag = 0;

    isPause = false;
    keyFlag = false;

    clickFlag = false;

    nowMyAreaNum = 1;
    nowMyPointNum = 1;



    mySpeed = 0.0;

    myVx = 0.0;
    myVy = 0.0;

    charaAnimeCnt = 0;

    charaAnimeFrameTime = 15;

    debugFlag = false;

    setNowAreaPointList();

    setNowRoadConnect();

    movePointList.clear();

    AreaGr = &AreaGrBuffer[nowMyAreaNum - 1];

}


void WorldMap::DrawMap() {

    DrawGraph(0, 0, *AreaGr, TRUE);

    /*
    for (int i = 0; i < nowRoadConnect.size(); i++) {

        int road1 = PointSearch(nowRoadConnect[i]->road[0]);
        int road2 = PointSearch(nowRoadConnect[i]->road[1]);

        DrawLine(nowAreaPointList[road1]->x, nowAreaPointList[road1]->y, nowAreaPointList[road2]->x, nowAreaPointList[road2]->y, GetColor(255, 255, 255), 10);

    }
    */

    for (int i = 0; i < nowAreaPointList.size(); i++) {

        if (nowAreaPointList[i]->isPoint == 1) {

            if (nowAreaPointList[i]->isStayPoint == 1) {
                if (typeid(*nowAreaPointList[i]) == typeid(AreaConnectPoint)) {
                    //DrawCircle(dynamic_cast<AreaConnectPoint*>(nowAreaPointList[i])->buttonX, dynamic_cast<AreaConnectPoint*>(nowAreaPointList[i])->buttonY, 15, GetColor(255, 0, 0), TRUE);
                }
                else {
                    //DrawCircle(nowAreaPointList[i]->x, nowAreaPointList[i]->y, pointR, GetColor(255, 0, 0), TRUE);
                    //DrawCircle(nowAreaPointList[i]->x - 5, nowAreaPointList[i]->y, pointR - 1, GetColor(255, 0, 0), TRUE);
                    //DrawCircle(nowAreaPointList[i]->x - 5 - 4, nowAreaPointList[i]->y, pointR - 2, GetColor(255, 0, 0), TRUE);
                    //DrawCircle(nowAreaPointList[i]->x - 5 - 4 - 3, nowAreaPointList[i]->y, pointR - 3, GetColor(255, 0, 0), TRUE);
                    //DrawCircle(nowAreaPointList[i]->x + 5, nowAreaPointList[i]->y, pointR - 1, GetColor(255, 0, 0), TRUE);
                    //DrawCircle(nowAreaPointList[i]->x + 5 + 4, nowAreaPointList[i]->y, pointR - 2, GetColor(255, 0, 0), TRUE);
                    //DrawCircle(nowAreaPointList[i]->x + 5 + 4 + 3, nowAreaPointList[i]->y, pointR - 3, GetColor(255, 0, 0), TRUE);
                }
            }
            else {
                DrawCircle(nowAreaPointList[i]->x, nowAreaPointList[i]->y, pointR, GetColor(255, 0, 0), TRUE);
            }

        }

        if (nowAreaPointList[i]->pointNum == nowMyPointNum) {
            myX = nowAreaPointList[i]->x;
            myY = nowAreaPointList[i]->y;
        }

    }


    if (nowMyPointNum != -1 || (myVx == 0 && myVy == 0)) {
        DrawRotaGraph(myX, myY - 12, 1.0, 0, charaGr_f[charaAnimeCnt / charaAnimeFrameTime], TRUE);
    }
    else if (fabs(myVx) > fabs(myVy)) {
        if (myVx > 0) {
            DrawRotaGraph(myX, myY - 12, 1.0, 0, charaGr_r[charaAnimeCnt / charaAnimeFrameTime], TRUE);
        }
        else {
            DrawRotaGraph(myX, myY - 12, 1.0, 0, charaGr_l[charaAnimeCnt / charaAnimeFrameTime], TRUE);
        }
    }
    else {
        if (myVy > 0) {
            DrawRotaGraph(myX, myY - 12, 1.0, 0, charaGr_f[charaAnimeCnt / charaAnimeFrameTime], TRUE);
        }
        else {
            DrawRotaGraph(myX, myY - 12, 1.0, 0, charaGr_b[charaAnimeCnt / charaAnimeFrameTime], TRUE);
        }
    }



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

        if (nowAreaPointList[vec]->pointNum == pointNum) {
            return vec;
        }

    }



    return -1;



}






bool WorldMap::checkMoveReach(Point* point) {



    double margin = 5.0;

    if (point->x - margin <= myX && point->x + margin >= myX && point->y - margin <= myY && point->y + margin >= myY) {

        myX = point->x;
        myY = point->y;

        return true;
    }



    return false;



}

void WorldMap::setNowAreaPointList() {

    //nowAreaPointList.reserve(100);

    //ここからポイント情報の読み込み
    //ファイルの読み込み

    nowAreaPointList.clear();

    std::string path = "csv/WorldMap/Area" + std::to_string(nowMyAreaNum) + ".csv";

    if (debugFlag == true) {
        path = "csv/WorldMap/Area_debug.csv";
    }

    std::ifstream ifs(path);
    if (ifs.fail()) {
        printfDx("fail\n");
        return;
    }

    int dataType = 0;   //読み込むデータ　ポイント情報か、エリア移動か

    //csvファイルを1行ずつ読み込む
    std::string str;
    while (getline(ifs, str)) {
        std::string::size_type index = str.find("#");  // "#"を検索
                                                       //"#"が入っていた行は飛ばす
        if (index != std::string::npos) {
            continue;
        }

        index = str.find("end");  // "end"を検索

        if (index != std::string::npos) {
            dataType++;
            continue;
        }

        std::string token;
        std::istringstream stream(str);

        Point* point = new Point();

        AreaConnectPoint* areaConnectPoint = new AreaConnectPoint();

        int num = 0;
        //1行のうち、文字列とコンマを分割する
        while (getline(stream, token, ',')) {

            if (dataType == 0) {

                switch (num) {
                case 0:
                    point->pointNum = stoi(token);
                    break;
                case 1:
                    point->stageNum = token;
                    break;
                case 2:
                    point->x = stoi(token);
                    break;
                case 3:
                    point->y = stoi(token);
                    break;
                case 4:
                    point->hitType = stoi(token);
                    break;
                case 5:
                    point->isStayPoint = stoi(token);
                    break;

                default:

                    if (num > 5) {
                        PointConnect* pc = new PointConnect();
                        pc->connectPointNum = stoi(token);
                        pc->PointCost = -1;
                        point->pointConect.push_back(pc);
                    }

                    break;
                }
            }
            else {

                switch (num) {
                case 0:
                    areaConnectPoint->pointNum = stoi(token);
                    break;
                case 1:
                    areaConnectPoint->moveArea = stoi(token);
                    break;
                case 2:
                    areaConnectPoint->buttonX = stoi(token);
                    break;
                case 3:
                    areaConnectPoint->buttonY = stoi(token);
                    break;
                case 4:
                    areaConnectPoint->x = stoi(token);
                    break;
                case 5:
                    areaConnectPoint->y = stoi(token);
                    break;
                case 6:
                    areaConnectPoint->firstMovePoint = stoi(token);
                    break;
                case 7:
                    areaConnectPoint->firstX = stoi(token);
                    break;
                case 8:
                    areaConnectPoint->firstY = stoi(token);
                    break;

                default:

                    if (num > 8) {
                        PointConnect* pc = new PointConnect();
                        pc->connectPointNum = stoi(token);
                        pc->PointCost = -1;
                        areaConnectPoint->pointConect.push_back(pc);
                    }

                    break;

                }
            }
            num++;
        }

        if (num != -1 && dataType == 0) {
            point->isPoint = 1;
            point->AreaNum = nowMyAreaNum;
            nowAreaPointList.push_back(point);
        }
        else if (num != -1 && dataType == 1) {
            areaConnectPoint->AreaNum = nowMyAreaNum;
            areaConnectPoint->hitType = 100;
            areaConnectPoint->isPoint = 1;
            areaConnectPoint->isStayPoint = 1;
            areaConnectPoint->stageNum = "";
            nowAreaPointList.push_back(areaConnectPoint);
        }

    }


    setPointCost();


}

void WorldMap::setNowRoadConnect() {

    nowRoadConnect.clear();

    for (int i = 0; i < nowAreaPointList.size(); i++) {

        if (nowAreaPointList[i]->isPoint == 1) {

            for (int j = 0; j < nowAreaPointList[i]->pointConect.size(); j++) {

                bool isConnect = true;

                for (int n = 0; n < nowRoadConnect.size(); n++) {

                    for (int b = 0; b < 2; b++) {
                        if (nowRoadConnect[n]->road[(b + 2) % 2] == nowAreaPointList[i]->pointNum && nowRoadConnect[n]->road[(b + 1 + 2) % 2] == nowAreaPointList[i]->pointConect[j]->connectPointNum) {
                            isConnect = false;
                            break;
                        }
                    }
                    if (isConnect == false) {
                        break;
                    }

                }

                if (isConnect == true) {
                    RoadConnect* rc = new RoadConnect();
                    rc->road[0] = nowAreaPointList[i]->pointNum;
                    rc->road[1] = nowAreaPointList[i]->pointConect[j]->connectPointNum;
                    nowRoadConnect.push_back(rc);
                }

            }



        }


    }
}

void WorldMap::setPointCost() {

    for (int i = 0; i < nowAreaPointList.size(); i++) {
        for (int j = 0; j < nowAreaPointList[i]->pointConect.size(); j++) {

            if (nowAreaPointList[i]->pointConect[j]->PointCost == -1) {

                Point* tempPoint = getPoint(nowAreaPointList[i]->pointConect[j]->connectPointNum);
                nowAreaPointList[i]->pointConect[j]->PointCost = std::hypot(nowAreaPointList[i]->x - tempPoint->x, nowAreaPointList[i]->y - tempPoint->y);

                for (int n = 0; n < tempPoint->pointConect.size(); n++) {
                    if (tempPoint->pointConect[n]->connectPointNum == nowAreaPointList[i]->pointNum) {
                        tempPoint->pointConect[n]->PointCost = nowAreaPointList[i]->pointConect[j]->PointCost;
                    }
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




WorldMap::Point* WorldMap::getPoint(int pointNum) {

    for (int i = 0; i < nowAreaPointList.size(); i++) {
        if (nowAreaPointList[i]->pointNum == pointNum) {
            return nowAreaPointList[i];
        }
    }

    return nullptr;

}



void WorldMap::movePoint() {

    Point* point;

    point = getPoint(movePointList[0]);

    bool isArrive = false;

    isArrive = checkMoveReach(point);

    if (isArrive == true) {

        if (typeid(*point) == typeid(AreaConnectPoint)) {

            AreaConnectPoint* areaPoint = dynamic_cast<AreaConnectPoint*>(point);

            setAreaNum(areaPoint->moveArea);

            myX = areaPoint->firstX;
            myY = areaPoint->firstY;
            
            movePointList.push_back(areaPoint->firstMovePoint);


        }else{
            movePointList.erase(movePointList.begin());

            if (movePointList.empty()) {
                nowMyPointNum = point->pointNum;
                mySpeed = 0.0;
                myVx = 0.0;
                myVy = 0.0;
                charaAnimeCnt = 0;
            }
        }
        

    }
    else {

        mySpeed = 3.0;

        double radian = 0.0;

        radian = atan2(point->y - myY, point->x - myX);

        myVx = cos(radian) * mySpeed;
        myVy = sin(radian) * mySpeed;

        myX += myVx;
        myY += myVy;

    }


}


void WorldMap::searchPath(int pointNum) {

    movePointList.clear();

    std::vector<SearchPointConnect*> spc;

    SearchPointConnect* sss = new SearchPointConnect();
    sss->connectPointNum = -1;
    sss->isSearch = false;
    sss->PointCost = 0;
    sss->pointNum = pointNum;

    spc.push_back(sss);

    setSearchPointConnect(pointNum, &spc);


    setMovePath(nowMyPointNum, &spc);


    /*
    Point* point;

    point = getPoint(nowMyPointNum);

    for (PointConnect* connectPoint : point->pointConect) {
        if (pointNum == connectPoint->connectPointNum) {
            movePointList.push_back(connectPoint->connectPointNum);
        }
    }
    */


    if (movePointList.empty()) {

    }
    else {
        nowMyPointNum = -1;
        charaAnimeCnt = 0;
    }




}




void WorldMap::setSearchPointConnect(int pointNum, std::vector<SearchPointConnect*>* spc) {

    double cost = 0;

    for (SearchPointConnect* ss : *spc) {
        if (ss->pointNum == pointNum && ss->isSearch == true) {
            return;
        }
        else if (ss->pointNum == pointNum && ss->isSearch == false) {
            ss->isSearch = true;
            cost = ss->PointCost;
        }
    }



    Point* point;

    point = getPoint(pointNum);

    for (PointConnect* connectPoint : point->pointConect) {

        bool is = false;

        for (SearchPointConnect* ss : *spc) {
            if (connectPoint->connectPointNum == ss->pointNum) {
                is = true;
                if (cost + connectPoint->PointCost < ss->PointCost) {
                    ss->connectPointNum = pointNum;
                    ss->PointCost = cost + connectPoint->PointCost;
                }
            }
        }

        if (is == false) {
            SearchPointConnect* ssq = new SearchPointConnect();
            ssq->connectPointNum = pointNum;
            ssq->isSearch = false;
            ssq->PointCost = cost + connectPoint->PointCost;
            ssq->pointNum = connectPoint->connectPointNum;
            spc->push_back(ssq);
        }

    }

    int pn = -1;
    int minCost = -1;

    for (SearchPointConnect* ss : *spc) {

        if (minCost == -1 && ss->isSearch == false) {
            pn = ss->pointNum;
            minCost = ss->PointCost;
        }
        else if (minCost > ss->PointCost && ss->isSearch == false) {
            pn = ss->pointNum;
            minCost = ss->PointCost;
        }

    }

    if (minCost == -1 && pn == -1) {
        return;
    }
    else {
        setSearchPointConnect(pn, spc);
    }


}



void WorldMap::setMovePath(int pointNum, std::vector<SearchPointConnect*>* spc) {

    for (SearchPointConnect* ss : *spc) {
        if (ss->pointNum == pointNum) {
            if (ss->connectPointNum == -1) {
                return;
            }
            else {
                movePointList.push_back(ss->connectPointNum);
                setMovePath(ss->connectPointNum, spc);
            }
        }
    }


}



void WorldMap::setAreaNum(int areaNum) {

    nowMyAreaNum = areaNum;
    nowMyPointNum = -1;



    mySpeed = 0.0;

    myVx = 0.0;
    myVy = 0.0;

    charaAnimeCnt = 0;

    setNowAreaPointList();

    setNowRoadConnect();

    movePointList.clear();

    AreaGr = &AreaGrBuffer[areaNum - 1];

}















