#include "Map.h"
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include "DxLib.h"


Map::Map()
{

    Init();

}


Map::~Map()
{
}

SceneBase * Map::Update()
{

    if (isMyMove == true) {
        Moving();
    }
    else {
        KeyJudge();
    }

    
    
    
    return this;
}

void Map::Draw()
{
    /*
    clsDx();

    for (auto itr = nowMapRoadList.begin(); itr != nowMapRoadList.end(); itr++) {

        printfDx("%d,", itr->mapNum);
        printfDx("%d,", itr->roadNum);
        printfDx("%d,", itr->startPointNum);
        printfDx("%d,", itr->endPointNum);
        printfDx("\n");
        for (auto itr2 = itr->roadTurnPoint.begin(); itr2 != itr->roadTurnPoint.end(); itr2++){

            printfDx("%f,", itr2->x);
            printfDx("%f,", itr2->y);
            printfDx("\n");
            
        }

        printfDx("\n");

    }
    */

    for (auto itr = nowMapPointList.begin(); itr != nowMapPointList.end(); itr++) {

        DrawCircle(itr->x, itr->y, pointR, GetColor(255, 0, 0), TRUE);

    }


    for (auto itr = nowMapRoadList.begin(); itr != nowMapRoadList.end(); itr++) {

        int num = PointSearch(itr->startPointNum);

        double LinkX = -1;
        double LinkY = -1;

        if (num != -1) {
            LinkX = nowMapPointList[num].x;
            LinkY = nowMapPointList[num].y;
        }
        
        for (auto itr3 = itr->roadTurnPoint.begin(); itr3 != itr->roadTurnPoint.end(); itr3++) {

            DrawCircle(itr3->x, itr3->y, 10, GetColor(255, 255, 0), TRUE);
            DrawLine(LinkX, LinkY, itr3->x, itr3->y, GetColor(255, 255, 255), 5);

            LinkX = itr3->x;
            LinkY = itr3->y;

        }

        num = PointSearch(itr->endPointNum);

        if (num != -1) {
            
            DrawLine(LinkX, LinkY, nowMapPointList[num].x, nowMapPointList[num].y, GetColor(255, 255, 255), 5);

        }

    }
    

    SetFontSize(20);
    DrawFormatString(myX-10, myY-10, GetColor(255, 255, 255),"MY");



}



void Map::Init() {

    nowMyMapNum = 1;

    nowMyPointNum = 0;

    finishPointNum = -1;

    isMyMove = false;

    myMoveDirection = -1;

    myVx = 0;

    myVy = 0;

    
    setNowMapPointList();

    setNowMapRoadList();
    

    myPointSet(1);

    mySpeed = 3;

}

bool Map::myPointSet(int PointNum) {

    //std::vector<Point>::iterator itr;

    for (auto itr = nowMapPointList.begin(); itr != nowMapPointList.end(); itr++) {

        if (itr->pointNum == PointNum) {
            nowMyPointNum = itr->pointNum;
            nowMyStageNum = itr->stageNum;
            myX = itr->x;
            myY = itr->y;
            return true;
        }

    }


    return false;

}

int Map::PointSearch(int pointNum) {

    for (int vec = 0; vec < nowMapPointList.size(); vec++) {

        if (nowMapPointList[vec].pointNum == pointNum) {
            return vec;
        }

    }

    return -1;

}

int Map::RoadSearch(int startPointNum, int endPointNum) {

    for (int vec = 0; vec < nowMapRoadList.size(); vec++) {

        if (nowMapRoadList[vec].startPointNum == startPointNum && nowMapRoadList[vec].endPointNum == endPointNum) {
            return vec;
        }
        if (nowMapRoadList[vec].startPointNum == endPointNum && nowMapRoadList[vec].endPointNum == startPointNum) {
            return vec;
        }

    }

    return -1;

}

void Map::Moving() {

    double radian = atan2(targetTurnPointList[0].y - myY, targetTurnPointList[0].x - myX);

    double tempX = cos(radian);
    double tempY = sin(radian);

    myVx = tempX * mySpeed;
    myVy = tempY * mySpeed;

    myX += myVx;
    myY += myVy;

    if (checkMoveReach() == true) {

        targetTurnPointList.erase(targetTurnPointList.begin());
        
        if (targetTurnPointList.size() <= 0) {
            
            myPointSet(finishPointNum);
            isMyMove = false;
            finishPointNum = -1;
            myMoveDirection = -1;
            targetTurnPointList.erase(targetTurnPointList.begin(), targetTurnPointList.end());

            int myPointInfoIndex = PointSearch(nowMyPointNum);
            
            if (nowMapPointList[myPointInfoIndex].mapMove_mapNum != -1) {

                nowMyMapNum = nowMapPointList[myPointInfoIndex].mapMove_mapNum;

                int moveMyPoint = nowMapPointList[myPointInfoIndex].mapMove_pointNum;

                nowMapPointList.erase(nowMapPointList.begin(), nowMapPointList.end());
                nowMapRoadList.erase(nowMapRoadList.begin(), nowMapRoadList.end());

                setNowMapPointList();
                setNowMapRoadList();

                myPointSet(moveMyPoint);

                myPointInfoIndex = PointSearch(nowMyPointNum);

                if (nowMapPointList[myPointInfoIndex].mapMove_movePointNum != -1) {
                    int roadNum = RoadSearch(nowMyPointNum, nowMapPointList[myPointInfoIndex].mapMove_movePointNum);
                    myMoveDirection = MoveDirection(nowMyPointNum, nowMapPointList[myPointInfoIndex].mapMove_movePointNum);
                    if (myMoveDirection == 1) {
                        for (int i = 0; i < nowMapRoadList[roadNum].roadTurnPoint.size(); i++) {
                            targetTurnPointList.push_back(nowMapRoadList[roadNum].roadTurnPoint[i]);
                        }
                        int finishPointIndex = PointSearch(nowMapPointList[myPointInfoIndex].mapMove_movePointNum);
                        RoadTurnPoint rtp;
                        rtp.x = nowMapPointList[finishPointIndex].x;
                        rtp.y = nowMapPointList[finishPointIndex].y;
                        finishPointNum = nowMapPointList[finishPointIndex].pointNum;
                        targetTurnPointList.push_back(rtp);
                    }
                    else if (myMoveDirection == 2) {
                        for (int i = nowMapRoadList[roadNum].roadTurnPoint.size() - 1; i >= 0; i--) {
                            targetTurnPointList.push_back(nowMapRoadList[roadNum].roadTurnPoint[i]);
                        }
                        int finishPointIndex = PointSearch(nowMapPointList[myPointInfoIndex].mapMove_movePointNum);
                        RoadTurnPoint rtp;
                        rtp.x = nowMapPointList[finishPointIndex].x;
                        rtp.y = nowMapPointList[finishPointIndex].y;
                        finishPointNum = nowMapPointList[finishPointIndex].pointNum;
                        targetTurnPointList.push_back(rtp);
                    }
                    isMyMove = true;
                }
                

            }


        }

    }

}

void Map::KeyJudge() {

    char KeyBuf[256];

    GetHitKeyStateAll(KeyBuf);

    int pointIndex = PointSearch(nowMyPointNum);

    if (KeyBuf[KEY_INPUT_UP] == 1) {
        if (pointIndex != -1) {
            if (nowMapPointList[pointIndex].upMovePoint != -1) {
                int roadNum = RoadSearch(nowMyPointNum, nowMapPointList[pointIndex].upMovePoint);
                myMoveDirection = MoveDirection(nowMyPointNum, nowMapPointList[pointIndex].upMovePoint);
                if (myMoveDirection == 1) {
                    for (int i = 0; i < nowMapRoadList[roadNum].roadTurnPoint.size(); i++) {
                        targetTurnPointList.push_back(nowMapRoadList[roadNum].roadTurnPoint[i]);
                    }
                    int finishPointIndex = PointSearch(nowMapPointList[pointIndex].upMovePoint);
                    RoadTurnPoint rtp;
                    rtp.x = nowMapPointList[finishPointIndex].x;
                    rtp.y = nowMapPointList[finishPointIndex].y;
                    finishPointNum = nowMapPointList[finishPointIndex].pointNum;
                    targetTurnPointList.push_back(rtp);
                }
                else if (myMoveDirection == 2) {
                    for (int i = nowMapRoadList[roadNum].roadTurnPoint.size() - 1; i >= 0; i--) {
                        targetTurnPointList.push_back(nowMapRoadList[roadNum].roadTurnPoint[i]);
                    }
                    int finishPointIndex = PointSearch(nowMapPointList[pointIndex].upMovePoint);
                    RoadTurnPoint rtp;
                    rtp.x = nowMapPointList[finishPointIndex].x;
                    rtp.y = nowMapPointList[finishPointIndex].y;
                    finishPointNum = nowMapPointList[finishPointIndex].pointNum;
                    targetTurnPointList.push_back(rtp);
                }
                isMyMove = true;
            }
        }
    }
    else if (KeyBuf[KEY_INPUT_DOWN] == 1) {
        if (pointIndex != -1) {
            if (nowMapPointList[pointIndex].downMovePoint != -1) {
                int roadNum = RoadSearch(nowMyPointNum, nowMapPointList[pointIndex].downMovePoint);
                myMoveDirection = MoveDirection(nowMyPointNum, nowMapPointList[pointIndex].downMovePoint);
                if (myMoveDirection == 1) {
                    for (int i = 0; i < nowMapRoadList[roadNum].roadTurnPoint.size(); i++) {
                        targetTurnPointList.push_back(nowMapRoadList[roadNum].roadTurnPoint[i]);
                    }
                    int finishPointIndex = PointSearch(nowMapPointList[pointIndex].downMovePoint);
                    RoadTurnPoint rtp;
                    rtp.x = nowMapPointList[finishPointIndex].x;
                    rtp.y = nowMapPointList[finishPointIndex].y;
                    finishPointNum = nowMapPointList[finishPointIndex].pointNum;
                    targetTurnPointList.push_back(rtp);
                }
                else if (myMoveDirection == 2) {
                    for (int i = nowMapRoadList[roadNum].roadTurnPoint.size() - 1; i >= 0; i--) {
                        targetTurnPointList.push_back(nowMapRoadList[roadNum].roadTurnPoint[i]);
                    }
                    int finishPointIndex = PointSearch(nowMapPointList[pointIndex].downMovePoint);
                    RoadTurnPoint rtp;
                    rtp.x = nowMapPointList[finishPointIndex].x;
                    rtp.y = nowMapPointList[finishPointIndex].y;
                    finishPointNum = nowMapPointList[finishPointIndex].pointNum;
                    targetTurnPointList.push_back(rtp);
                }
                isMyMove = true;
            }
        }
    }
    else if (KeyBuf[KEY_INPUT_LEFT] == 1) {
        if (pointIndex != -1) {
            if (nowMapPointList[pointIndex].leftMovePoint != -1) {
                int roadNum = RoadSearch(nowMyPointNum, nowMapPointList[pointIndex].leftMovePoint);
                myMoveDirection = MoveDirection(nowMyPointNum, nowMapPointList[pointIndex].leftMovePoint);
                if (myMoveDirection == 1) {
                    for (int i = 0; i < nowMapRoadList[roadNum].roadTurnPoint.size(); i++) {
                        targetTurnPointList.push_back(nowMapRoadList[roadNum].roadTurnPoint[i]);
                    }
                    int finishPointIndex = PointSearch(nowMapPointList[pointIndex].leftMovePoint);
                    RoadTurnPoint rtp;
                    rtp.x = nowMapPointList[finishPointIndex].x;
                    rtp.y = nowMapPointList[finishPointIndex].y;
                    finishPointNum = nowMapPointList[finishPointIndex].pointNum;
                    targetTurnPointList.push_back(rtp);
                }
                else if (myMoveDirection == 2) {
                    for (int i = nowMapRoadList[roadNum].roadTurnPoint.size() - 1; i >= 0; i--) {
                        targetTurnPointList.push_back(nowMapRoadList[roadNum].roadTurnPoint[i]);
                    }
                    int finishPointIndex = PointSearch(nowMapPointList[pointIndex].leftMovePoint);
                    RoadTurnPoint rtp;
                    rtp.x = nowMapPointList[finishPointIndex].x;
                    rtp.y = nowMapPointList[finishPointIndex].y;
                    finishPointNum = nowMapPointList[finishPointIndex].pointNum;
                    targetTurnPointList.push_back(rtp);
                }
                isMyMove = true;
            }
        }
    }
    else if (KeyBuf[KEY_INPUT_RIGHT] == 1) {
        if (pointIndex != -1) {
            if (nowMapPointList[pointIndex].rightMovePoint != -1) {
                int roadNum = RoadSearch(nowMyPointNum, nowMapPointList[pointIndex].rightMovePoint);
                myMoveDirection = MoveDirection(nowMyPointNum, nowMapPointList[pointIndex].rightMovePoint);
                if (myMoveDirection == 1) {
                    for (int i = 0; i < nowMapRoadList[roadNum].roadTurnPoint.size(); i++) {
                        targetTurnPointList.push_back(nowMapRoadList[roadNum].roadTurnPoint[i]);
                    }
                    int finishPointIndex = PointSearch(nowMapPointList[pointIndex].rightMovePoint);
                    RoadTurnPoint rtp;
                    rtp.x = nowMapPointList[finishPointIndex].x;
                    rtp.y = nowMapPointList[finishPointIndex].y;
                    finishPointNum = nowMapPointList[finishPointIndex].pointNum;
                    targetTurnPointList.push_back(rtp);
                }
                else if (myMoveDirection == 2) {
                    for (int i = nowMapRoadList[roadNum].roadTurnPoint.size() - 1; i >= 0; i--) {
                        targetTurnPointList.push_back(nowMapRoadList[roadNum].roadTurnPoint[i]);
                    }
                    int finishPointIndex = PointSearch(nowMapPointList[pointIndex].rightMovePoint);
                    RoadTurnPoint rtp;
                    rtp.x = nowMapPointList[finishPointIndex].x;
                    rtp.y = nowMapPointList[finishPointIndex].y;
                    finishPointNum = nowMapPointList[finishPointIndex].pointNum;
                    targetTurnPointList.push_back(rtp);
                }
                isMyMove = true;
            }
        }
    }

}


bool Map::checkMoveReach() {

    double margin = 5.0;

    if (targetTurnPointList[0].x - margin <= myX && targetTurnPointList[0].x + margin >= myX && targetTurnPointList[0].y - margin <= myY && targetTurnPointList[0].y + margin >= myY) {
        
        myX = targetTurnPointList[0].x;
        myY = targetTurnPointList[0].y;

        return true;
    }

    return false;

}

void Map::setNowMapPointList() {

    //ここからポイント情報の読み込み
    //ファイルの読み込み
    std::ifstream ifs("CreationOfDungeon_master\\csv\\WorldMap\\Point\\Point.csv");
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
        int num = 0;
        //1行のうち、文字列とコンマを分割する
        while (getline(stream, token, ',')) {
            if (num == 0 && stoi(token) != nowMyMapNum) {
                num = -1;
                break;
            }
            switch (num) {
            case 0:
                point.mapNum = stoi(token);
                break;
            case 1:
                point.pointNum = stoi(token);
                break;
            case 2:
                point.stageNum = stoi(token);
                break;
            case 3:
                point.mapMove_mapNum = stoi(token);
                break;
            case 4:
                point.mapMove_pointNum = stoi(token);
                break;
            case 5:
                point.mapMove_movePointNum = stoi(token);
                break;
            case 6:
                point.x = stod(token);
                break;
            case 7:
                point.y = stod(token);
                break;
            case 8:
                point.upMovePoint = stoi(token);
                break;
            case 9:
                point.downMovePoint = stoi(token);
                break;
            case 10:
                point.leftMovePoint = stoi(token);
                break;
            case 11:
                point.rightMovePoint = stoi(token);
                break;
            default:
                break;
            }

            num++;

        }

        if (num != -1) {
            nowMapPointList.push_back(point);
        }

    }

}

void Map::setNowMapRoadList() {

    //ここから道の情報の読み込み
    //ファイルの読み込み
    std::ifstream ifs2("CreationOfDungeon_master\\csv\\WorldMap\\Road\\Road.csv");
    if (ifs2.fail()) {
        printfDx("fail\n");
        return;
    }

    //csvファイルを1行ずつ読み込む
    std::string str;
    while (getline(ifs2, str)) {
        std::string::size_type index = str.find("#");  // "#"を検索
                                                       //"#"が入っていた行は飛ばす
        if (index != std::string::npos) {
            continue;
        }


        std::string token;
        std::istringstream stream(str);

        Road road;
        int num = 0;
        //1行のうち、文字列とコンマを分割する
        while (getline(stream, token, ',')) {
            if (num == 0 && stoi(token) != nowMyMapNum) {
                num = -1;
                break;
            }
            switch (num) {
            case 0:
                road.mapNum = stoi(token);
                break;
            case 1:
                road.roadNum = stoi(token);
                break;
            case 2:
                road.startPointNum = stoi(token);
                break;
            case 3:
                road.endPointNum = stoi(token);
                break;
            default:
                break;
            }

            num++;

        }

        if (num != -1) {

            //ここから道の曲がる場所の情報の読み込み
            //ファイルの読み込み
            std::ostringstream outstr;
            outstr << "CreationOfDungeon_master\\csv\\WorldMap\\Road\\RoadTurnPoint\\RoadTurnPoint_RoadNum" << road.roadNum << ".csv";
            std::string strPath = outstr.str();
            std::ifstream ifs2(strPath);
            if (ifs2.fail()) {
                printfDx("fail\n");
                return;
            }

            //csvファイルを1行ずつ読み込む
            std::string str2;
            while (getline(ifs2, str2)) {
                std::string::size_type index = str2.find("#");  // "#"を検索
                                                                //"#"が入っていた行は飛ばす
                if (index != std::string::npos) {
                    continue;
                }


                std::string token;
                std::istringstream stream(str2);

                RoadTurnPoint roadTurnPoint;
                int num = 0;
                //1行のうち、文字列とコンマを分割する
                while (getline(stream, token, ',')) {
                    switch (num) {
                    case 0:
                        roadTurnPoint.x = stod(token);
                        break;
                    case 1:
                        roadTurnPoint.y = stod(token);
                        break;
                    default:
                        break;
                    }

                    num++;

                }

                road.roadTurnPoint.push_back(roadTurnPoint);
            }

            nowMapRoadList.push_back(road);
        }

    }


}


int Map::MoveDirection(int startPointNum, int endPointNum) {

    for (int vec = 0; vec < nowMapRoadList.size(); vec++) {

        if (nowMapRoadList[vec].startPointNum == startPointNum && nowMapRoadList[vec].endPointNum == endPointNum) {
            return 1;
        }
        if (nowMapRoadList[vec].startPointNum == endPointNum && nowMapRoadList[vec].endPointNum == startPointNum) {
            return 2;
        }

    }

    return -1;

}


